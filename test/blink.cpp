#include <lot/lot.h>

const lot::pin_size_t LED_PIN = 13;

int main( void )
{
    lot::init();
    lot::set_pin_mode( LED_PIN, lot::OUTPUT );

    for( ;; )
    {
        if( lot::digital_read( LED_PIN ) == lot::HIGH )
        {
            lot::digital_write( LED_PIN, lot::LOW );
        }
        else
        {
            lot::digital_write( LED_PIN, lot::HIGH );
        }

        lot::delay_ms( 500 );
    }
}