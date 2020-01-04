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

// clang-format off
#define MMAP_BLOCK_SIZE 0x1000

#define S922X_GPIO_BASE 0xFF634000
#define S922X_PWM_BASE  0xFFD19000

#define S922X_BOOT_INPUT_EN_0_REG_OFFSET    0x110
#define S922X_GPIOC_INPUT_EN_1_REG_OFFSET   0x113
#define S922X_GPIOX_INPUT_EN_2_REG_OFFSET   0x116
#define S922X_GPIOH_INPUT_EN_3_REG_OFFSET   0x119
#define S922X_GPIOZ_INPUT_EN_4_REG_OFFSET   0x11C
#define S922X_GPIOA_INPUT_EN_5_REG_OFFSET   0x120

#define S922X_BOOT_OUTPUT_0_REG_OFFSET      0x111
#define S922X_GPIOC_OUTPUT_1_REG_OFFSET     0x114
#define S922X_GPIOX_OUTPUT_2_REG_OFFSET     0x117
#define S922X_GPIOH_OUTPUT_3_REG_OFFSET     0x11A
#define S922X_GPIOZ_OUTPUT_4_REG_OFFSET     0x11D
#define S922X_GPIOA_OUTPUT_5_REG_OFFSET     0x121

#define S922X_BOOT_INPUT_0_REG_OFFSET       0x112
#define S922X_GPIOC_INPUT_1_REG_OFFSET      0x115
#define S922X_GPIOX_INPUT_2_REG_OFFSET      0x118
#define S922X_GPIOH_INPUT_3_REG_OFFSET      0x11B
#define S922X_GPIOZ_INPUT_4_REG_OFFSET      0x11E
#define S922X_GPIOA_INPUT_5_REG_OFFSET      0x122

#define S922X_BOOT_MUX_0_REG_OFFSET         0x1B0
#define S922X_BOOT_MUX_1_REG_OFFSET         0x1B1
#define S922X_RESERVED_MUX_2_REG_OFFSET     0x1B2
#define S922X_GPIOX_MUX_3_REG_OFFSET        0x1B3
#define S922X_GPIOX_MUX_4_REG_OFFSET        0x1B4
#define S922X_GPIOX_MUX_5_REG_OFFSET        0x1B5
#define S922X_GPIOZ_MUX_6_REG_OFFSET        0x1B6
#define S922X_GPIOZ_MUX_7_REG_OFFSET        0x1B7
#define S922X_RESERVED_MUX_8_REG_OFFSET     0x1B8
#define S922X_GPIOC_MUX_9_REG_OFFSET        0x1B9
#define S922X_RESERVED_MUX_A_REG_OFFSET     0x1BA
#define S922X_GPIOH_MUX_B_REG_OFFSET        0x1BB
#define S922X_GPIOH_MUX_C_REG_OFFSET        0x1BC
#define S922X_GPIOA_MUX_D_REG_OFFSET        0x1BD
#define S922X_GPIOA_MUX_E_REG_OFFSET        0x1BE
#define S922X_RESERVED_MUX_F_REG_OFFSET     0x1BF

#define S922X_BOOT_PULL_UP_0_REG_OFFSET     0x13A
#define S922X_GPIOC_PULL_UP_1_REG_OFFSET    0x13B
#define S922X_GPIOX_PULL_UP_2_REG_OFFSET    0x13C
#define S922X_GPIOH_PULL_UP_3_REG_OFFSET    0x13D
#define S922X_GPIOZ_PULL_UP_4_REG_OFFSET    0x13E
#define S922X_GPIOA_PULL_UP_5_REG_OFFSET    0x13F

#define S922X_BOOT_PULL_UP_EN_0_REG_OFFSET  0x148
#define S922X_GPIOC_PULL_UP_EN_1_REG_OFFSET 0x149
#define S922X_GPIOX_PULL_UP_EN_2_REG_OFFSET 0x14A
#define S922X_GPIOH_PULL_UP_EN_3_REG_OFFSET 0x14B
#define S922X_GPIOZ_PULL_UP_EN_4_REG_OFFSET 0x14C
#define S922X_GPIOA_PULL_UP_EN_5_REG_OFFSET 0x14D

#define S922X_BOOT_DS_0A_REG_OFFSET         0x1D0
#define S922X_GPIOC_DS_1A_REG_OFFSET        0x1D1
#define S922X_GPIOX_DS_2A_REG_OFFSET        0x1D2
#define S922X_GPIOX_DS_2B_REG_OFFSET        0x1D3
#define S922X_GPIOH_DS_3A_REG_OFFSET        0x1D4
#define S922X_GPIOZ_DS_4A_REG_OFFSET        0x1D5
#define S922X_GPIOA_DS_5A_REG_OFFSET        0x1D6

namespace lot
{
    enum{
        BOOT0 = 0,
        GPIOC0 = 32,
        GPIOX0 = 32*2,
        GPIOX1,
        GPIOX2,
        GPIOX3,
        GPIOX4,
        GPIOX5,
        GPIOX6,
        GPIOX7,
        GPIOX8,
        GPIOX9,
        GPIOX10,
        GPIOX11,
        GPIOX12,
        GPIOX13,
        GPIOX14,
        GPIOX15,
        GPIOX16,
        GPIOX17,
        GPIOX18,
        GPIOX19,
        GPIOH0 = 32*3,
        GPIOZ0 = 32*4,
        GPIOA0 = 32*5,
        GPIOA1,
        GPIOA2,
        GPIOA3,
        GPIOA4,
        GPIOA5,
        GPIOA6,
        GPIOA7,
        GPIOA8,
        GPIOA9,
        GPIOA10,
        GPIOA11,
        GPIOA12,
        GPIOA13,
        GPIOA14,
        GPIOA15,
    };
}
// clang-format off
