![license](https://img.shields.io/github/license/loliot/lot-odroid-n2)
![version](https://img.shields.io/github/v/tag/loliot/lot-odroid-n2?sort=semver)
![language](https://img.shields.io/github/languages/top/loliot/lot-odroid-n2)

# lot-odroid-n2

## Installation

Ref: <a href="https://github.com/loliot/lot" target=_blank>https://github.com/loliot/lot</a>

```bash
sudo add-apt-repository -y ppa:loliot/ppa \
&& sudo apt update
```

```bash
sudo apt install -y lot
```

```bash
sudo lot install cpp
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
