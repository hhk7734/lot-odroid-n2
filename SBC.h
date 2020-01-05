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

namespace lot
{
constexpr int LAST_PHY_PIN = 40;

const int phy_to_gpio[LAST_PHY_PIN + 1] = {
    // clang-format off
     UNUSED ,
     UNUSED , UNUSED ,   // 3.3V                 1   | 2     5.0V
     GPIOX17, UNUSED ,   // GPIOX.17(I2C-2_SDA)  3   | 4     5.0V
     GPIOX18, UNUSED ,   // GPIOX.18(I2C-2_SCL)  5   | 6     GND
     GPIOA13, GPIOX12,   // GPIOA.13             7   | 8     GPIOX.12(UART_TX_B)
     UNUSED , GPIOX13,   // GND                  9   | 10    GPIOX.13(UART_RX_B)
     GPIOX3 , GPIOX16,   // GPIOX.3              11  | 12    GPIOX.16(PWM_E)
     GPIOX4 , UNUSED ,   // GPIOX.4              13  | 14    GND
     GPIOX7 , GPIOX0 ,   // GPIOX.7(PWM_F)       15  | 16    GPIOX.0
     UNUSED , GPIOX1 ,   // 3.3V                 17  | 18    GPIOX.1
     GPIOX8 , UNUSED ,   // GPIOX.8(SPI_MOSI)    19  | 20    GND
     GPIOX9 , GPIOX2 ,   // GPIOX.9(SPI_MISO)    21  | 22    GPIOX.2
     GPIOX11, GPIOX10,   // GPIOX.11(SPI_SCLK)   23  | 24    GPIOX.10(SPI_CE0)
     UNUSED , GPIOA4 ,   // GND                  25  | 26    GPIOA.4(SPI_CE1)
     GPIOA14, GPIOA15,   // GPIOA.14(I2C-3_SDA)  27  | 28    GPIOA.15(I2C-3_SCL)
     GPIOX14, UNUSED ,   // GPIOX.14             29  | 30    GND
     GPIOX15, GPIOA12,   // GPIOX.15             31  | 32    GPIOA.12
     GPIOX5 , UNUSED ,   // GPIOX.5(PWM_C)       33  | 34    GND
     GPIOX6 , GPIOX19,   // GPIOX.6(PWM_D)       35  | 36    GPIOX.19
     UNUSED , UNUSED ,   // ADC.AIN3             37  | 38    1.8V REF OUT
     UNUSED , UNUSED     // GND                  39  | 40    ADC.AIN2
    // clang-format on
};

const bool is_available_phy[LAST_PHY_PIN + 1] = {
    // clang-format off
     false,
     false, false,   // 3.3V                 1   | 2     5.0V
     true , false,   // GPIOX.17(I2C-2_SDA)  3   | 4     5.0V
     true , false,   // GPIOX.18(I2C-2_SCL)  5   | 6     GND
     true , true ,   // GPIOA.13             7   | 8     GPIOX.12(UART_TX_B)
     false, true ,   // GND                  9   | 10    GPIOX.13(UART_RX_B)
     true , true ,   // GPIOX.3              11  | 12    GPIOX.16(PWM_E)
     true , false,   // GPIOX.4              13  | 14    GND
     true , true ,   // GPIOX.7(PWM_F)       15  | 16    GPIOX.0
     false, true ,   // 3.3V                 17  | 18    GPIOX.1
     true , false,   // GPIOX.8(SPI_MOSI)    19  | 20    GND
     true , true ,   // GPIOX.9(SPI_MISO)    21  | 22    GPIOX.2
     true , true ,   // GPIOX.11(SPI_SCLK)   23  | 24    GPIOX.10(SPI_CE0)
     false, true ,   // GND                  25  | 26    GPIOA.4(SPI_CE1)
     true , true ,   // GPIOA.14(I2C-3_SDA)  27  | 28    GPIOA.15(I2C-3_SCL)
     true , false,   // GPIOX.14             29  | 30    GND
     true , true ,   // GPIOX.15             31  | 32    GPIOA.12
     true , false,   // GPIOX.5(PWM_C)       33  | 34    GND
     true , true ,   // GPIOX.6(PWM_D)       35  | 36    GPIOX.19
     true , false,   // ADC.AIN3             37  | 38    1.8V REF OUT
     false, true     // GND                  39  | 40    ADC.AIN2
    // clang-format on
};
}    // namespace lot