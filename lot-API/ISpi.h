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
class ISpi
{
public:
    /**
     * @brief Deletes instance of ISpi class.
     */
    virtual ~ISpi()
    {
    }

    /**
     * @brief Sets clock in hertz.
     * @param spi_clock
     */
    virtual void clock( uint32_t spi_clock ) = 0;

    /**
     * @brief Sets SPI mode.
     * @param spi_mode \n
     *      This parameter can be a value of @ref spi_mode_t.
     */
    virtual void mode( spi_mode_t spi_mode ) = 0;

    /**
     * @brief Sets bit-order.
     * @param spi_bit_order \n
     *      This parameter can be a value of @ref bit_order_t.
     */
    virtual void bit_order( bit_order_t spi_bit_order ) = 0;

    /**
     * @brief Transmits and Receives data at the same time.
     * @param tx_buffer Pointer to transmission data buffer.
     * @param rx_buffer Pointer to reception data buffer.
     * @param size The number of data to be transceived.
     */
    virtual void
        transceive( uint8_t *tx_buffer, uint8_t *rx_buffer, uint16_t size )
        = 0;

    /**
     * @brief Transmits and Receives data at the same time.
     * @param tx_buffer Pointer to transmission data buffer.
     * @param rx_buffer Pointer to reception data buffer.
     * @param size The number of data to be transceived.
     * @param cs_pin
     */
    virtual void transceive( uint8_t *tx_buffer,
                             uint8_t *rx_buffer,
                             uint16_t size,
                             int      cs_pin );

    /**
     * @brief Transmits and Receives data at the same time.
     * @param data Transmission data.
     * @return Reception data.
     */
    virtual uint8_t transceive( uint8_t data ) = 0;

    /**
     * @brief Transmits and Receives data at the same time.
     * @param data Transmission data.
     * @param cs_pin
     * @return Reception data.
     */
    virtual uint8_t transceive( uint8_t data, int cs_pin );

    /**
     * @brief Writes data to multiple registers of a slave device.
     * @param register_address
     * @param buffer Pointer to data buffer.
     * @param size The number of data.
     */
    virtual void
        write_reg( uint8_t register_address, uint8_t *buffer, uint16_t size )
        = 0;

    /**
     * @brief Writes data to multiple registers of a slave device.
     * @param register_address
     * @param buffer Pointer to data buffer.
     * @param size The number of data.
     * @param cs_pin
     */
    virtual void write_reg( uint8_t  register_address,
                            uint8_t *buffer,
                            uint16_t size,
                            int      cs_pin );

    /**
     * @brief Writes data to a register of a slave device.
     * @param register_address
     * @param data
     */
    virtual void write_reg( uint8_t register_address, uint8_t data ) = 0;

    /**
     * @brief Writes data to a register of a slave device.
     * @param register_address
     * @param data
     * @param cs_pin
     */
    virtual void
        write_reg( uint8_t register_address, uint8_t data, int cs_pin );

    /**
     * @brief Reads data from multiple registers of a slave device.
     * @param register_address
     * @param buffer Pointer to data buffer.
     * @param size The number of data.
     */
    virtual void
        read_reg( uint8_t register_address, uint8_t *buffer, uint16_t size )
        = 0;

    /**
     * @brief Reads data from multiple registers of a slave device.
     * @param register_address
     * @param buffer Pointer to data buffer.
     * @param size The number of data.
     * @param cs_pin
     */
    virtual void read_reg( uint8_t  register_address,
                           uint8_t *buffer,
                           uint16_t size,
                           int      cs_pin );

    /**
     * @brief Reads data from a register of a slave device.
     * @param register_address
     * @return Data read from the register.
     */
    virtual uint8_t read_reg( uint8_t register_address ) = 0;

    /**
     * @brief Reads data from a register of a slave device.
     * @param register_address
     * @param cs_pin
     * @return Data read from the register.
     */
    virtual uint8_t read_reg( uint8_t register_address, int cs_pin );
};
}    // namespace lot

#include "ISpi.hpp"