#include <lot/lot.h>
#include <iostream>
#include <iomanip>
#include <string>

int main( int argc, char *argv[] )
{
    lot::init();

    int max_pin = 40;

    if( argc > 1 )
    {
        max_pin = std::stoi( argv[1] );
    }

    for( int i = 1; i <= max_pin; ++i )
    {
        std::cout << std::setw( 3 ) << std::setfill( '0' ) << i << ": ";
        if( lot::get_lot_pin_available( i ) != UNUSED )
        {
            switch( lot::get_pin_mode( i ) )
            {
                case lot::INPUT:
                    std::cout << "IN  ";
                    break;
                case lot::OUTPUT:
                    std::cout << "OUT ";
                    break;
                case lot::ALT_FUNC0:
                    std::cout << "ALT0";
                    break;
                case lot::ALT_FUNC1:
                    std::cout << "ALT1";
                    break;
                case lot::ALT_FUNC2:
                    std::cout << "ALT2";
                    break;
                case lot::ALT_FUNC3:
                    std::cout << "ALT3";
                    break;
                case lot::ALT_FUNC4:
                    std::cout << "ALT4";
                    break;
                case lot::ALT_FUNC5:
                    std::cout << "ALT5";
                    break;
                case lot::ALT_FUNC6:
                    std::cout << "ALT6";
                    break;
                case lot::ALT_FUNC7:
                    std::cout << "ALT7";
                    break;
            }
        }
        else
        {
            std::cout << "    ";
        }

        if( i % 2 == 1 )
        {
            std::cout << "\t";
        }
        else
        {
            std::cout << std::endl;
        }
    }
}