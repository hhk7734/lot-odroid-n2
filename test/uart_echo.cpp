#include <lot/lot.h>
#include <lot/Uart.h>
#include <iostream>

lot::Uart uart( "/dev/ttyS1" );

int main( void )
{
    lot::init();

    uart.init();

    uart << "hello world" << lot::endl;

    for( ;; )
    {
        if( uart.available() )
        {
            uart.transmit( uart.receive() );
        }
    }
}