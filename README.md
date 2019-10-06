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
#include <unistd.h>

const lot::pin_size_t LED_PIN = 7;

int main( void )
{
    lot::init( lot::PHY );
    lot::set_pin_mode( LED_PIN, lot::OUTPUT );

    for( ;; )
    {
        lot::digital_write( LED_PIN, lot::HIGH );
        sleep( 1 );
        lot::digital_write( LED_PIN, lot::LOW );
        sleep( 1 );
    }
}
```

```bash
g++ blink.cpp -o blink -llot &&\
./blink
```
