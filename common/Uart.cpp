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

#include "../Uart.h"
#include "../lot.h"

#include <stdio.h>     // sprintf()
#include <unistd.h>    // write(), close(), usleep()
#include <string.h>    // strcpy(), strlen()
#include <fcntl.h>     // open(), fcntl()
#include <termios.h>
#include <sys/ioctl.h>    // ioctl()
#include <errno.h>        // errno
#include <stdexcept>

static inline ssize_t unistd_write( int fd, const void *buf, size_t n )
{
    return write( fd, buf, n );
}

namespace lot
{
Uart::Uart( uint16_t bus_num )
    : m_fd( -1 )
{
    sprintf( m_device, "%s%d", "/dev/ttyS", bus_num );
}

Uart::Uart( const char *device )
    : m_fd( -1 )
{
    if( device != NULL )
    {
        strcpy( m_device, device );
    }
}

Uart::~Uart()
{
    close( m_fd );
}

void Uart::init( uint32_t baudrate, uart_mode_t mode )
{
    if( m_fd > 0 )
    {
        close( m_fd );
    }

    // No controlling tty, Enables nonblocking mode.
    m_fd = open( m_device, O_RDWR | O_NOCTTY | O_NONBLOCK );
    if( m_fd < 0 )
    {
        Log::error( "Failed to open %s.\r\n", m_device );
        throw std::runtime_error( strerror( errno ) );
    }

    // Explicit reset due to O_NONBLOCK.
    fcntl( m_fd, F_SETFL, O_RDWR );

    set_baudrate( baudrate );

    set_mode( mode );
}

void Uart::set_baudrate( uint32_t baudrate )
{
    struct termios options;
    speed_t        baud_rate = B0;

    // clang-format off
    switch( baudrate )
    {
        case 50:        baud_rate = B50;        break;
        case 75:        baud_rate = B75;        break;
        case 110:       baud_rate = B110;       break;
        case 134:       baud_rate = B134;       break;
        case 150:       baud_rate = B150;       break;
        case 200:       baud_rate = B200;       break;
        case 300:       baud_rate = B300;       break;
        case 600:       baud_rate = B600;       break;
        case 1200:      baud_rate = B1200;      break;
        case 1800:      baud_rate = B1800;      break;
        case 2400:      baud_rate = B2400;      break;
        case 4800:      baud_rate = B4800;      break;
        case 9600:      baud_rate = B9600;      break;
        case 19200:     baud_rate = B19200;     break;
        case 38400:     baud_rate = B38400;     break;
        case 57600:     baud_rate = B57600;     break;
        case 115200:    baud_rate = B115200;    break;
        case 230400:    baud_rate = B230400;    break;
        case 460800:    baud_rate = B460800;    break;
        case 500000:    baud_rate = B500000;    break;
        case 576000:    baud_rate = B576000;    break;
        case 921600:    baud_rate = B921600;    break;
        case 1000000:   baud_rate = B1000000;   break;
        case 1152000:   baud_rate = B1152000;   break;
        case 1500000:   baud_rate = B1500000;   break;
        case 2000000:   baud_rate = B2000000;   break;
        case 2500000:   baud_rate = B2500000;   break;
        case 3000000:   baud_rate = B3000000;   break;
        case 3500000:   baud_rate = B3500000;   break;
        case 4000000:   baud_rate = B4000000;   break;
        default:
            baud_rate = B115200;
            Log::warning( "The baudrate is invalid. It will set default buadrate(115200).\r\n" );
            break;
    };
    // clang-format on

    tcgetattr( m_fd, &options );

    cfsetispeed( &options, baud_rate );
    cfsetospeed( &options, baud_rate );

    tcsetattr( m_fd, TCSANOW, &options );

    usleep( 10000 );
}

void Uart::set_mode( uart_mode_t mode )
{
    struct termios options;

    tcgetattr( m_fd, &options );

    // Raw level read/write. Non-standard.
    cfmakeraw( &options );

    options.c_cc[VMIN]  = 0;
    options.c_cc[VTIME] = 100;    // timeout = 10s

    // Ignore Error.
    options.c_iflag |= IGNPAR;

    // Disable implementation-defined output processing.
    options.c_oflag &= ~OPOST;

    options.c_cflag |= ( CLOCAL | CREAD );

    options.c_cflag &= ~CSIZE;
    switch( mode % 4 )
    {
        case 0:
            options.c_cflag |= CS5;
        case 1:
            options.c_cflag |= CS6;
        case 2:
            options.c_cflag |= CS7;
        case 3:
            options.c_cflag |= CS8;
    }

    switch( static_cast<uint8_t>( mode / 8 ) )
    {
        case 0:
            // None
            options.c_cflag &= ~PARENB;
            options.c_iflag &= ~INPCK;
            break;
        case 1:
            // Even
            options.c_iflag |= INPCK;
            options.c_cflag |= PARENB;
            options.c_cflag &= ~PARODD;
            break;
        case 2:
            // Odd
            options.c_iflag |= INPCK;
            options.c_cflag |= PARENB;
            options.c_cflag |= PARODD;
            break;
        case 3:
            // Mark
            break;
        case 4:
            // Space
            break;
    }

    switch( static_cast<uint8_t>( mode / 4 ) % 2 )
    {
        case 0:
            options.c_cflag &= ~CSTOPB;
            break;
        case 1:
            options.c_cflag |= CSTOPB;
            break;
    }

    options.c_lflag &= ~( ISIG | ICANON | ECHO | ECHOE );

    tcsetattr( m_fd, TCSANOW, &options );

    usleep( 10000 );
}

uint16_t Uart::available( void )
{
    int result;

    if( ioctl( m_fd, FIONREAD, &result ) < 0 )
    {
        Log::warning( "Failed to read UART RX buffer size.\r\n" );
        return 0;
    }

    return result;
}

void Uart::transmit( uint8_t *buffer, uint16_t size )
{
    unistd_write( m_fd, buffer, size );
}

void Uart::transmit( uint8_t data )
{
    unistd_write( m_fd, &data, 1 );
}

void Uart::receive( uint8_t *buffer, uint16_t size )
{
    if( read( m_fd, buffer, size ) != size )
    {
        Log::warning( "Failed to read UART RX buffer.\r\n" );
    }
}

uint8_t Uart::receive( void )
{
    uint8_t data;

    receive( &data, 1 );

    return data;
}
}    // namespace lot
