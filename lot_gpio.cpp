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

#include "lot.h"

#include <fcntl.h>       // open()
#include <sys/mman.h>    // mmap()
#include <unistd.h>      // getuid()
#include <errno.h>       // errno
#include <string.h>      // strerror()
#include <stdexcept>

namespace lot
{
static volatile uint32_t *gpio;

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

    return -1;
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

    return -1;
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

    return -1;
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

    return -1;
}

static uint32_t get_pull_up_en_offset( pin_size_t pin )
{
    switch( pin )
    {
        case 0 ... 15:
            // GPIOA.0 ... GPIOA.15
            return S922X_GPIOA_PULL_UP_EN_5_REG_OFFSET;
        case 16 ... 35:
            // GPIOX.0 ... GPIOX.19
            return S922X_GPIOX_PULL_UP_EN_2_REG_OFFSET;
    }

    return -1;
}

static uint32_t get_pull_up_offset( pin_size_t pin )
{
    switch( pin )
    {
        case 0 ... 15:
            // GPIOA.0 ... GPIOA.15
            return S922X_GPIOA_PULL_UP_5_REG_OFFSET;
        case 16 ... 35:
            // GPIOX.0 ... GPIOX.19
            return S922X_GPIOX_PULL_UP_2_REG_OFFSET;
    }

    return -1;
}

static uint32_t get_ds_offset( pin_size_t pin )
{
    switch( pin )
    {
        case 0 ... 15:
            // GPIOA.0 ... GPIOA.15
            return S922X_GPIOA_DS_5A_REG_OFFSET;
            break;
        case 16 ... 31:
            // GPIOX.0 ... GPIOX.15
            return S922X_GPIOX_DS_2A_REG_OFFSET;
            break;
        case 32 ... 35:
            // GPIOX.16 ... GPIOX.19
            return S922X_GPIOX_DS_2B_REG_OFFSET;
            break;
    }

    return -1;
}

static inline int get_lot_pin_available( int pin, const char *func_name )
{
    if( pin <= MAX_PHY_PIN_COUNT )
    {
        pin = phy_to_lot[pin];
    }
    else
    {
        pin = UNUSED;
    }

    if( pin < MAX_LOT_PIN_COUNT )
    {
        if( is_available_lot[pin] )
        {
            return pin;
        }
    }

    Log::error( "Used unavailable pin %d in %s().\r\n", pin, func_name );
    throw std::invalid_argument( "Check pin number and functions." );
}

