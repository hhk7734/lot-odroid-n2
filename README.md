# lot-odroid-n2

## Installation

```bash
sudo add-apt-repository -y ppa:loliot/ppa &&\
sudo apt update
```

```bash
sudo apt install -y lot
```

```bash
sudo lot install
```

## Blink example

```cpp
#include <lot/lot.h>
#include <lot/Gpio.h>

#include <string>

int main( int argc, char *argv[] )
{
    lot::init_time();

    int pin = 13;

    if( argc > 1 )
    {
        pin = std::stoi( argv[1] );
    }

    lot::Gpio led( pin );

    led.mode( lot::DOUT );

    for( ;; )
    {
        led.toggle();
        lot::delay_ms( 200 );
    }
}
```

```bash
g++ blink.cpp -o blink -llot &&\
./blink
```
