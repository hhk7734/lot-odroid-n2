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
/**
 * @brief Initializes GPIO.
 */
void init( void );

/**
 * @brief Gets a LOT pin available.
 * @param pin
 * @return LOT pin. \n
 *      If the pin received as a parameter is not available, \n
 *      it returns UNUSED(-1).
 */
int get_gpio_available( int pin );

/**
 * @brief Sets a pin mode.
 * @param pin
 * @param mode \n
 *      This parameter can be a value of @ref pin_mode_t.
 */
void set_pin_mode( int pin, pin_mode_t mode );

/**
 * @brief Gets a pin mode.
 * @param pin
 * @return Pin mode.
 */
pin_mode_t get_pin_mode( int pin );

/**
 * @brief Sets a pin pull-up-down mode.
 * @param pin
 * @param pud \n
 *      This parameter can be a value of @ref pud_mode_t.
 */
void set_pin_pull_up_down( int pin, pud_mode_t pud );

/**
 * @brief Gets a pin pull-up-down mode.
 * @param pin
 * @return Pull-up-down mode.\n
 *      This return can be a value of @ref pud_mode_t.
 */
pud_mode_t get_pin_pull_up_down( int pin );

/**
 * @brief Sets a pin drive strength.
 * @param pin
 * @param drive Drive strength.
 */
void set_pin_drive( int pin, uint32_t drive );

/**
 * @brief Gets a pin drive strength.
 * @param pin
 * @return Drive strength.
 */
uint32_t get_pin_drive( int pin );

/**
 * @brief Writes a HIGH or a LOW value to a pin.
 * @param pin
 * @param status
 */
void digital_write( int pin, int status );

/**
 * @brief Reads a value from a pin.
 * @param pin
 * @return digital status
 */
int digital_read( int pin );

/**
 * @brief Writes an analog value to a pin.
 * @param pin
 * @param value
 */
void analog_write( int pin, int value );

/**
 * @brief Reads an analog value from a pin.
 * @param pin
 * @return analog value
 */
int analog_read( int pin );
}    // namespace lot