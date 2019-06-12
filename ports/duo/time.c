#include <stdio.h>
#include <string.h>

#include "py/nlr.h"
#include "py/smallint.h"
#include "py/obj.h"
#include "timeutils.h"
#include "portmodules.h"
#include "wiring.h"

#define CHUNK_MS (10)

mp_obj_t time_delay_ms(mp_obj_t ms)
{
	int d = mp_obj_get_int(ms);
	handle_keyboardinterrupt();
	while (d > CHUNK_MS) {
		delay(CHUNK_MS);
		handle_keyboardinterrupt();
		d -= CHUNK_MS;
	}
	delay(d);

	return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_1(time_delay_ms_obj, time_delay_ms);

#define CHUNK_US (10000)

mp_obj_t time_delay_us(mp_obj_t us)
{
	int d = mp_obj_get_int(us);
	// TODO calibration
	handle_keyboardinterrupt();
	while (d > CHUNK_US) {
		delayMicroseconds(CHUNK_US);
		handle_keyboardinterrupt();
		d -= CHUNK_US;
	}
	delayMicroseconds(d);

	return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_1(time_delay_us_obj, time_delay_us);

STATIC const mp_map_elem_t time_module_globals_table[] = {
	{ MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_utime) },

	{ MP_OBJ_NEW_QSTR(MP_QSTR_delayMilliseconds), (mp_obj_t)&time_delay_ms_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_delayMicroseconds), (mp_obj_t)&time_delay_us_obj },
};

STATIC MP_DEFINE_CONST_DICT(time_module_globals, time_module_globals_table);

const mp_obj_module_t mp_module_utime = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&time_module_globals,
};
