#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>

#include "ticks_api.h"

#include "py/nlr.h"
#include "py/compile.h"
#include "py/runtime.h"
#include "py/stackctrl.h"
#include "py/repl.h"
#include "py/gc.h"
#include "py/mphal.h"
#include "py/builtin.h"
#include "gccollect.h"
#include "lib/utils/pyexec.h"
#include "lib/utils/interrupt_char.h"
#include "readline.h"
#include "wiring.h"
#include "extint.h"
#include "TCP_server.h"
#include "ble.h"


static mp_obj_t result = MP_OBJ_NULL;
const qstr UNDERSCORE = MP_QSTR__;

void do_str(const char *src, mp_parse_input_kind_t input_kind) {
    mp_lexer_t *lex = mp_lexer_new_from_str_len(MP_QSTR__lt_stdin_gt_, src, strlen(src), 0);
    if (lex == NULL) {
        printf("MemoryError: lexer could not allocate memory\n");
        return;
    }

    nlr_buf_t nlr;
    if (nlr_push(&nlr) == 0) {
        qstr source_name = lex->source_name;
        mp_parse_tree_t parse_tree = mp_parse(lex, input_kind);
        mp_obj_t module_fun = mp_compile(&parse_tree, source_name, MP_EMIT_OPT_NONE, true);
        result = mp_call_function_0(module_fun);
        if (result != MP_OBJ_NULL) {
            mp_module_builtins.base.type->attr(MP_OBJ_FROM_PTR(&mp_module_builtins), UNDERSCORE, &result);
        }
        nlr_pop();
    } else {
        // uncaught exception
        mp_obj_print_exception(&mp_plat_print, (mp_obj_t)nlr.ret_val);
    }
}

#define HEAP_SIZE (20*1024)
//void * heap;
void mp_heap() {
  /*heap = malloc(HEAP_SIZE);
  if(!heap) {
    printf("FATAL: couldn't allocate heap of size %u\n", HEAP_SIZE);
    while(1);
  }*/
}
static char heap[HEAP_SIZE];

void mp_reset() {
    mp_stack_ctrl_init();
    mp_stack_set_limit(3*1024+512);
#if MICROPY_ENABLE_GC
    //gc_init((void*)min_heap_end, (void*)end);
    gc_init(heap, heap + sizeof(heap));
    //gc_init(heap, heap + HEAP_SIZE);
#endif
    mp_init();
    mp_obj_list_init(mp_sys_path, 0);
    mp_obj_list_append(mp_sys_path, MP_OBJ_NEW_QSTR(MP_QSTR_)); // current dir (or base dir of the script)
    mp_obj_list_init(mp_sys_argv, 0);
    readline_init0();
    extint_init0();
    TCP_server_init0();
    ble_init0();
    mp_hal_set_interrupt_char(CHAR_CTRL_C);
#if MICROPY_MODULE_FROZEN
    pyexec_frozen_module("_boot.py");
    if (mp_import_stat("boot.py") == MP_IMPORT_STAT_FILE) {
        pyexec_file("boot.py");
    }
    if (pyexec_mode_kind == PYEXEC_MODE_FRIENDLY_REPL) {
        if (mp_import_stat("main.py") == MP_IMPORT_STAT_FILE) {
            pyexec_file("main.py");
        }
    }
#endif
}

void soft_reset(void) {
    gc_sweep_all();
    mp_hal_stdout_tx_str("!!! Soft reboot\r\n");
    delayMicroseconds(10000); // allow UART to flush output
    mp_deinit();
    mp_reset();
#if MICROPY_REPL_EVENT_DRIVEN
    pyexec_event_repl_init();
#endif
}

void mp_setup() {
    usbserial_begin(9600);
    mp_reset();
    mp_hal_stdout_tx_str("\r\n");
#if MICROPY_REPL_EVENT_DRIVEN
    pyexec_event_repl_init();
#endif
}

static jmp_buf buf;

void mp_loop() {
    if(setjmp(buf)) {
soft_reset:
        soft_reset();
    }
#if MICROPY_REPL_EVENT_DRIVEN
        for (;;) {
            int c = mp_hal_stdin_rx_chr();
            if (pyexec_event_repl_process_char(c)) {
                break;
            }
        }
#else
        for (;;) {
            if (pyexec_mode_kind == PYEXEC_MODE_RAW_REPL) {
                if (pyexec_raw_repl() != 0) {
                    break;
                }
            } else {
                if (pyexec_friendly_repl() != 0) {
                    break;
                }
            }
        }
#endif
        goto soft_reset;
}

#if !MICROPY_VFS
mp_lexer_t *mp_lexer_new_from_file(const char *filename) {
    mp_raise_OSError(MP_ENOENT);
}

mp_import_stat_t mp_import_stat(const char *path) {
    (void)path;
    return MP_IMPORT_STAT_NO_EXIST;
}

mp_obj_t mp_builtin_open(size_t n_args, const mp_obj_t *args, mp_map_t *kwargs) {
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_KW(mp_builtin_open_obj, 1, mp_builtin_open);

#endif

STATIC void stderr_print_strn(void *env, const char *str, size_t len) {
    (void)env;
    //ssize_t dummy = write(STDERR_FILENO, str, len);
    //mp_uos_dupterm_tx_strn(str, len);
    mp_hal_stdout_tx_strn(str, len);
    //(void)dummy;
}

const mp_print_t mp_stderr_print = {NULL, stderr_print_strn};

void NORETURN __fatal_error(const char *msg) {
    printf("!!! %s\n", msg);
    longjmp(buf, 1);
}

void nlr_jump_fail(void *val) {
    printf("FATAL: uncaught exception %p\n", val);
    mp_obj_print_exception(&mp_plat_print, MP_OBJ_FROM_PTR(val));
    __fatal_error("Uncaught exception");
}

#ifndef NDEBUG
void MP_WEAK __assert_func(const char *file, int line, const char *func, const char *expr) {
    printf("Assertion '%s' failed, at file %s:%d\n", expr, file, line);
    __fatal_error("Assertion failed");
}
#endif

void __check_keyboardinterrupt() {
    int peek = mp_hal_stdin_rx_chr_peek();
    if(peek != -1) {
        if(peek == CHAR_CTRL_C) {
            mp_keyboard_interrupt();
        }
        mp_hal_stdin_rx_chr();
    }
}

void __raise_keyboardinterrupt() {
    if (MP_STATE_VM(mp_pending_exception) == MP_OBJ_FROM_PTR(&MP_STATE_VM(mp_kbd_exception))) {
        MP_STATE_VM(mp_pending_exception) = MP_OBJ_NULL;
        nlr_raise(mp_obj_new_exception(&mp_type_KeyboardInterrupt));
    }
}

void handle_keyboardinterrupt() {
    __check_keyboardinterrupt();
    __raise_keyboardinterrupt();
}
