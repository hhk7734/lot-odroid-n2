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
#include <map>

namespace lot
{
namespace gpio
{
    static volatile uint32_t *gpio_base;

    static std::map<int, int> adc_fds;

    static uint32_t input_en_offset( int pin )
    {
        switch( pin )
        {
            case GPIOX0 ... GPIOX19:
                return S922X_GPIOX_INPUT_EN_2_REG_OFFSET;
            case GPIOA0 ... GPIOA15:
                return S922X_GPIOA_INPUT_EN_5_REG_OFFSET;
        }

        return -1;
    }

    static uint32_t mux_offset( int pin )
    {
        switch( pin )
        {
            case GPIOX0 ... GPIOX7:
                return S922X_GPIOX_MUX_3_REG_OFFSET;
            case GPIOX8 ... GPIOX15:
                return S922X_GPIOX_MUX_4_REG_OFFSET;
            case GPIOX16 ... GPIOX19:
                return S922X_GPIOX_MUX_5_REG_OFFSET;
            case GPIOA0 ... GPIOA7:
                return S922X_GPIOA_MUX_D_REG_OFFSET;
            case GPIOA8 ... GPIOA15:
                return S922X_GPIOA_MUX_E_REG_OFFSET;
        }

        return -1;
    }

    static uint32_t output_offset( int pin )
    {
        switch( pin )
        {
            case GPIOX0 ... GPIOX19:
                return S922X_GPIOX_OUTPUT_2_REG_OFFSET;
            case GPIOA0 ... GPIOA15:
                return S922X_GPIOA_OUTPUT_5_REG_OFFSET;
        }

        return -1;
    }

    static uint32_t input_offset( int pin )
    {
        switch( pin )
        {
            case GPIOX0 ... GPIOX19:
                return S922X_GPIOX_INPUT_2_REG_OFFSET;
            case GPIOA0 ... GPIOA15:
                return S922X_GPIOA_INPUT_5_REG_OFFSET;
        }

        return -1;
    }

    static uint32_t pull_up_en_offset( int pin )
    {
        switch( pin )
        {
            case GPIOX0 ... GPIOX19:
                return S922X_GPIOX_PULL_UP_EN_2_REG_OFFSET;
            case GPIOA0 ... GPIOA15:
                return S922X_GPIOA_PULL_UP_EN_5_REG_OFFSET;
        }

        return -1;
    }

    static uint32_t pull_up_offset( int pin )
    {
        switch( pin )
        {
            case GPIOX0 ... GPIOX19:
                return S922X_GPIOX_PULL_UP_2_REG_OFFSET;
            case GPIOA0 ... GPIOA15:
                return S922X_GPIOA_PULL_UP_5_REG_OFFSET;
        }

        return -1;
    }

    static uint32_t ds_offset( int pin )
    {
        switch( pin )
        {
            case GPIOX0 ... GPIOX15:
                return S922X_GPIOX_DS_2A_REG_OFFSET;
            case GPIOX16 ... GPIOX19:
                return S922X_GPIOX_DS_2B_REG_OFFSET;
            case GPIOA0 ... GPIOA15:
                return S922X_GPIOA_DS_5A_REG_OFFSET;
        }

        return -1;
    }

    void init( void )
    {
        int fd = -1;

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

        gpio_base = ( uint32_t * )mmap( 0,
                                        MMAP_BLOCK_SIZE,
                                        PROT_READ | PROT_WRITE,
                                        MAP_SHARED,
                                        fd,
                                        S922X_GPIO_BASE );

        if( ( void * )gpio_base == MAP_FAILED )
        {
            close( fd );
            Log::error( "Failed to map gpio in init().\r\n" );
            throw std::runtime_error( strerror( errno ) );
        }

        close( fd );

        const char *AIN0_NODE, *AIN1_NODE;

        /* ADC node setup */
        AIN0_NODE
            = "/sys/devices/platform/ff809000.saradc/iio:device0/"
              "in_voltage2_raw";
        AIN1_NODE
            = "/sys/devices/platform/ff809000.saradc/iio:device0/"
              "in_voltage3_raw";

        adc_fds[40] = open( AIN0_NODE, O_RDONLY );
        adc_fds[37] = open( AIN1_NODE, O_RDONLY );
    }

    void mode( int pin, pin_mode_t pin_mode )
    {
        uint32_t input_en, mux;
        uint8_t  shift, shift_4;
        int      original_pin = pin;

        pin = phy_to_gpio[pin];

        if( pin == UNUSED )
        {
            if( pin_mode != AIN )
            {
                Log::error( "%d must set AIN.\r\n", original_pin );
                throw std::invalid_argument(
                    "Check pin number and functions." );
            }
            return;
        }

        input_en = input_en_offset( pin );
        mux      = mux_offset( pin );
        shift    = pin & 0x1F;
        shift_4  = ( shift * 4 ) & 0x1F;

        switch( pin_mode )
        {
            case DIN:
                *( gpio_base + input_en ) |= ( 1 << shift );
                *( gpio_base + mux ) &= ~( 0xF << shift_4 );
                pull_up_down( original_pin, PULL_OFF );
                return;
            case DOUT:
                *( gpio_base + input_en ) &= ~( 1 << shift );
                *( gpio_base + mux ) &= ~( 0xF << shift_4 );
                return;
            default:
                Log::error( "Set unavailable mode for pin %d in %s().\r\n",
                            original_pin,
                            __func__ );
                throw std::invalid_argument( "Check mode." );
        }
    }

