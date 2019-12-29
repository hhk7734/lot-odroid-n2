#include <lot/lot.h>
#include <iostream>

int main( void )
{
    lot::init();

    for( int i = 1; i <= 40; ++i )
    {
        if( lot::phy_to_lot[i] != UNUSED )
        {
            std::cout << i << ": " << lot::get_pin_mode( i );
        }
        else
        {
            std::cout << i << ": UNU";
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