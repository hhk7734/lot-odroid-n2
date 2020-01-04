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

#include "lotdef.h"

namespace lot
{
class II2c
{
public:
    /**
     * @brief Initializes I2C.
     * @param clock
     */
    virtual void init( uint32_t clock ) = 0;

    /**
     * @brief Sets clock in hertz.
     * @param clock
     */
    virtual void set_clock( uint32_t clock ) = 0;

    /**
     * @brief Transmits data to a slave device.
     * @param slave_address
     * @param buffer Pointer to transmission data buffer.
     * @param size The number of data.
     */
    virtual void
        transmit( uint8_t slave_address, uint8_t *buffer, uint16_t size )
        = 0;

    /**
     * @brief Transmits data to a slave device.
     * @param slave_address
     * @param data
     */
    virtual void transmit( uint8_t slave_address, uint8_t data ) = 0;

    /**
     * @brief Receives data from a slave device.
     * @param slave_address
     * @param buffer Pointer to reception data buffer.
     * @param size The number of data.
     */
    virtual void
        receive( uint8_t slave_address, uint8_t *buffer, uint16_t size )
        = 0;

    /**
     * @brief Receives data from a slave device.
     * @param slave_address
     * @return Reception data
     */
    virtual uint8_t receive( uint8_t slave_address ) = 0;

    /**
     * @brief Writes data to multiple registers of a slave device.
     * @param slave_address
     * @param register_address
     * @param buffer Pointer to data buffer.
     * @param size The number of data.
     */
    virtual void write_reg( uint8_t  slave_address,
                            uint8_t  register_address,
                            uint8_t *buffer,
                            uint8_t  size )
        = 0;

    /**
     * @brief Writes data to a register of a slave device.
     * @param slave_address
     * @param register_address
     * @param data
     */
    virtual void write_reg( uint8_t slave_address,
                            uint8_t register_address,
                            uint8_t data )
        = 0;

    /**
     * @brief Reads data from multiple registers of a slave device.
     * @param slave_address
     * @param register_address
     * @param buffer Pointer to data buffer.
     * @param size The number of data.
     */
    virtual void read_reg( uint8_t  slave_address,
                           uint8_t  register_address,
                           uint8_t *buffer,
                           uint16_t size )
        = 0;

    /**
     * @brief Reads data from a register of a slave device.
     * @param slave_address
     * @param register_address
     * @return Reception data
     */
    virtual uint8_t read_reg( uint8_t slave_address, uint8_t register_address )
        = 0;
};

}    // namespace lot
