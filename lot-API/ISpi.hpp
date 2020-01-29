/*
 * MIT License
 * 
 * Copyright (c) 2020 Hyeonki Hong <hhk7734@gmail.com>
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

#include "ISpi.h"
#include "lot_gpio.h"

namespace lot
{
inline void ISpi::transceive( uint8_t *tx_buffer,
                              uint8_t *rx_buffer,
                              uint16_t size,
                              int      cs_pin )
{
    gpio::digital( cs_pin, LOW );
    transceive( tx_buffer, rx_buffer, size );
    gpio::digital( cs_pin, HIGH );
}

inline uint8_t ISpi::transceive( uint8_t data, int cs_pin )
{
    gpio::digital( cs_pin, LOW );
    uint8_t temp = transceive( data );
    gpio::digital( cs_pin, HIGH );
    return temp;
}

inline void ISpi::write_reg( uint8_t  register_address,
                             uint8_t *buffer,
                             uint16_t size,
                             int      cs_pin )
{
    gpio::digital( cs_pin, LOW );
    write_reg( register_address, buffer, size );
    gpio::digital( cs_pin, HIGH );
}

inline void
    ISpi::write_reg( uint8_t register_address, uint8_t data, int cs_pin )
{
    gpio::digital( cs_pin, LOW );
    write_reg( register_address, data );
    gpio::digital( cs_pin, HIGH );
}

inline void ISpi::read_reg( uint8_t  register_address,
                            uint8_t *buffer,
                            uint16_t size,
                            int      cs_pin )
{
    gpio::digital( cs_pin, LOW );
    read_reg( register_address, buffer, size );
    gpio::digital( cs_pin, HIGH );
}

inline uint8_t ISpi::read_reg( uint8_t register_address, int cs_pin )
{
    gpio::digital( cs_pin, LOW );
    uint8_t temp = read_reg( register_address );
    gpio::digital( cs_pin, HIGH );
    return temp;
}
}    // namespace lot