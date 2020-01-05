#include <lot/lot.h>
#include <lot/Gpio.h>

#include <string>
#include <iostream>

int main( int argc, char *argv[] )
{
    lot::init_time();

    int pin = 37;

    if( argc > 1 )
    {
        pin = std::stoi( argv[1] );
    }

    lot::Gpio ain( pin );

    ain.mode( lot::AIN );

    for( ;; )
    {
        std::cout << ain.analog() << std::endl;
        lot::delay_ms( 500 );
    }
}