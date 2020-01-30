/*
 * MIT License
 * 
 * Copyright (c) 2020 Hyeonki Hong <hhk7734@gmail.com>
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
class IGpio
{
public:
    /**
     * @brief Creates an instance of IGpio class and initializes GPIO.
     * @param pin
     */
    IGpio( int pin )
        : m_pin( pin )
    {
    }

    /**
     * @brief Deletes instance of IGpio class.
     */
    virtual ~IGpio()
    {
    }

    /**
     * @brief Sets pin mode.
     * @param pin_mode \n
     *      This parameter can be a value of @ref GpioMode.
     */
    virtual void mode( GpioMode pin_mode );

    /**
     * @brief Gets pin mode.
     * @return Pin mode. \n
     *      This return value can be a value of @ref GpioMode.
     */
    virtual GpioMode mode( void );

    /**
     * @brief Sets pull up/down/off.
     * @param pud \n
     *      This parameter can be a value of @ref PUDMode.
     */
    virtual void pull_up_down( PUDMode pud );

    /**
     * @brief Gets pull up/down/off.
     * @return Pull up/down/off mode. \n
     *      This return value can be a value of @ref PUDMode.
     */
    virtual PUDMode pull_up_down( void );

    /**
     * @brief Sets pin drive strength.
     * @param pin_drive
     */
    virtual void drive( uint32_t pin_drive );

    /**
     * @brief Gets pin drive strength.
     * @return Pin drive.
     */
    virtual uint32_t drive( void );

    /**
     * @brief Sets digital output status.
     * @param status \n
     *      This parameter can be @ref LOW (0) or @ref HIGH (not 0).
     */
    virtual void digital( int status );

    /**
     * @brief Gets digital output status.
     * @return Digital output status. \n
     *      This return value can be @ref LOW (0) or @ref HIGH (not 0).
     */
    virtual int digital( void );

    /**
     * @brief Sets digital output to @ref HIGH.
     */
    void on( void );

    /**
     * @brief Sets digital output to @ref LOW.
     */
    void off( void );

    /**
     * @brief Toggle digital output.
     * @return Digital output status. \n
     *      This return value can be @ref LOW (0) or @ref HIGH (not 0).
     */
    int toggle( void );

    /**
     * @brief Sets analog output value.
     * @param value
     */
    virtual void analog( int value );

    /**
     * @brief Gets analog output value.
     * @return Analog output value.
     */
    virtual int analog( void );

protected:
    const int m_pin;
    GpioMode  m_mode;
};
}    // namespace lot

#include "IGpio.hpp"