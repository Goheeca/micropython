#include <stdio.h>

#include "py/runtime.h"
//#include "py/mperrno.h"
//#include "py/mphal.h"
#include "flash.h"

#define sFLASH_START_ADDRESS 0x00

STATIC mp_obj_t sFlash_read(mp_obj_t offset_in, mp_obj_t len_or_buf_in) {
    mp_int_t offset = mp_obj_get_int(offset_in);

    mp_int_t len;
    byte *buf;
    bool alloc_buf = MP_OBJ_IS_INT(len_or_buf_in);

    if (alloc_buf) {
        len = mp_obj_get_int(len_or_buf_in);
        buf = m_new(byte, len);
    } else {
        mp_buffer_info_t bufinfo;
        mp_get_buffer_raise(len_or_buf_in, &bufinfo, MP_BUFFER_WRITE);
        len = bufinfo.len;
        buf = (byte*)bufinfo.buf;
    }

    sFLASH_readBuffer((uint8_t*)buf, offset, len);
    if (alloc_buf) {
        return mp_obj_new_bytes(buf, len);
    }
    return mp_const_none;
	
    /*if (alloc_buf) {
        m_del(byte, buf, len);
    }
    mp_raise_OSError(res == SPI_FLASH_RESULT_TIMEOUT ? MP_ETIMEDOUT : MP_EIO);*/
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(sFlash_read_obj, sFlash_read);

STATIC mp_obj_t sFlash_write(mp_obj_t offset_in, const mp_obj_t buf_in) {
    mp_int_t offset = mp_obj_get_int(offset_in);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(buf_in, &bufinfo, MP_BUFFER_READ);
    /*if (bufinfo.len & 0x3) {
        mp_raise_ValueError("len must be multiple of 4");
    }*/

    sFLASH_writeBuffer((const uint8_t*)bufinfo.buf, offset, bufinfo.len);
    return mp_const_none;
    /*if (res == SPI_FLASH_RESULT_OK) {
        return mp_const_none;
    }
    mp_raise_OSError(res == SPI_FLASH_RESULT_TIMEOUT ? MP_ETIMEDOUT : MP_EIO);*/
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(sFlash_write_obj, sFlash_write);

STATIC mp_obj_t sFlash_erase(mp_obj_t sector_in) {
    mp_int_t sector = mp_obj_get_int(sector_in);

    sFLASH_eraseSector(sector);
    return mp_const_none;

    /*if (res == SPI_FLASH_RESULT_OK) {
        return mp_const_none;
    }
    mp_raise_OSError(res == SPI_FLASH_RESULT_TIMEOUT ? MP_ETIMEDOUT : MP_EIO);*/
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(sFlash_erase_obj, sFlash_erase);

STATIC mp_obj_t sFlash_size(void) {
    return MP_OBJ_NEW_SMALL_INT((uint32_t)sFLASH_END_ADDRESS-sFLASH_START_ADDRESS);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(sFlash_size_obj, sFlash_size);

STATIC mp_obj_t sFlash_start(void) {
    return MP_OBJ_NEW_SMALL_INT((uint32_t)sFLASH_START_ADDRESS);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(sFlash_start_obj, sFlash_start);

STATIC mp_obj_t sFlash_sector_size(void) {
    return MP_OBJ_NEW_SMALL_INT((uint32_t)sFLASH_SECTOR_SIZE);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(sFlash_sector_size_obj, sFlash_sector_size);


STATIC const mp_rom_map_elem_t sFlash_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_sFlash) },

    { MP_ROM_QSTR(MP_QSTR_read), MP_ROM_PTR(&sFlash_read_obj) },
    { MP_ROM_QSTR(MP_QSTR_write), MP_ROM_PTR(&sFlash_write_obj) },
    { MP_ROM_QSTR(MP_QSTR_erase), MP_ROM_PTR(&sFlash_erase_obj) },
    { MP_ROM_QSTR(MP_QSTR_size), MP_ROM_PTR(&sFlash_size_obj) },
    { MP_ROM_QSTR(MP_QSTR_start), MP_ROM_PTR(&sFlash_start_obj) },
    { MP_ROM_QSTR(MP_QSTR_sector_size), MP_ROM_PTR(&sFlash_sector_size_obj) },
};
STATIC MP_DEFINE_CONST_DICT(sFlash_module_globals, sFlash_module_globals_table);

const mp_obj_module_t sFlash_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&sFlash_module_globals,
};

STATIC const mp_rom_map_elem_t spark_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_spark) },

    { MP_ROM_QSTR(MP_QSTR_sFlash), MP_ROM_PTR(&sFlash_module) },
};

STATIC MP_DEFINE_CONST_DICT(spark_module_globals, spark_module_globals_table);

const mp_obj_module_t spark_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&spark_module_globals,
};