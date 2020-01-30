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

#include <stdarg.h>
#include <stdexcept>

#include "lotdef.h"

namespace lot
{
class unsupported_error : public std::exception
{
private:
    const char *m_what_arg;

public:
    explicit unsupported_error( const std::string &what_arg )
        : m_what_arg( what_arg.c_str() )
    {
    }
    explicit unsupported_error( const char *what_arg )
        : m_what_arg( what_arg )
    {
    }
    virtual const char *what() const throw()
    {
        return m_what_arg;
    }
};

class Log
{
public:
    /**
     * @brief Sets log level.
     * @param level \n
     *      This parameter can be a value of @ref LogLevel.
     */
    static void log_level( LogLevel level );

    /**
     * @brief Prints debug message.
     * @param fmt
     * @param variable_argument
     */
    static void debug( const char *fmt, ... );

    /**
     * @brief Prints info message.
     * @param fmt
     * @param variable_argument
     */
    static void info( const char *fmt, ... );

    /**
     * @brief Prints warning message.
     * @param fmt
     * @param variable_argument
     */
    static void warning( const char *fmt, ... );

    /**
     * @brief Prints error message.
     * @param fmt
     * @param variable_argument
     */
    static void error( const char *fmt, ... );

private:
    static LogLevel   m_log_level;
    static const char m_log_msg[4][12];

    /**
     * @brief Prints message according to log level.
     * @param level \n
     *      This parameter can be a value of @ref LogLevel.
     * @param fmt
     * @param args @ref va_list
     */
    static void print( LogLevel level, const char *fmt, va_list args );
};
}    // namespace lot