void init( void )
{
    int fd   = -1;
    lot_time_init();

    if( getuid() == 0 )
    {
        // With root privilege.
        fd = open( "/dev/mem", O_RDWR | O_SYNC | O_CLOEXEC );
        if( fd < 0 )
        {
            Log::error( "Failed to open /dev/mem in init().\r\n" );
            throw std::runtime_error( strerror( errno ) );
        }
    }
    else
    {
        // Without root privilege.
        fd = open( "/dev/gpiomem", O_RDWR | O_SYNC | O_CLOEXEC );
        if( fd < 0 )
        {
            Log::error( "Failed to open /dev/gpiomem in init().\r\n" );
            throw std::runtime_error( strerror( errno ) );
        }
        else
        {
            Log::warning( "Used /dev/gpiomem instead of /dev/mem.\r\n" );
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
        close( fd );
        Log::error( "Failed to map gpio in init().\r\n" );
        throw std::runtime_error( strerror( errno ) );
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

int get_lot_pin_available( int pin )
{
    if( pin <= MAX_PHY_PIN_COUNT )
    {
        pin = phy_to_lot[pin];
    }
    else
    {
        return UNUSED;
    }

    if( pin < MAX_LOT_PIN_COUNT )
    {
        if( is_available_lot[pin] )
        {
            return pin;
        }
    }

    return UNUSED;
}

void set_pin_mode( int pin, pin_mode_t mode )
{
    uint32_t   input_en, mux;
    uint8_t    shift, shift_4;
    pin_size_t original_pin = pin;

    pin = get_lot_pin_available( pin, __func__ );

    input_en = get_input_en_offset( pin );
    mux      = get_mux_offset( pin );
    shift    = lot_to_shift[pin];
    shift_4  = ( shift * 4 ) & 0x1F;

    switch( mode )
    {
        case INPUT:
            *( gpio + input_en ) |= ( 1 << shift );
            *( gpio + mux ) &= ~( 0xF << shift_4 );
            set_pin_pull_up_down( original_pin, PULL_OFF );
            return;
        case OUTPUT:
            *( gpio + input_en ) &= ~( 1 << shift );
            *( gpio + mux ) &= ~( 0xF << shift_4 );
            break;
        default:
            Log::error(
                "Set unavailable mode for pin %d in %s().\r\n", pin, __func__ );
            throw std::invalid_argument( "Check mode." );
            break;
    }
}

pin_mode_t get_pin_mode( int pin )
{
    uint32_t input_en, mux;
    uint8_t  shift, shift_4;
    uint8_t  mode;

    pin = get_lot_pin_available( pin, __func__ );

    input_en = get_input_en_offset( pin );
    mux      = get_mux_offset( pin );
    shift    = lot_to_shift[pin];
    shift_4  = ( shift * 4 ) & 0x1F;

    mode = ( *( gpio + mux ) >> shift_4 ) & 0xF;
    return mode
               ? static_cast<pin_mode_t>( ALT_FUNC0 + mode )
               : ( ( *( gpio + input_en ) & ( 1 << shift ) ) ? INPUT : OUTPUT );
}

void set_pin_pull_up_down( int pin, pud_mode_t pud )
{
    uint32_t pull_up_en, pull_up;
    uint8_t  shift;

    pin = get_lot_pin_available( pin, __func__ );

    pull_up_en = get_pull_up_en_offset( pin );
    pull_up    = get_pull_up_offset( pin );
    shift      = lot_to_shift[pin];

    switch( pud )
    {
        case PULL_OFF:
            *( gpio + pull_up_en ) &= ~( 1 << shift );
            return;
        case PULL_DOWN:
            *( gpio + pull_up_en ) |= ( 1 << shift );
            *( gpio + pull_up ) &= ~( 1 << shift );
            return;
        case PULL_UP:
            *( gpio + pull_up_en ) |= ( 1 << shift );
            *( gpio + pull_up ) |= ( 1 << shift );
            return;
    }
}

pud_mode_t get_pin_pull_up_down( int pin )
{
    uint32_t pull_up_en, pull_up;
    uint8_t  shift;

    pin = get_lot_pin_available( pin, __func__ );

    pull_up_en = get_pull_up_en_offset( pin );
    pull_up    = get_pull_up_offset( pin );
    shift      = lot_to_shift[pin];

    if( *( gpio + pull_up_en ) & ( 1 << shift ) )
    {
        if( ( *gpio + pull_up ) & ( 1 << shift ) )
        {
            return PULL_UP;
        }
        else
        {
            return PULL_DOWN;
        }
    }
    else
    {
        return PULL_OFF;
    }
}

void set_pin_speed( int pin, uint32_t speed )
{
    Log::error( "%s() is not supported or not implemented yet.\r\n", __func__ );
    throw unsupported_error( __func__ );
}

uint32_t get_pin_speed( int pin )
{
    Log::error( "%s() is not supported or not implemented yet.\r\n", __func__ );
    throw unsupported_error( __func__ );
}

void set_pin_drive( int pin, uint32_t drive )
{
    uint32_t ds;
    uint8_t  shift_2;

    pin = get_lot_pin_available( pin, __func__ );

    switch( drive )
    {
        case 0 ... 3:
            /*
             * 0 : 0.5 mA
             * 1 : 2.5 mA
             * 2 : 3 mA
             * 3 : 4 ~ 6 mA, this does not care about Vol/Voh spec.
             */

            ds      = get_ds_offset( pin );
            shift_2 = ( lot_to_shift[pin] * 2 ) & 0x1F;

            *( gpio + ds ) &= ~( 0x3 << shift_2 );
            *( gpio + ds ) |= ( drive << shift_2 );
            break;

        default:
            Log::error( "Set unavailable drive for pin %d in %s().\r\n",
                        pin,
                        __func__ );
            Log::error( "Drive must be 0 to 3.\r\n" );
            throw std::invalid_argument( "Check driving capability." );
            break;
    }
}

uint32_t get_pin_drive( int pin )
{
    uint32_t ds;
    uint8_t  shift_2;

    pin = get_lot_pin_available( pin, __func__ );

    ds      = get_ds_offset( pin );
    shift_2 = ( lot_to_shift[pin] * 2 ) & 0x1F;

    return ( *( gpio + ds ) >> shift_2 ) & 0x3;
}

void digital_write( int pin, int status )
{
    uint32_t output;

    pin = get_lot_pin_available( pin, __func__ );

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

int digital_read( int pin )
{
    uint32_t input;

    pin = get_lot_pin_available( pin, __func__ );

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

void analog_write( int pin, int value )
{
    Log::error( "%s() is not supported or not implemented yet.\r\n", __func__ );
    throw unsupported_error( __func__ );
}

int analog_read( int pin )
{
    Log::error( "%s() is not supported or not implemented yet.\r\n", __func__ );
    throw unsupported_error( __func__ );
}
}    // namespace lot
