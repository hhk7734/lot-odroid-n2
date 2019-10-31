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

#include "lot-API/ISpi.h"

namespace lot
{
class Spi : public ISpi
{
public:
    Spi( uint16_t bus_num );
    ~Spi();

    void    init( uint32_t clock, spi_mode_t mode, bit_order_t bit_order );
    void    set_clock( uint32_t clock );
    void    set_mode( spi_mode_t mode );
    void    set_bit_order( bit_order_t bit_order );
    void    transceive( uint8_t *tx_buffer, uint8_t *rx_buffer, uint16_t size );
    void    transceive( pin_size_t chip_select,
                        uint8_t *  tx_buffer,
                        uint8_t *  rx_buffer,
                        uint16_t   size );
    uint8_t transceive( uint8_t data );
    uint8_t transceive( pin_size_t chip_select, uint8_t data );
    void write_reg( uint8_t register_address, uint8_t *buffer, uint16_t size );
    void write_reg( pin_size_t chip_select,
                    uint8_t    register_address,
                    uint8_t *  buffer,
                    uint8_t    size );
    void write_reg( uint8_t register_address, uint8_t data );
    void write_reg( pin_size_t chip_select,
                    uint8_t    register_address,
                    uint8_t    data );
    void read_reg( uint8_t register_address, uint8_t *buffer, uint16_t size );
    void read_reg( pin_size_t chip_select,
                   uint8_t    register_address,
                   uint8_t *  buffer,
                   uint16_t   size );
    uint8_t read_reg( uint8_t register_address );
    uint8_t read_reg( pin_size_t chip_select, uint8_t register_address );
};

}    // namespace lot