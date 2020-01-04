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

#include "lot-API/IUart.h"

#include <string.h>    // strcpy(), strlen()

namespace lot
{
class Uart : public IUart
{
public:
    Uart( uint16_t bus_num );
    Uart( const char *device );
    ~Uart();

    Uart &put( char c );
    Uart &write( const char *str, uint16_t size );
    Uart &write( const char *str );

    void     init( uint32_t baudrate = 115200, uart_mode_t mode = U8N1 );
    void     set_baudrate( uint32_t baudrate );
    void     set_mode( uart_mode_t mode );
    uint16_t available( void );
    void     transmit( uint8_t *buffer, uint16_t size );
    void     transmit( uint8_t data );
    void     receive( uint8_t *buffer, uint16_t size );
    uint8_t  receive( void );

private:
    char m_device[30];
    int  m_fd;
};

inline Uart &Uart::put( char c )
{
    transmit( static_cast<uint8_t>( c ) );
    return *this;
}

inline Uart &Uart::write( const char *str, uint16_t size )
{
    transmit( reinterpret_cast<uint8_t *>( const_cast<char *>( str ) ), size );
    return *this;
}

inline Uart &Uart::write( const char *str )
{
    transmit( reinterpret_cast<uint8_t *>( const_cast<char *>( str ) ),
              strlen( str ) );
    return *this;
}
}    // namespace lot