/*
 * MIT License
 * Copyright (c) 2019 Hyeonki Hong <hhk7734@gmail.com>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <stdint.h>

namespace lot
{
#define USING_LARGE_PIN_SIZE 0

typedef enum
{
    LOT = 0,
    PHY
} lot_mode_t;

#if USING_LARGE_PIN_SIZE
typedef uint32_t pin_size_t;
#define UNUSED 0xFFFFFFFF
#else
typedef uint8_t pin_size_t;
#define UNUSED 0xFF
#endif    // USING_LARGE_PIN_SIZE

typedef enum
{
    INPUT = 0,
    OUTPUT,
    ALT_FUNC0 = 100,
    ALT_FUNC1,
    ALT_FUNC2,
    ALT_FUNC3,
    ALT_FUNC4,
    ALT_FUNC5,
    ALT_FUNC6,
    ALT_FUNC7
} pin_mode_t;

typedef enum
{
    PULL_OFF = 0,
    PULL_DOWN,
    PULL_UP
} pud_mode_t;

typedef enum
{
    LOW = 0,
    HIGH
} pin_status_t;

typedef enum
{
    LSB_FIRST = 0,
    MSB_FIRST
} bit_order_t;

}    // namespace lot