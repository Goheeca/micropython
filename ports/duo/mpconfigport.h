#include <stdint.h>

#ifndef __INCLUDED_MPCONFIGPORT_H
#define __INCLUDED_MPCONFIGPORT_H

// options to control how Micro Python is built

#define MICROPY_CAN_OVERRIDE_BUILTINS (1)

#define MICROPY_STACK_CHECK         (1)
#define MICROPY_ENABLE_PYSTACK      (0)
#define MICROPY_ENABLE_EMERGENCY_EXCEPTION_BUF   (1)
#define MICROPY_EMERGENCY_EXCEPTION_BUF_SIZE  (256)

#define MICROPY_OBJ_REPR            (MICROPY_OBJ_REPR_C)
#define MICROPY_KBD_EXCEPTION       (1)
#define MICROPY_REPL_AUTO_INDENT    (1)
//#define MICROPY_ASYNC_KBD_INTR      (1)
#define MICROPY_ENABLE_SCHEDULER    (0)

#define MICROPY_NLR_SETJMP          (1)
#define MICROPY_QSTR_BYTES_IN_HASH  (1)
#define MICROPY_ALLOC_PATH_MAX      (256)
#define MICROPY_ALLOC_PARSE_CHUNK_INIT (16)
#define MICROPY_EMIT_X64            (0)
#define MICROPY_EMIT_THUMB          (0)
#define MICROPY_EMIT_INLINE_THUMB   (0)
#define MICROPY_COMP_MODULE_CONST   (0)
#define MICROPY_COMP_CONST          (0)
#define MICROPY_COMP_DOUBLE_TUPLE_ASSIGN (1)
#define MICROPY_COMP_TRIPLE_TUPLE_ASSIGN (1)
#define MICROPY_MEM_STATS           (0)
#define MICROPY_DEBUG_PRINTERS      (0)
#define MICROPY_ENABLE_GC           (1)
#define MICROPY_REPL_EVENT_DRIVEN   (0)
#define MICROPY_HELPER_REPL         (1)
#define MICROPY_HELPER_LEXER_UNIX   (0)
#define MICROPY_ENABLE_SOURCE_LINE  (1)
#define MICROPY_ENABLE_DOC_STRING   (1)
//#define MICROPY_ERROR_REPORTING     (MICROPY_ERROR_REPORTING_TERSE)
#define MICROPY_BUILTIN_METHOD_CHECK_SELF_ARG (0)
#define MICROPY_PY_ASYNC_AWAIT      (1)

#define MICROPY_PY_BUILTINS_HELP    (1)
#define MICROPY_PY_BUILTINS_HELP_MODULES (1)
#define MICROPY_MODULE_WEAK_LINKS   (1)
//#define MICROPY_MODULE_FROZEN_STR   (0)
//#define MICROPY_MODULE_FROZEN_MPY   (0)

#define MICROPY_PY_OS_STATVFS       (1)
#define MICROPY_PY_UJSON            (1)
#define MICROPY_PY_UTIME            (1)
#define MICROPY_PY_UTIME_MP_HAL     (1)
#define MICROPY_PY_UERRNO           (1)
#define MICROPY_PY_UCTYPES          (1)
#define MICROPY_PY_UZLIB            (1)
#define MICROPY_PY_UJSON            (1)
#define MICROPY_PY_URE              (1)
#define MICROPY_PY_UHEAPQ           (1)
#define MICROPY_PY_UTIMEQ           (1)
#define MICROPY_PY_UHASHLIB         (1)
#define MICROPY_PY_UHASHLIB_MD5     (0)
#define MICROPY_PY_USSL             (0)
#define MICROPY_SSL_AXTLS           (0)
#define MICROPY_SSL_MBEDTLS         (0)
#if MICROPY_PY_USSL
#define MICROPY_PY_UHASHLIB_SHA1    (1)
#define MICROPY_PY_UCRYPTOLIB       (1)
#endif
#define MICROPY_PY_UBINASCII        (1)
#define MICROPY_PY_UBINASCII_CRC32  (1)
#define MICROPY_PY_URANDOM          (1)

