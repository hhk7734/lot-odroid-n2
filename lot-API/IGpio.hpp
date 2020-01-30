/*
 * MIT License
 * 
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

#include "IGpio.h"
#include "Log.h"
#include "lot_gpio.h"

namespace lot
{
static void pin_mode_error( int pin, const char *mode, const char *func )
{
    Log::error( "Called %s() when %d's mode is not %s.\r\n", func, pin, mode );
    throw std::invalid_argument( func );
}

inline void IGpio::mode( GpioMode pin_mode )
{
    gpio::mode( m_pin, pin_mode );
    m_mode = pin_mode;
}

inline GpioMode IGpio::mode( void )
{
    return gpio::mode( m_pin );
}

inline void IGpio::pull_up_down( PUDMode pud )
{
    gpio::pull_up_down( m_pin, pud );
}

inline PUDMode IGpio::pull_up_down( void )
{
    return gpio::pull_up_down( m_pin );
}

inline void IGpio::drive( uint32_t pin_drive )
{
    gpio::drive( m_pin, pin_drive );
}

inline uint32_t IGpio::drive( void )
{
    return gpio::drive( m_pin );
}

inline void IGpio::digital( int status )
{
    if( m_mode == DOUT )
    {
        gpio::digital( m_pin, status );
        return;
    }
    pin_mode_error( m_pin, "DOUT", __func__ );
}

inline int IGpio::digital( void )
{
    return gpio::digital( m_pin );
}

inline void IGpio::on( void )
{
    digital( HIGH );
}

inline void IGpio::off( void )
{
    digital( LOW );
}

inline int IGpio::toggle( void )
{
    if( digital() )
    {
        digital( LOW );
        return LOW;
    }
    else
    {
        digital( HIGH );
        return HIGH;
    }
}

inline void IGpio::analog( int value )
{
    if( m_mode == AOUT )
    {
        gpio::analog( m_pin, value );
        return;
    }
    pin_mode_error( m_pin, "AOUT", __func__ );
}

inline int IGpio::analog( void )
{
    if( m_mode == AIN )
    {
        return gpio::analog( m_pin );
    }
    pin_mode_error( m_pin, "AIN", __func__ );
    return -1;
}
}    // namespace lot