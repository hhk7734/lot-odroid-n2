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
Log::log_level_t Log::m_log_level = WARNING;
const char       Log::m_log_msg[4][12]
    = { "[DEBUG]  : ", "[INFO]   : ", "[WARNING]: ", "[ERROR]  : " };

void Log::set_log_level( log_level_t level )
{
    m_log_level = level;
}

void Log::debug( const char *fmt, ... )
{
    va_list args;
    va_start( args, fmt );
    print( DEBUG, fmt, args );
    va_end( args );
}

void Log::info( const char *fmt, ... )
{
    va_list args;
    va_start( args, fmt );
    print( INFO, fmt, args );
    va_end( args );
}

void Log::warning( const char *fmt, ... )
{
    va_list args;
    va_start( args, fmt );
    print( WARNING, fmt, args );
    va_end( args );
}

void Log::error( const char *fmt, ... )
{
    va_list args;
    va_start( args, fmt );
    print( ERROR, fmt, args );
    va_end( args );
}
}    // namespace lot
