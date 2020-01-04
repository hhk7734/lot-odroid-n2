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

#include "lot_iostream.h"

/**
 * UART_XYZ \n
 *      @arg X: data bits; 5, 6, 7, 8 \n
 *      @arg Y: parity bits; N: None, E: Even, O: Odd, M: Mark, S: Space \n
 *      @arg Z: stop bits; 1, 2
 */

namespace lot
{
class IUart : public iostream
{
public:
    typedef enum
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
    } uart_mode_t;

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
    virtual uint8_t receive( void ) = 0;
};

}    // namespace lot