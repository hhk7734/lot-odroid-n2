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

#include "lot_def.h"

/**
 * UART_XYZ \n
 *      @arg X: data bits; 5, 6, 7, 8 \n
 *      @arg Y: parity bits; N: None, E: Even, O: Odd, M: Mark, S: Space \n
 *      @arg Z: stop bits; 1, 2
 */
typedef enum
{
    UART_5N1 = 0,
    UART_6N1,
    UART_7N1,
    UART_8N1,
    UART_5N2,
    UART_6N2,
    UART_7N2,
    UART_8N2,
    UART_5E1,
    UART_6E1,
    UART_7E1,
    UART_8E1,
    UART_5E2,
    UART_6E2,
    UART_7E2,
    UART_8E2,
    UART_5O1,
    UART_6O1,
    UART_7O1,
    UART_8O1,
    UART_5O2,
    UART_6O2,
    UART_7O2,
    UART_8O2,
    UART_5M1,
    UART_6M1,
    UART_7M1,
    UART_8M1,
    UART_5M2,
    UART_6M2,
    UART_7M2,
    UART_8M2,
    UART_5S1,
    UART_6S1,
    UART_7S1,
    UART_8S1,
    UART_5S2,
    UART_6S2,
    UART_7S2,
    UART_8S2
} uart_mode_t;

namespace lot
{
class IUart
{
public:
    /**
     * @brief Initializes UART.
     * @param baudrate
     * @param mode \n
     *      This parameter can be a value of @ref uart_mode_t.
     */
    virtual void init( uint32_t baudrate, uart_mode_t mode ) = 0;

    /**
     * @brief Sets buadrate.
     * @param baudrate
     */
    virtual void set_baudrate( uint32_t baudrate ) = 0;

    /**
     * @brief Sets UART mode.
     * @param mode \n
     *      This parameter can be a value of @ref uart_mode_t.
     */
    virtual void set_mode( uart_mode_t mode ) = 0;

    /**
     * @brief Returns the number of data available to be read.
     * @return The number of data.
     */
    virtual uint16_t available( void ) = 0;

    /**
     * @brief Transmits data to another device.
     * @param buffer Pointer to transmission data buffer.
     * @param size The number of data.
     */
    virtual void transmit( uint8_t *buffer, uint16_t size ) = 0;

    /**
     * @brief Transmits data to another device.
     * @param data
     */
    virtual void transmit( uint8_t data ) = 0;

    /**
     * @brief Receives data from another device.
     * @param buffer Pointer to reception data buffer.
     * @param size The number of data.
     */
    virtual void receive( uint8_t *buffer, uint16_t size ) = 0;

    /**
     * @brief Receives data from another device.
     * @return Reception Data.
     */
    virtual uint8_t read( void ) = 0;
};

}    // namespace lot