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

#include "s922x.h"
#include "lot-API/lotdef.h"

// clang-format off
#define N2_SYS_PIN_BASE     460
#define MAX_PHY_PIN_COUNT   40
#define MAX_LOT_PIN_COUNT   36
// clang-format on

namespace lot
{
const int phy_to_lot[MAX_PHY_PIN_COUNT + 1] = {
    // clang-format off
     UNUSED,
     UNUSED, UNUSED,   // 3.3V                 1   | 2     5.0V
         33, UNUSED,   // GPIOX.17(I2C-2_SDA)  3   | 4     5.0V
         34, UNUSED,   // GPIOX.18(I2C-2_SCL)  5   | 6     GND
         13,     28,   // GPIOA.13             7   | 8     GPIOX.12(UART_TX_B)
     UNUSED,     29,   // GND                  9   | 10    GPIOX.13(UART_RX_B)
         19,     32,   // GPIOX.3              11  | 12    GPIOX.16(PWM_E)
         20, UNUSED,   // GPIOX.4              13  | 14    GND
         23,     16,   // GPIOX.7(PWM_F)       15  | 16    GPIOX.0
     UNUSED,     17,   // 3.3V                 17  | 18    GPIOX.1
         24, UNUSED,   // GPIOX.8(SPI_MOSI)    19  | 20    GND
         25,     18,   // GPIOX.9(SPI_MISO)    21  | 22    GPIOX.2
         27,     26,   // GPIOX.11(SPI_SCLK)   23  | 24    GPIOX.10(SPI_CE0)
     UNUSED,      4,   // GND                  25  | 26    GPIOA.4(SPI_CE1)
         14,     15,   // GPIOA.14(I2C-3_SDA)  27  | 28    GPIOA.15(I2C-3_SCL)
         30, UNUSED,   // GPIOX.14             29  | 30    GND
         31,     12,   // GPIOX.15             31  | 32    GPIOA.12
         21, UNUSED,   // GPIOX.5(PWM_C)       33  | 34    GND
         22,     35,   // GPIOX.6(PWM_D)       35  | 36    GPIOX.19
     UNUSED, UNUSED,   // ADC.AIN3             37  | 38    1.8V REF OUT
     UNUSED, UNUSED    // GND                  39  | 40    ADC.AIN2
    // clang-format on
};

const int lot_to_phy[MAX_LOT_PIN_COUNT] = {
    // clang-format off
     UNUSED,  UNUSED,   // GPIOA.0      |   GPIOA.1
     UNUSED,  UNUSED,   // GPIOA.2      |   GPIOA.3
         26,  UNUSED,   // GPIOA.4      |   GPIOA.5
     UNUSED,  UNUSED,   // GPIOA.6      |   GPIOA.7
     UNUSED,  UNUSED,   // GPIOA.8      |   GPIOA.9
     UNUSED,  UNUSED,   // GPIOA.10     |   GPIOA.11
         32,       7,   // GPIOA.12     |   GPIOA.13
         27,      28,   // GPIOA.14     |   GPIOA.15
         16,      18,   // GPIOX.0      |   GPIOX.1
         22,      11,   // GPIOX.2      |   GPIOX.3
         13,      33,   // GPIOX.4      |   GPIOX.5
         35,      15,   // GPIOX.6      |   GPIOX.7
         19,      21,   // GPIOX.8      |   GPIOX.9
         24,      23,   // GPIOX.10     |   GPIOX.11
          8,      10,   // GPIOX.12     |   GPIOX.13
         29,      31,   // GPIOX.14     |   GPIOX.15
         12,       3,   // GPIOX.16     |   GPIOX.17
          5,      36    // GPIOX.18     |   GPIOX.19
    // clang-format on
};

const uint8_t lot_to_shift[MAX_LOT_PIN_COUNT] = {
    // clang-format off
      0,   1,   // GPIOA.0      |   GPIOA.1
      2,   3,   // GPIOA.2      |   GPIOA.3
      4,   5,   // GPIOA.4      |   GPIOA.5
      6,   7,   // GPIOA.6      |   GPIOA.7
      8,   9,   // GPIOA.8      |   GPIOA.9
     10,  11,   // GPIOA.10     |   GPIOA.11
     12,  13,   // GPIOA.12     |   GPIOA.13
     14,  15,   // GPIOA.14     |   GPIOA.15
      0,   1,   // GPIOX.0      |   GPIOX.1
      2,   3,   // GPIOX.2      |   GPIOX.3
      4,   5,   // GPIOX.4      |   GPIOX.5
      6,   7,   // GPIOX.6      |   GPIOX.7
      8,   9,   // GPIOX.8      |   GPIOX.9
     10,  11,   // GPIOX.10     |   GPIOX.11
     12,  13,   // GPIOX.12     |   GPIOX.13
     14,  15,   // GPIOX.14     |   GPIOX.15
     16,  17,   // GPIOX.16     |   GPIOX.17
     18,  19    // GPIOX.18     |   GPIOX.19
    // clang-format on
};

const bool is_available_lot[MAX_LOT_PIN_COUNT] = {
    // clang-format off
     false, false,   // GPIOA.0      |   GPIOA.1
     false, false,   // GPIOA.2      |   GPIOA.3
     true,  false,   // GPIOA.4      |   GPIOA.5
     false, false,   // GPIOA.6      |   GPIOA.7
     false, false,   // GPIOA.8      |   GPIOA.9
     false, false,   // GPIOA.10     |   GPIOA.11
     true,  true,    // GPIOA.12     |   GPIOA.13
     true,  true,    // GPIOA.14     |   GPIOA.15
     true,  true,    // GPIOX.0      |   GPIOX.1
     true,  true,    // GPIOX.2      |   GPIOX.3
     true,  true,    // GPIOX.4      |   GPIOX.5
     true,  true,    // GPIOX.6      |   GPIOX.7
     true,  true,    // GPIOX.8      |   GPIOX.9
     true,  true,    // GPIOX.10     |   GPIOX.11
     true,  true,    // GPIOX.12     |   GPIOX.13
     true,  true,    // GPIOX.14     |   GPIOX.15
     true,  true,    // GPIOX.16     |   GPIOX.17
     true,  true     // GPIOX.18     |   GPIOX.19
    // clang-format on
};
}    // namespace lot