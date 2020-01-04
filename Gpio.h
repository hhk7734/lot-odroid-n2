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

#include "lot.h"

namespace lot
{
class Gpio
{
public:
    Gpio( int pin );
    ~Gpio();

    void       mode( pin_mode_t pin_mode );
    pin_mode_t mode( void );
    void       pull_up_down( pud_mode_t pud );
    pud_mode_t pull_up_down( void );
    void       drive( uint32_t pin_drive );
    uint32_t   drive( void );

    void digital( int status );
    int  digital( void );
    void on( void );
    void off( void );
    int  toggle( void );

    void analog( int value );
    int  analog( void );

private:
    static bool m_is_init;
    const int   m_pin;
    pin_mode_t  m_mode;
};
}    // namespace lot

#include "Gpio.hpp"