#define MICROPY_MODULE_FROZEN (1)
#define MICROPY_PY_BUILTINS_BYTEARRAY (1)
#define MICROPY_PY_BUILTINS_MEMORYVIEW (1)
#define MICROPY_PY_BUILTINS_ENUMERATE (1)
#define MICROPY_PY_BUILTINS_FILTER  (1)
#define MICROPY_PY_BUILTINS_FROZENSET (1)
#define MICROPY_PY_BUILTINS_REVERSED (1)
#define MICROPY_PY_BUILTINS_SET     (1)
#define MICROPY_PY_BUILTINS_SLICE   (1)
#define MICROPY_PY_BUILTINS_PROPERTY (1)
#define MICROPY_PY_BUILTINS_MIN_MAX (1)
#define MICROPY_PY_BUILTINS_COMPILE (1)
#define MICROPY_PY_BUILTINS_NOTIMPLEMENTED (1)
#define MICROPY_PY_BUILTINS_INPUT   (1)
#define MICROPY_PY_BUILTINS_POW3    (1)
#define MICROPY_PY_BUILTINS_ROUND_INT    (1)
#define MICROPY_PY_BUILTINS_STR_UNICODE (1)
#define MICROPY_PY_BUILTINS_STR_CENTER (1)
#define MICROPY_PY_BUILTINS_STR_PARTITION (1)
#define MICROPY_PY_BUILTINS_STR_SPLITLINES (1)
#define MICROPY_PY_BUILTINS_SLICE_ATTRS (1)
#define MICROPY_PY___FILE__         (1)
#define MICROPY_PY_FUNCTION_ATTRS   (1)
#define MICROPY_PY_DESCRIPTORS      (1)
#define MICROPY_PY_ALL_SPECIAL_METHODS (1)
#define MICROPY_PY_REVERSE_SPECIAL_METHODS (1)
#define MICROPY_PY_ARRAY_SLICE_ASSIGN (1)
#define MICROPY_PY_GC               (1)
#define MICROPY_PY_ARRAY            (1)
#define MICROPY_PY_ARRAY_SLICE_ASSIGN (1)
#define MICROPY_PY_ATTRTUPLE        (1)
#define MICROPY_PY_COLLECTIONS      (1)
#define MICROPY_PY_COLLECTIONS_DEQUE (1)
#define MICROPY_PY_COLLECTIONS_ORDEREDDICT (1)
#define MICROPY_PY_MATH             (1)
#define MICROPY_PY_CMATH            (1)
#define MICROPY_PY_IO               (1)
#define MICROPY_PY_IO_IOBASE        (1)
#define MICROPY_PY_IO_FILEIO        (1)
#define MICROPY_PY_STRUCT           (1)
#define MICROPY_PY_SYS              (1)
#define MICROPY_PY_SYS_MAXSIZE      (1)
#define MICROPY_PY_SYS_EXIT         (1)
#define MICROPY_PY_SYS_STDFILES     (1)
#define MICROPY_PY_OS_STATVFS       (1)
#define MICROPY_CPYTHON_COMPAT      (0)
#define MICROPY_LONGINT_IMPL        (MICROPY_LONGINT_IMPL_MPZ)
#define MICROPY_FLOAT_IMPL          (MICROPY_FLOAT_IMPL_FLOAT)


#define MICROPY_VFS                    (1)
#define MICROPY_FATFS_ENABLE_LFN       (1)
#define MICROPY_FATFS_RPATH            (2)
#define MICROPY_FATFS_MAX_SS           (4096)
#define MICROPY_FATFS_LFN_CODE_PAGE    437 /* 1=SFN/ANSI 437=LFN/U.S.(OEM) */
#define MICROPY_VFS_FAT                (1)
#define MICROPY_VFS_FAT_HEAP_BUFFER    (1)
#define MICROPY_FATFS_MULTI_PARTITION  (0)
#define MICROPY_READER_VFS             (MICROPY_VFS)


#define MICROPY_ERROR_REPORTING     (MICROPY_ERROR_REPORTING_DETAILED)
#define MICROPY_WARNINGS            (1)
#define MICROPY_ERROR_PRINTER       (&mp_stderr_print)
#define MICROPY_PY_STR_BYTES_CMP_WARN (1)

