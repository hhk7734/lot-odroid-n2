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
#include "lotdef.h"

namespace lot
{
class IUart : public iostream
{
public:
    /**
     * @brief Deletes instance of IUart class.
     */
    virtual ~IUart()
    {
    }

    /**
     * @brief Sets buadrate.
     * @param baud_rate
     */
    virtual void baudrate( uint32_t baud_rate ) = 0;

    /**
     * @brief Sets UART mode.
     * @param uart_mode \n
     *      This parameter can be a value of @ref UartMode.
     */
    virtual void mode( UartMode uart_mode ) = 0;

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