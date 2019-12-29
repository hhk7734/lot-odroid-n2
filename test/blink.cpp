#include <lot/lot.h>

const lot::pin_size_t PUD_PIN = 11;
const lot::pin_size_t LED_PIN = 13;

int main( void )
{
    lot::init();
    lot::set_pin_mode( PUD_PIN, lot::INPUT );
    lot::set_pin_mode( LED_PIN, lot::OUTPUT );

    for( ;; )
    {
        if( lot::digital_read( PUD_PIN ) == lot::HIGH )
        {
            lot::set_pin_pull_up_down( PUD_PIN, lot::PULL_DOWN );
            lot::digital_write( LED_PIN, lot::LOW );
        }
        else
        {
            lot::set_pin_pull_up_down( PUD_PIN, lot::PULL_UP );
            lot::digital_write( LED_PIN, lot::HIGH );
        }

        lot::delay_ms( 500 );
    }
}