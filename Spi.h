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
    // /dev/spidevB.C B == bus_num, C == chip_select
    Spi( uint16_t bus_num, uint16_t chip_select );
    Spi( const char *device );
    ~Spi();

    void    init( uint32_t    clock     = 1000000,
                  spi_mode_t  mode      = MODE0,
                  bit_order_t bit_order = MSB_FIRST );
    void    set_clock( uint32_t clock );
    void    set_mode( spi_mode_t mode );
    void    set_bit_order( bit_order_t bit_order );
    void    transceive( uint8_t *tx_buffer, uint8_t *rx_buffer, uint16_t size );
    void    transceive( int      cs_pin,
                        uint8_t *tx_buffer,
                        uint8_t *rx_buffer,
                        uint16_t size );
    uint8_t transceive( uint8_t data );
    uint8_t transceive( int cs_pin, uint8_t data );
    void write_reg( uint8_t register_address, uint8_t *buffer, uint16_t size );
    void write_reg( int      cs_pin,
                    uint8_t  register_address,
                    uint8_t *buffer,
                    uint8_t  size );
    void write_reg( uint8_t register_address, uint8_t data );
    void write_reg( int cs_pin, uint8_t register_address, uint8_t data );
    void read_reg( uint8_t register_address, uint8_t *buffer, uint16_t size );
    void read_reg( int      cs_pin,
                   uint8_t  register_address,
                   uint8_t *buffer,
                   uint16_t size );
    uint8_t read_reg( uint8_t register_address );
    uint8_t read_reg( int cs_pin, uint8_t register_address );

private:
    char    m_device[30];
    int     m_fd;
    uint8_t m_mode;
};

}    // namespace lot