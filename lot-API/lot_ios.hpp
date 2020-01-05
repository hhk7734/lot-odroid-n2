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
inline ios_base::fmtflags ios_base::flags( void ) const
{
    return mformat;
}

inline void ios_base::unsetf( ios_base::fmtflags mask )
{
    mformat &= ~mask;
}

inline streamsize ios_base::precision( void ) const
{
    return mprecision;
}

inline ios_base &dec( ios_base &str )
{
    str.setf( ios_base::dec, ios_base::basefield );
    return str;
}
inline ios_base &hex( ios_base &str )
{
    str.setf( ios_base::hex, ios_base::basefield );
    return str;
}
inline ios_base &oct( ios_base &str )
{
    str.setf( ios_base::oct, ios_base::basefield );
    return str;
}
}    // namespace lot