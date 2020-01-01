#include <lot/lot.h>
#include <string>

int main( int argc, char *argv[] )
{
    lot::init();

    int pin = 13;

    if( argc > 1 )
    {
        pin = std::stoi( argv[1] );
    }

    lot::set_pin_mode( pin, lot::OUTPUT );

    for( ;; )
    {
        if( lot::digital_read( pin ) == lot::HIGH )
        {
            lot::digital_write( pin, lot::LOW );
        }
        else
        {
            lot::digital_write( pin, lot::HIGH );
        }

        lot::delay_ms( 300 );
    }
}