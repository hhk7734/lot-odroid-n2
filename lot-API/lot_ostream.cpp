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

#include "lot_ostream.h"
#include <math.h>

namespace lot
{
basic_ostream &basic_ostream::print( int32_t value )
{
    if( value < 0 )
    {
        print( '-' );
        value = -value;
    }

    return print( static_cast<uint32_t>( value ) );
}

basic_ostream &basic_ostream::print( uint32_t value )
{
    char     buf[33];
    char *   str = &buf[32];
    uint32_t temp;

    *str = '\0';


    switch( ios_base::flags() & ios_base::basefield )
    {
        case ios_base::oct:
            do
            {
                temp           = value / 8;
                char remainder = ( value - temp * 8 ) + '0';
                *--str         = remainder;
                value          = temp;
            } while( value );
            break;
        case ios_base::dec:
            do
            {
                temp           = value / 10;
                char remainder = ( value - temp * 10 ) + '0';
                *--str         = remainder;
                value          = temp;
            } while( value );
            break;
        case ios_base::hex:
            do
            {
                temp           = value / 16;
                char remainder = ( value - temp * 16 );
                if( remainder < 10 )
                {
                    remainder += '0';
                }
                else
                {
                    remainder = remainder - 10 + 'A';
                }
                *--str = remainder;
                value  = temp;
            } while( value );
            break;
    }

    return print( str );
}

basic_ostream &basic_ostream::print( int64_t value )
{
    if( value < 0 )
    {
        print( '-' );
        value = -value;
    }

    return print( static_cast<uint64_t>( value ) );
}

basic_ostream &basic_ostream::print( uint64_t value )
{
    char     buf[65];
    char *   str = &buf[64];
    uint64_t temp;

    *str = '\0';


    switch( ios_base::flags() & ios_base::basefield )
    {
        case ios_base::oct:
            do
            {
                temp           = value / 8;
                char remainder = ( value - temp * 8 ) + '0';
                *--str         = remainder;
                value          = temp;
            } while( value );
            break;
        case ios_base::dec:
            do
            {
                temp           = value / 10;
                char remainder = ( value - temp * 10 ) + '0';
                *--str         = remainder;
                value          = temp;
            } while( value );
            break;
        case ios_base::hex:
            do
            {
                temp           = value / 16;
                char remainder = ( value - temp * 16 );
                if( remainder < 10 )
                {
                    remainder += '0';
                }
                else
                {
                    remainder = remainder - 10 + 'A';
                }
                *--str = remainder;
                value  = temp;
            } while( value );
            break;
    }

    return print( str );
}

basic_ostream &basic_ostream::print( float value )
{
    if( value < 0.0 )
    {
        print( '-' );
        value = -value;
    }

    float      rounding = 0.5;
    streamsize size     = ios_base::precision();
    for( streamsize i = 0; i < size; ++i )
    {
        rounding /= 10.0;
    }
    value += rounding;

    uint32_t _int = static_cast<uint32_t>( value );
    print( _int );
    print( '.' );

    float _dec = value - static_cast<float>( _int );

    while( size-- > 0 )
    {
        _dec *= 10.0;
        char c = static_cast<char>( _dec );
        _dec -= c;
        c += '0';
        print( c );
    }

    return *this;
}

basic_ostream &basic_ostream::print( double value )
{
    if( value < 0.0 )
    {
        print( '-' );
        value = -value;
    }

    double     rounding = 0.5;
    streamsize size     = ios_base::precision();
    for( streamsize i = 0; i < size; ++i )
    {
        rounding /= 10.0;
    }
    value += rounding;

    uint64_t _int = static_cast<uint64_t>( value );
    print( _int );
    print( '.' );

    double _dec = value - static_cast<double>( _int );

    while( size-- > 0 )
    {
        _dec *= 10.0;
        char c = static_cast<char>( _dec );
        _dec -= c;
        c += '0';
        print( c );
    }

    return *this;
}
}    // namespace lot