extern const struct _mp_print_t mp_stderr_print;


// extra builtin modules to add to the list of known ones
extern const struct _mp_obj_module_t pyb_module;
extern const struct _mp_obj_module_t spark_module;
extern const struct _mp_obj_module_t uos_module;

#define MICROPY_PORT_BUILTIN_MODULES \
    { MP_OBJ_NEW_QSTR(MP_QSTR_pyb), (mp_obj_t)&pyb_module }, \
    { MP_OBJ_NEW_QSTR(MP_QSTR_spark), (mp_obj_t)&spark_module }, \
    { MP_OBJ_NEW_QSTR(MP_QSTR_uos), (mp_obj_t)&uos_module }, \

// extra constants
#define MICROPY_PORT_CONSTANTS \
    { MP_OBJ_NEW_QSTR(MP_QSTR_pyb), (mp_obj_t)&pyb_module }, \


#define BYTES_PER_WORD (4)

#define MICROPY_MAKE_POINTER_CALLABLE(p) ((void*)((mp_uint_t)(p) | 1))

// This port is intended to be 32-bit, but unfortunately, int32_t for
// different targets may be defined in different ways - either as int
// or as long. This requires different printf formatting specifiers
// to print such value. So, we avoid int32_t and use int directly.
#define UINT_FMT "%u"
#define INT_FMT "%d"
typedef int mp_int_t; // must be pointer size
typedef unsigned mp_uint_t; // must be pointer size

typedef void *machine_ptr_t; // must be of pointer size
typedef const void *machine_const_ptr_t; // must be of pointer size
typedef long mp_off_t;

#define MP_PLAT_PRINT_STRN(str, len) mp_hal_stdout_tx_strn_cooked(str, len)

#define mp_type_fileio mp_type_vfs_fat_fileio
#define mp_type_textio mp_type_vfs_fat_textio

// use vfs's functions for import stat and builtin open
#define mp_import_stat mp_vfs_import_stat
#define mp_builtin_open mp_vfs_open
#define mp_builtin_open_obj mp_vfs_open_obj

// extra built in names to add to the global namespace
#define MICROPY_PORT_BUILTINS \
    { MP_OBJ_NEW_QSTR(MP_QSTR_open), (mp_obj_t)&mp_builtin_open_obj },

#include "platform_config.h"

// board specific definitions
#include "mpconfigboard.h"

// We need to provide a declaration/definition of alloca()
#include <alloca.h>

#define MICROPY_PIN_DEFS_PORT_H "pin_defs_stmhal.h"

#ifdef __thumb__
#define MICROPY_MIN_USE_CORTEX_CPU (1)
#define MICROPY_MIN_USE_STM32_MCU (1)
#endif

#define PYB_EXTI_NUM_VECTORS (23)

#define MP_STATE_PORT MP_STATE_VM

#define MICROPY_PORT_ROOT_POINTERS \
    const char *readline_hist[8]; \
    \
    mp_obj_t mp_const_vcp_interrupt; \
    mp_obj_t pyb_hid_report_desc; \
    \
    mp_obj_t pyb_config_main; \
    \
    mp_obj_t pyb_switch_callback; \
    \
    mp_obj_t pin_class_mapper; \
    mp_obj_t pin_class_map_dict; \
    \
    mp_obj_t pyb_extint_callback[PYB_EXTI_NUM_VECTORS]; \
    \
    /* Used to do callbacks to Python code on interrupt */ \
    struct _pyb_timer_obj_t *pyb_timer_obj_all[14]; \
    \
    /* stdio is repeated on this UART object if it's not null */ \
    struct _pyb_uart_obj_t *pyb_stdio_uart; \
    \
    /* pointers to all UART objects (if they have been created) */ \
    struct _pyb_uart_obj_t *pyb_uart_obj_all[6]; \
    \
    /* pointers to all CAN objects (if they have been created) */ \
    struct _pyb_can_obj_t *pyb_can_obj_all[2]; \
    \
    /* list of registered NICs */ \
    mp_obj_list_t mod_network_nic_list; \

#endif // __INCLUDED_MPCONFIGPORT_H
