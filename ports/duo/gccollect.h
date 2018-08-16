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
#ifndef MICROPY_INCLUDED_STM32_GCCOLLECT_H
#define MICROPY_INCLUDED_STM32_GCCOLLECT_H

// variables defining memory layout
// (these probably belong somewhere else...)
/*extern uint32_t _etext;
extern uint32_t _sidata;
extern uint32_t _ram_start;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _heap_start;
extern uint32_t _heap_end;
extern uint32_t _estack;
extern uint32_t _ram_end;*/
extern const uint32_t sram_start;
extern const uint32_t sram_end;

#define STACK_SIZE (8*1024)
#define SENTINEL (1*1024)

#define HEAP_START ((void*) sram_start)
#define STACK_TOP ((void*) sram_end)
#define STACK_BOTTOM (STACK_TOP - STACK_SIZE)
#define HEAP_END (STACK_BOTTOM - SENTINEL)

#endif // MICROPY_INCLUDED_STM32_GCCOLLECT_H
