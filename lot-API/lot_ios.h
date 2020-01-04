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

#include "lotdef.h"

namespace lot
{
typedef uint16_t streamsize;

class ios_base
{
public:
    typedef uint16_t fmtflags;

    static const fmtflags skipws = 0x0001;

    static const fmtflags left     = 0x0002;
    static const fmtflags right    = 0x0004;
    static const fmtflags internal = 0x0008;

    static const fmtflags boolalpha = 0x0010;

    static const fmtflags dec = 0x0020;
    static const fmtflags oct = 0x0040;
    static const fmtflags hex = 0x0080;

    static const fmtflags scientific = 0x0100;
    static const fmtflags fixed      = 0x0200;

    static const fmtflags showbase  = 0x0400;
    static const fmtflags showpoint = 0x0800;
    static const fmtflags showpos   = 0x1000;
    static const fmtflags uppercase = 0x2000;

    static const fmtflags adjustfield = left | right | internal;
    static const fmtflags basefield   = dec | oct | hex;
    static const fmtflags floatfield  = fixed | scientific;

    static const fmtflags unitbuf = 0x4000;

    fmtflags flags( void ) const;
    fmtflags flags( fmtflags fmtfl );

    fmtflags setf( fmtflags fmtfl );
    fmtflags setf( fmtflags fmtfl, fmtflags mask );

    void unsetf( fmtflags mask );

    streamsize precision( void ) const;
    streamsize precision( streamsize prec );

protected:
    ios_base();
    fmtflags   mformat;
    streamsize mprecision;
};

class basic_ios : public ios_base
{
};

typedef basic_ios ios;

}    // namespace lot

#include "lot_ios.hpp"
