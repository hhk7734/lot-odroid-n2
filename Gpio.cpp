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

#include "Gpio.h"
#include "lot.h"

namespace lot
{
bool Gpio::m_is_init = false;

Gpio::Gpio( int pin )
    : IGpio( pin )
{
    if( m_is_init == false )
    {
        gpio::init();
        m_is_init = true;
    }

    if( !is_available_phy[pin] )
    {
        Log::error( "Used unavailable pin %d.\r\n", pin );
        throw std::invalid_argument( "Check pin number and functions." );
    }

    m_mode = gpio::mode( pin );
}

Gpio::~Gpio()
{
}
}    // namespace lot