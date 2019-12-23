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

const lot::pin_size_t LED_PIN = 7;

int main( void )
{
    lot::init();
    lot::set_pin_mode( LED_PIN, lot::OUTPUT );

    for( ;; )
    {
        lot::digital_write( LED_PIN, lot::HIGH );
        lot::delay_ms( 500 );
        lot::digital_write( LED_PIN, lot::LOW );
        lot::delay_ms( 500 );
    }
}
```

```bash
g++ blink.cpp -o blink -llot &&\
./blink
```
