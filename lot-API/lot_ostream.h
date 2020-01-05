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

#include "lot_ios.h"

namespace lot
{
class basic_ostream;

typedef basic_ostream ostream;

typedef ios_base &( *pf_ios_base )( ios_base & );
typedef basic_ostream &( *pf_basic_ostream )( basic_ostream & );


class basic_ostream : public ios
{
public:
    virtual basic_ostream &put( char c ) = 0;

    virtual basic_ostream &write( const char *str, uint16_t size ) = 0;
    virtual basic_ostream &write( const char *str )                = 0;

    basic_ostream &print( char c );
    basic_ostream &print( uint8_t value );
    basic_ostream &print( const char *str );
    basic_ostream &print( const uint8_t *str );

    basic_ostream &print( int16_t value );
    basic_ostream &print( uint16_t value );
    basic_ostream &print( int32_t value );
    basic_ostream &print( uint32_t value );
    basic_ostream &print( int64_t value );
    basic_ostream &print( uint64_t value );

    basic_ostream &print( float value );
    basic_ostream &print( double value );

    template<typename T>
    basic_ostream &operator<<( T value );

private:
};

}    // namespace lot

#include "lot_ostream.hpp"