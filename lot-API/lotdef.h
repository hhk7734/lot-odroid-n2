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

enum GpioMode
{
    // clang-format off
    ALT0 = 0,
            ALT1,   ALT2,   ALT3,
    ALT4,   ALT5,   ALT6,   ALT7,
    DIN,    DOUT,   AIN,    AOUT,
    PWM
    // clang-format on
};

enum PUDMode
{
    PULL_OFF = 0,
    PULL_DOWN,
    PULL_UP
};

constexpr int LOW  = 0;
constexpr int HIGH = 1;

enum BitOrder
{
    LSB_FIRST = 0,
    MSB_FIRST
};

const std::map<std::string, GpioMode> pin_mode_stoi = {
    { "ALT0", ALT0 }, { "ALT1", ALT1 }, { "ALT2", ALT2 }, { "ALT3", ALT3 },
    { "ALT4", ALT4 }, { "ALT5", ALT5 }, { "ALT6", ALT6 }, { "ALT7", ALT7 },
    { "DIN", DIN },   { "DOUT", DOUT }, { "AIN", AIN },   { "AOUT", AOUT },
    { "PWM", PWM },
};
const std::map<GpioMode, std::string> pin_mode_itos = {
    { ALT0, "ALT0" }, { ALT1, "ALT1" }, { ALT2, "ALT2" }, { ALT3, "ALT3" },
    { ALT4, "ALT4" }, { ALT5, "ALT5" }, { ALT6, "ALT6" }, { ALT7, "ALT7" },
    { DIN, "DIN" },   { DOUT, "DOUT" }, { AIN, "AIN" },   { AOUT, "AOUT" },
    { PWM, "PWM" },
};

const std::map<std::string, PUDMode> pud_stoi = { { "PULL_OFF", PULL_OFF },
                                                  { "PULL_DOWN", PULL_DOWN },
                                                  { "PULL_UP", PULL_UP } };
const std::map<PUDMode, std::string> pud_itos = { { PULL_OFF, "PULL_OFF" },
                                                  { PULL_DOWN, "PULL_DOWN" },
                                                  { PULL_UP, "PULL_UP" } };

const std::map<std::string, int> status_stoi
    = { { "LOW", LOW }, { "HIGH", HIGH } };
const std::map<int, std::string> status_itos
    = { { LOW, "LOW" }, { HIGH, "HIGH" } };

const std::map<std::string, BitOrder> bit_order_stoi
    = { { "LSB_FIRST", LSB_FIRST }, { "MSB_FIRST", MSB_FIRST } };
const std::map<BitOrder, std::string> bit_order_itos
    = { { LSB_FIRST, "LSB_FIRST" }, { MSB_FIRST, "MSB_FIRST" } };

/**
 * UXYZ \n
 *      @arg X: data bits; 5, 6, 7, 8 \n
 *      @arg Y: parity bits; N: None, E: Even, O: Odd, M: Mark, S: Space \n
 *      @arg Z: stop bits; 1, 2
 */
enum UartMode
{
    // clang-format off
    U5N1 = 0,
            U6N1,   U7N1,   U8N1,
    U5N2,   U6N2,   U7N2,   U8N2,
    U5E1,   U6E1,   U7E1,   U8E1,
    U5E2,   U6E2,   U7E2,   U8E2,
    U5O1,   U6O1,   U7O1,   U8O1,
    U5O2,   U6O2,   U7O2,   U8O2,
    U5M1,   U6M1,   U7M1,   U8M1,
    U5M2,   U6M2,   U7M2,   U8M2,
    U5S1,   U6S1,   U7S1,   U8S1,
    U5S2,   U6S2,   U7S2,   U8S2
    // clang-format on
};

enum SpiMode
{
    MODE0 = 0,
    MODE1,
    MODE2,
    MODE3
};

enum LogLevel
{
    DEBUG = 0,
    INFO,
    WARNING,
    ERROR
};
}    // namespace lot