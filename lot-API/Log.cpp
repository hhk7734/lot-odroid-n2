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

#include "lot-API/Log.h"

namespace lot
{
log_level_t Log::log_level = WARNING;

void Log::set_log_level( log_level_t level )
{
    log_level = level;
}

void Log::debug( const char *str )
{
    if( log_level <= DEBUG )
    {
        print( "[DEBUG]  : " );
        print( str );
        print( "\r\n" );
    }
}

void Log::info( const char *str )
{
    if( log_level <= INFO )
    {
        print( "[INFO]   : " );
        print( str );
        print( "\r\n" );
    }
}

void Log::warning( const char *str )
{
    if( log_level <= WARNING )
    {
        print( "[WARNING]: " );
        print( str );
        print( "\r\n" );
    }
}

void Log::error( const char *str )
{
    if( log_level <= ERROR )
    {
        print( "[ERROR]  : " );
        print( str );
        print( "\r\n" );
    }
}
}    // namespace lot
