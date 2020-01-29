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

#include "lot-API/ISpi.h"

namespace lot
{
class Spi : public ISpi
{
public:
    /**
     * @brief Creates an instance of Spi class and initializes SPI. \n
     *      /dev/spidevB.C B == bus_num, C == chip_select.
     * @param bus_num
     * @param chip_select
     */
    Spi( uint16_t bus_num, uint16_t chip_select );

    /**
     * @brief Creates an instance of Spi class and initializes SPI. \n
     *      /dev/spidevB.C B == bus_num, C == chip_select.
     * @param device Device node name.
     */
    Spi( const char *device );
    ~Spi();

    void clock( uint32_t spi_clock ) override;
    void mode( spi_mode_t spi_mode ) override;
    void bit_order( bit_order_t spi_bit_order ) override;

    void    transceive( uint8_t *tx_buffer,
                        uint8_t *rx_buffer,
                        uint16_t size ) override;
    void    transceive( uint8_t *tx_buffer,
                        uint8_t *rx_buffer,
                        uint16_t size,
                        int      cs_pin ) override;
    uint8_t transceive( uint8_t data ) override;
    uint8_t transceive( uint8_t data, int cs_pin ) override;

    void write_reg( uint8_t  register_address,
                    uint8_t *buffer,
                    uint16_t size ) override;
    void write_reg( uint8_t  register_address,
                    uint8_t *buffer,
                    uint16_t size,
                    int      cs_pin ) override;
    void write_reg( uint8_t register_address, uint8_t data ) override;
    void write_reg( uint8_t register_address,
                    uint8_t data,
                    int     cs_pin ) override;

    void    read_reg( uint8_t  register_address,
                      uint8_t *buffer,
                      uint16_t size ) override;
    void    read_reg( uint8_t  register_address,
                      uint8_t *buffer,
                      uint16_t size,
                      int      cs_pin ) override;
    uint8_t read_reg( uint8_t register_address ) override;
    uint8_t read_reg( uint8_t register_address, int cs_pin ) override;

private:
    char    m_device[30];
    int     m_fd;
    uint8_t m_spi_mode;

    void init( void );
};

}    // namespace lot