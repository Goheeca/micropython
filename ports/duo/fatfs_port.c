/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2013, 2014 Damien P. George
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <time.h>
#include "py/runtime.h"
#include "lib/oofatfs/ff.h"
#include "rtc_hal.h"

MP_WEAK DWORD get_fattime(void) {
    #if MICROPY_HW_ENABLE_RTC

    time_t time = HAL_RTC_Get_UnixTime();
    struct tm * timeinfo;
    timeinfo = localtime (&time);

    return ((timeinfo->tm_year - 80) << 25) | (timeinfo->tm_mon << 21) | (timeinfo->tm_mday << 16) | (timeinfo->tm_hour << 11) | (timeinfo->tm_min << 5) | (timeinfo->tm_sec >> 1);
    #else
    // Jan 1st, 2018 at midnight. Not sure what timezone.
    return ((2018 - 1980) << 25) | ((1) << 21) | ((1) << 16) | ((0) << 11) | ((0) << 5) | (0 / 2);
    #endif
}
