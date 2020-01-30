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

#include "../Spi.h"
#include "../lot.h"

#include <stdio.h>     // sprintf()
#include <unistd.h>    // close()
#include <fcntl.h>     // open()
#include <string.h>    // strcpy(), memset(), memcpy()
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <stdlib.h>    // malloc(), free()
#include <errno.h>     // errno
#include <stdexcept>

#define SPI_READ_REG_FLAG 0x80
#define SPI_WRITE_REG_FLAG 0x00

namespace lot
{
Spi::Spi( uint16_t bus_num, uint16_t chip_select )
    : m_fd( -1 )
    , m_spi_mode( 0 )
{
    sprintf( m_device, "%s%d.%d", "/dev/spidev", bus_num, chip_select );
    init();
}

Spi::Spi( const char *device )
    : m_fd( -1 )
    , m_spi_mode( 0 )
{
    if( device != NULL )
    {
        strcpy( m_device, device );
    }
    init();
}

Spi::~Spi()
{
    close( m_fd );
}

void Spi::clock( uint32_t spi_clock )
{
    if( ioctl( m_fd, SPI_IOC_WR_MAX_SPEED_HZ, &spi_clock ) < 0 )
    {
        Log::warning( "Failed to set SPI clock speed.\r\n" );
    }
}

void Spi::mode( SpiMode spi_mode )
{
    m_spi_mode &= ~0x03;
    m_spi_mode |= spi_mode;
    if( ioctl( m_fd, SPI_IOC_WR_MODE, &m_spi_mode ) < 0 )
    {
        Log::warning( "Failed to set SPI mode.\r\n" );
    }
}

void Spi::bit_order( BitOrder bit_order )
{
    m_spi_mode &= ~SPI_LSB_FIRST;
    if( bit_order == SPI_LSB_FIRST )
    {
        m_spi_mode |= SPI_LSB_FIRST;
    }

    if( ioctl( m_fd, SPI_IOC_WR_MODE, &m_spi_mode ) < 0 )
    {
        Log::warning( "Failed to set SPI bit odrder.\r\n" );
    }
}

void Spi::transceive( uint8_t *tx_buffer, uint8_t *rx_buffer, uint16_t size )
{
    struct spi_ioc_transfer spi;
    memset( &spi, 0, sizeof( spi ) );

    spi.tx_buf = ( unsigned long )tx_buffer;
    spi.rx_buf = ( unsigned long )rx_buffer;
    spi.len    = size;

    ioctl( m_fd, SPI_IOC_MESSAGE( 1 ), &spi );
}

uint8_t Spi::transceive( uint8_t data )
{
    uint8_t temp = data;
    transceive( &temp, &temp, 1 );
    return temp;
}

void Spi::write_reg( uint8_t register_address, uint8_t *buffer, uint16_t size )
{
    uint8_t *temp = ( uint8_t * )malloc( size + 1 );
    temp[0]       = register_address | SPI_WRITE_REG_FLAG;
    memcpy( temp + 1, buffer, size );

    transceive( temp, temp, size + 1 );

    free( temp );
}

void Spi::write_reg( uint8_t register_address, uint8_t data )
{
    uint8_t temp[2];
    temp[0] = register_address | SPI_WRITE_REG_FLAG;
    temp[1] = data;

    transceive( temp, temp, 2 );
}

void Spi::read_reg( uint8_t register_address, uint8_t *buffer, uint16_t size )
{
    uint8_t *temp = ( uint8_t * )malloc( size + 1 );
    memset( temp, 0, size + 1 );
    temp[0] = register_address | SPI_READ_REG_FLAG;

    transceive( temp, temp, size + 1 );
    memcpy( buffer, temp + 1, size );

    free( temp );
}

uint8_t Spi::read_reg( uint8_t register_address )
{
    uint8_t temp[2];
    temp[0] = register_address | SPI_READ_REG_FLAG;
    temp[1] = 0;

    transceive( temp, temp, 2 );
    return temp[1];
}

void Spi::init( void )
{
    m_fd = open( m_device, O_RDWR );
    if( m_fd < 0 )
    {
        Log::error( "Failed to open %s.\r\n", m_device );
        throw std::runtime_error( strerror( errno ) );
    }

    clock( 1000000 );
    mode( lot::MODE0 );
    bit_order( lot::MSB_FIRST );

    uint8_t spi_BPW = 0;    // means 8 bits
    if( ioctl( m_fd, SPI_IOC_WR_BITS_PER_WORD, &spi_BPW ) < 0 )
    {
        Log::warning( "Failed to set SPI bits per word.\r\n" );
    }
}
}    // namespace lot