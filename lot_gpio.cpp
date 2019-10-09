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

#include "lot.h"

#include <fcntl.h>       // open()
#include <sys/mman.h>    // mmap()
#include <unistd.h>      // getuid()

namespace lot
{
lot_mode_t lot_mode;

static volatile uint32_t *gpio;

static uint32_t get_input_en_offset( pin_size_t pin )
{
    switch( pin )
    {
        case 0 ... 15:
            // GPIOA.0 ... GPIOA.15
            return S922X_GPIOA_INPUT_EN_5_REG_OFFSET;
        case 16 ... 35:
            // GPIOX.0 ... GPIOX.19
            return S922X_GPIOX_INPUT_EN_2_REG_OFFSET;
    }
}

static uint32_t get_mux_offset( pin_size_t pin )
{
    switch( pin )
    {
        case 0 ... 7:
            // GPIOA.0 ... GPIOA.7
            return S922X_GPIOA_MUX_D_REG_OFFSET;
        case 8 ... 15:
            // GPIOA.8 ... GPIOA.15
            return S922X_GPIOA_MUX_E_REG_OFFSET;
        case 16 ... 23:
            // GPIOX.0 ... GPIOX.7
            return S922X_GPIOX_MUX_3_REG_OFFSET;
        case 24 ... 31:
            // GPIOX.8 ... GPIOX.15
            return S922X_GPIOX_MUX_4_REG_OFFSET;
        case 32 ... 35:
            // GPIOX.16 ... GPIOX.19
            return S922X_GPIOX_MUX_5_REG_OFFSET;
    }
}

static uint32_t get_output_offset( pin_size_t pin )
{
    switch( pin )
    {
        case 0 ... 15:
            // GPIOA.0 ... GPIOA.15
            return S922X_GPIOA_OUTPUT_5_REG_OFFSET;
        case 16 ... 35:
            // GPIOX.0 ... GPIOX.19
            return S922X_GPIOX_OUTPUT_2_REG_OFFSET;
    }
}

static uint32_t get_input_offset( pin_size_t pin )
{
    switch( pin )
    {
        case 0 ... 15:
            // GPIOA.0 ... GPIOA.15
            return S922X_GPIOA_INPUT_5_REG_OFFSET;
        case 16 ... 35:
            // GPIOX.0 ... GPIOX.19
            return S922X_GPIOX_INPUT_2_REG_OFFSET;
    }
}

void init( lot_mode_t mode )
{
    lot_mode = mode;
    int fd   = -1;

    if( getuid() == 0 )
    {
        // With root privilege.
        fd = open( "/dev/mem", O_RDWR | O_SYNC | O_CLOEXEC );
        if( fd < 0 )
        {
            // Error message.
        }
    }
    else
    {
        // Without root privilege.
        fd = open( "/dev/gpiomem", O_RDWR | O_SYNC | O_CLOEXEC );
        if( fd < 0 )
        {
            // Error message.
        }
        else
        {
            // Warning message.
        }
    }

    gpio = ( uint32_t * )mmap( 0,
                               MMAP_BLOCK_SIZE,
                               PROT_READ | PROT_WRITE,
                               MAP_SHARED,
                               fd,
                               S922X_GPIO_BASE );

    if( ( void * )gpio == MAP_FAILED )
    {
        // Error message.
    }

    close( fd );

    switch( mode )
    {
        case LOT:

            break;

        case PHY:
            break;
    }
}

void set_pin_mode( pin_size_t pin, pin_mode_t mode )
{
    uint32_t input_en, mux;
    uint8_t  shift, shift_4;

    if( lot_mode == PHY )
    {
        pin = phy_to_lot[pin];
    }

    if( pin == UNUSED )
    {
        // Error message.
    }

    input_en = get_input_en_offset( pin );
    mux      = get_mux_offset( pin );
    shift    = lot_to_shift[pin];
    shift_4  = ( shift * 4 ) & 0x1F;

    switch( mode )
    {
        case INPUT:
            *( gpio + input_en ) |= ( 1 << shift );
            *( gpio + mux ) &= ~( 0xF << shift_4 );
            break;
        case OUTPUT:
            *( gpio + input_en ) &= ~( 1 << shift );
            *( gpio + mux ) &= ~( 0xF << shift_4 );
            break;
        default:
            // Error message.
            break;
    }
}

pin_mode_t get_pin_mode( pin_size_t pin )
{
    if( lot_mode == PHY )
    {
    }
}

void set_pin_pull_up_down( pin_size_t pin, pud_mode_t pud )
{
    if( lot_mode == PHY )
    {
    }
}

pud_mode_t get_pin_pull_up_down( pin_size_t pin )
{
    if( lot_mode == PHY )
    {
    }
}

void set_pin_speed( pin_size_t pin, uint32_t speed )
{
    if( lot_mode == PHY )
    {
    }
}

uint32_t get_pin_speed( pin_size_t pin )
{
    if( lot_mode == PHY )
    {
    }
}

void set_pin_drive( pin_size_t pin, uint32_t drive )
{
    if( lot_mode == PHY )
    {
    }
}

uint32_t get_pin_drive( pin_size_t pin )
{
    if( lot_mode == PHY )
    {
    }
}

void digital_write( pin_size_t pin, pin_status_t status )
{
    uint32_t output;

    if( lot_mode == PHY )
    {
        pin = phy_to_lot[pin];
    }

    if( pin == UNUSED )
    {
        // Error message.
    }

    output = get_output_offset( pin );

    if( status == LOW )
    {
        *( gpio + output ) &= ~( 1 << lot_to_shift[pin] );
    }
    else
    {
        *( gpio + output ) |= ( 1 << lot_to_shift[pin] );
    }
}

pin_status_t digital_read( pin_size_t pin )
{
    uint32_t input;

    if( lot_mode == PHY )
    {
        pin = phy_to_lot[pin];
    }

    if( pin == UNUSED )
    {
        // Error message.
    }

    input = get_input_offset( pin );

    if( ( *( gpio + input ) & ( 1 << lot_to_shift[pin] ) ) == 0 )
    {
        return LOW;
    }
    else
    {
        return HIGH;
    }
}

void analog_write( pin_size_t pin, uint32_t value )
{
    if( lot_mode == PHY )
    {
    }
}

uint32_t analog_read( pin_size_t pin )
{
    if( lot_mode == PHY )
    {
    }
}
}    // namespace lot