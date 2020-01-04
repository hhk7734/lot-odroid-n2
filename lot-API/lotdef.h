/*
 * MIT License
 * Copyright (c) 2019-2020 Hyeonki Hong <hhk7734@gmail.com>
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
#include <map>
#include <string>

namespace lot
{
constexpr int UNUSED = -1;

typedef enum
{
    ALT0 = 0,
    ALT1,
    ALT2,
    ALT3,
    ALT4,
    ALT5,
    ALT6,
    ALT7,
    DIN,
    DOUT,
    AIN,
    AOUT
} pin_mode_t;

typedef enum
{
    PULL_OFF = 0,
    PULL_DOWN,
    PULL_UP
} pud_mode_t;

enum
{
    LOW = 0,
    HIGH
};

typedef enum
{
    LSB_FIRST = 0,
    MSB_FIRST
} bit_order_t;

const std::map<std::string, pin_mode_t> pin_mode_stoi = {
    { "ALT0", ALT0 }, { "ALT1", ALT1 }, { "ALT2", ALT2 }, { "ALT3", ALT3 },
    { "ALT4", ALT4 }, { "ALT5", ALT5 }, { "ALT6", ALT6 }, { "ALT7", ALT7 },
    { "DIN ", DIN },  { "DOUT", DOUT }, { "AIN ", AIN },  { "AOUT", AOUT },
};
const std::map<pin_mode_t, std::string> pin_mode_itos = {
    { ALT0, "ALT0" }, { ALT1, "ALT1" }, { ALT2, "ALT2" }, { ALT3, "ALT3" },
    { ALT4, "ALT4" }, { ALT5, "ALT5" }, { ALT6, "ALT6" }, { ALT7, "ALT7" },
    { DIN, "DIN " },  { DOUT, "DOUT" }, { AIN, "AIN " },  { AOUT, "AOUT" },
};

const std::map<std::string, pud_mode_t> pud_stoi = { { "PULL_OFF", PULL_OFF },
                                               { "PULL_DOWN", PULL_DOWN },
                                               { "PULL_UP", PULL_UP } };
const std::map<pud_mode_t, std::string> pud_itos = { { PULL_OFF, "PULL_OFF" },
                                               { PULL_DOWN, "PULL_DOWN" },
                                               { PULL_UP, "PULL_UP" } };

const std::map<std::string, int> status_stoi = { { "LOW", LOW }, { "HIGH", HIGH } };
const std::map<int, std::string> status_itos = { { LOW, "LOW" }, { HIGH, "HIGH" } };

const std::map<std::string, bit_order_t> bit_order_stoi
    = { { "LSB_FIRST", LSB_FIRST }, { "MSB_FIRST", MSB_FIRST } };
const std::map<bit_order_t, std::string> bit_order_itos
    = { { LSB_FIRST, "LSB_FIRST" }, { MSB_FIRST, "MSB_FIRST" } };
}    // namespace lot