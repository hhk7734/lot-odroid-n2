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

namespace lot
{
inline basic_ostream &basic_ostream::print( char c )
{
    return put( c );
}

inline basic_ostream &basic_ostream::print( uint8_t c )
{
    return print( static_cast<char>( c ) );
}

inline basic_ostream &basic_ostream::print( const char *str )
{
    return write( str );
}

inline basic_ostream &basic_ostream::print( const uint8_t *str )
{
    return write( reinterpret_cast<const char *>( str ) );
}

inline basic_ostream &basic_ostream::print( int16_t value )
{
    return print( static_cast<int32_t>( value ) );
}

inline basic_ostream &basic_ostream::print( uint16_t value )
{
    return print( static_cast<uint32_t>( value ) );
}

template<typename T>
inline basic_ostream &basic_ostream::operator<<( T value )
{
    return print( value );
}

template<>
inline basic_ostream &basic_ostream::
                      operator<<<pf_basic_ostream>( pf_basic_ostream pf )
{
    pf( *this );
    return *this;
}

template<>
inline basic_ostream &basic_ostream::operator<<<pf_ios_base>( pf_ios_base pf )
{
    pf( *this );
    return *this;
}

inline basic_ostream &endl( basic_ostream &os )
{
    return os.print( "\r\n" );
}
}    // namespace lot