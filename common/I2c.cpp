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

#include "../I2c.h"
#include "../lot.h"

#include <stdio.h>     // sprintf()
#include <unistd.h>    // close()
#include <fcntl.h>     // open()
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>    // ioctl()
#include <stdlib.h>       // malloc(), free()
#include <string.h>       // strcpy(), memcpy()
#include <errno.h>        // errno
#include <stdexcept>

namespace lot
{
I2c::I2c( uint16_t bus_num )
    : m_fd( -1 )
{
    sprintf( m_device, "%s%d", "/dev/i2c-", bus_num );
}

I2c::I2c( const char *device )
    : m_fd( -1 )
{
    if( device != NULL )
    {
        strcpy( m_device, device );
    }
}

I2c::~I2c()
{
    close( m_fd );
}

void I2c::init( uint32_t i2c_clock )
{
    if( m_fd > 0 )
    {
        close( m_fd );
    }

    m_fd = open( m_device, O_RDWR );
    if( m_fd < 0 )
    {
        Log::error( "Failed to open %s.\r\n", m_device );
        throw std::runtime_error( strerror( errno ) );
    }
}

void I2c::clock( uint32_t i2c_clock )
{
}

void I2c::transmit( uint8_t slave_address, uint8_t *buffer, uint16_t size )
{
    struct i2c_rdwr_ioctl_data i2c;
    struct i2c_msg             msgs;

    msgs.addr  = slave_address;
    msgs.flags = 0;
    msgs.len   = size;
    msgs.buf   = buffer;

    i2c.msgs  = &msgs;
    i2c.nmsgs = 1;

    ioctl( m_fd, I2C_RDWR, &i2c );
}

void I2c::transmit( uint8_t slave_address, uint8_t data )
{
    transmit( slave_address, &data, 1 );
}

void I2c::receive( uint8_t slave_address, uint8_t *buffer, uint16_t size )
{
    struct i2c_rdwr_ioctl_data i2c;
    struct i2c_msg             msgs;

    msgs.addr  = slave_address;
    msgs.flags = I2C_M_RD;    // read
    msgs.len   = size;
    msgs.buf   = buffer;

    i2c.msgs  = &msgs;
    i2c.nmsgs = 1;

    ioctl( m_fd, I2C_RDWR, &i2c );
}

uint8_t I2c::receive( uint8_t slave_address )
{
    uint8_t data;
    receive( slave_address, &data, 1 );
    return data;
}

void I2c::write_reg( uint8_t  slave_address,
                     uint8_t  register_address,
                     uint8_t *buffer,
                     uint8_t  size )
{
    uint8_t *temp = ( uint8_t * )malloc( size + 1 );
    temp[0]       = register_address;
    memcpy( temp + 1, buffer, size );

    transmit( slave_address, temp, size + 1 );

    free( temp );
}

void I2c::write_reg( uint8_t slave_address,
                     uint8_t register_address,
                     uint8_t data )
{
    uint8_t temp[2];
    temp[0] = register_address;
    temp[1] = data;

    transmit( slave_address, temp, 2 );
}

void I2c::read_reg( uint8_t  slave_address,
                    uint8_t  register_address,
                    uint8_t *buffer,
                    uint16_t size )
{
    struct i2c_rdwr_ioctl_data i2c;
    struct i2c_msg             msgs[2];

    msgs[0].addr  = slave_address;
    msgs[0].flags = 0;    // write
    msgs[0].len   = 1;
    msgs[0].buf   = &register_address;

    msgs[1].addr  = slave_address;
    msgs[1].flags = I2C_M_RD;    // read
    msgs[1].len   = size;
    msgs[1].buf   = buffer;

    i2c.msgs  = msgs;
    i2c.nmsgs = 2;

    ioctl( m_fd, I2C_RDWR, &i2c );
}

uint8_t I2c::read_reg( uint8_t slave_address, uint8_t register_address )
{
    uint8_t data;
    read_reg( slave_address, register_address, &data, 1 );
    return data;
}
}    // namespace lot