    pin_mode_t mode( int pin )
    {
        uint32_t input_en, mux;
        uint8_t  shift, shift_4;
        uint8_t  mode;

        pin = phy_to_gpio[pin];

        if( pin == UNUSED )
        {
            return AIN;
        }

        input_en = input_en_offset( pin );
        mux      = mux_offset( pin );
        shift    = pin & 0x1F;
        shift_4  = ( shift * 4 ) & 0x1F;

        mode = ( *( gpio_base + mux ) >> shift_4 ) & 0xF;
        return mode ? static_cast<pin_mode_t>( ALT0 + mode )
                    : ( ( *( gpio_base + input_en ) & ( 1 << shift ) ) ? DIN
                                                                       : DOUT );
    }

    void pull_up_down( int pin, pud_mode_t pud )
    {
        uint32_t pull_up_en, pull_up;
        uint8_t  shift;

        pin = phy_to_gpio[pin];

        pull_up_en = pull_up_en_offset( pin );
        pull_up    = pull_up_offset( pin );
        shift      = pin & 0x1F;

        switch( pud )
        {
            case PULL_OFF:
                *( gpio_base + pull_up_en ) &= ~( 1 << shift );
                return;
            case PULL_DOWN:
                *( gpio_base + pull_up_en ) |= ( 1 << shift );
                *( gpio_base + pull_up ) &= ~( 1 << shift );
                return;
            case PULL_UP:
                *( gpio_base + pull_up_en ) |= ( 1 << shift );
                *( gpio_base + pull_up ) |= ( 1 << shift );
                return;
        }
    }

    pud_mode_t pull_up_down( int pin )
    {
        uint32_t pull_up_en, pull_up;
        uint8_t  shift;

        pin = phy_to_gpio[pin];

        pull_up_en = pull_up_en_offset( pin );
        pull_up    = pull_up_offset( pin );
        shift      = pin & 0x1F;

        if( *( gpio_base + pull_up_en ) & ( 1 << shift ) )
        {
            return ( *( gpio_base + pull_up ) & ( 1 << shift ) ) ? PULL_UP
                                                                 : PULL_DOWN;
        }
        else
        {
            return PULL_OFF;
        }
    }

    void drive( int pin, uint32_t pin_drive )
    {
        uint32_t ds;
        uint8_t  shift_2;

        pin = phy_to_gpio[pin];

        switch( pin_drive )
        {
            case 0 ... 3:
                /*
                 * 0 : 0.5 mA
                 * 1 : 2.5 mA
                 * 2 : 3 mA
                 * 3 : 4 ~ 6 mA, this does not care about Vol/Voh spec.
                 */
                ds      = ds_offset( pin );
                shift_2 = ( ( pin & 0x1F ) * 2 ) & 0x1F;

                *( gpio_base + ds ) &= ~( 0x3 << shift_2 );
                *( gpio_base + ds ) |= ( pin_drive << shift_2 );
                break;

            default:
                Log::error( "Set unavailable drive for pin %d in %s().\r\n",
                            pin,
                            __func__ );
                Log::error( "Drive must be 0 to 3.\r\n" );
                throw std::invalid_argument( "Check driving capability." );
        }
    }

    uint32_t drive( int pin )
    {
        uint32_t ds;
        uint8_t  shift_2;

        pin = phy_to_gpio[pin];

        ds      = ds_offset( pin );
        shift_2 = ( ( pin & 0x1F ) * 2 ) & 0x1F;

        return ( *( gpio_base + ds ) >> shift_2 ) & 0x3;
    }

    void digital( int pin, int status )
    {
        uint32_t output;

        pin = phy_to_gpio[pin];

        output = output_offset( pin );

        if( status == LOW )
        {
            *( gpio_base + output ) &= ~( 1 << ( pin & 0x1F ) );
        }
        else
        {
            *( gpio_base + output ) |= ( 1 << ( pin & 0x1F ) );
        }
    }

    int digital( int pin )
    {
        uint32_t input;

        pin = phy_to_gpio[pin];

        input = input_offset( pin );

        return ( *( gpio_base + input ) & ( 1 << ( pin & 0x1F ) ) ) ? HIGH
                                                                    : LOW;
    }

    void analog( int pin, int value )
    {
        Log::error( "%s() is not supported or not implemented yet.\r\n",
                    __func__ );
        throw unsupported_error( __func__ );
    }

    int analog( int pin )
    {
        char value[5] = { 0 };
        lseek( adc_fds.at( pin ), 0L, SEEK_SET );
        if( read( adc_fds.at( pin ), &value[0], 4 ) < 0 )
        {
            Log::warning( "Failed to read analog value from %d.\r\n", pin );
            return -1;
        }
        return atoi( value );
    }
}    // namespace gpio
}    // namespace lot
