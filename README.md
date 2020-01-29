![license](https://img.shields.io/github/license/loliot/lot-odroid-n2)
![version](https://img.shields.io/github/v/tag/loliot/lot-odroid-n2?sort=semver)
![language](https://img.shields.io/github/languages/top/loliot/lot-odroid-n2)

# lot-odroid-n2

## Installation

<strong><a href="https://github.com/loliot/lot#installation" target=_blank>lot installation guide</a></strong>

```bash
sudo lot install cpp
```

## Blink example

```cpp
#include <lot/lot.h>
#include <lot/Gpio.h>

const int LED_PIN = 13;

int main( void )
{
    lot::Gpio led( LED_PIN );
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
