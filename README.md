# lot-API

## Adding New board

```bash
git clone https://github.com/loliot/lot-SBC.git
```

Change **lot-SBC** to **lot-\<your board\>** in `debian/*` and Doxyfile.
Make the board name a combination of lowercase letters and hyphens.

Rewrite README.md. 

```bash
git remote rename origin lot-SBC &&\
git remote add origin https://github.com/loliot/lot-<your board>.git &&\
git add . &&\
git commit -m "init" &&\
git push -f -u origin master
```

## Pin mapping

Pin mapping is based on the pinouts of the datasheet.

### LOT

Set port group numbers in alphabetical order.  
Set pin numbers by the combination of the port group numbers and pin numbers in the ports.

### PHY

Set the pin numbers in physical order.

#### Example

In case using an 8-bit processor and using PA3, PA4, PC0, PC2, PD1, and PD4.

Set port A, C, and D numbers to 0, 8, and 16, respectively.

Set PA3 and PA4 to 3(0+3) and 4(0+4).  
Set PC0 and PC2 to 8(8+0) and 10(8+2).  
Set PD1 and PD4 to 17(16+1) and 20(16+4).

```bash
|     | LOT |  PHY  | LOT |     |
| PA3 |   3 | 1 | 2 |   4 | PA4 |
| PD4 |  20 | 3 | 4 |   8 | PC0 |
| PC2 |  10 | 5 | 6 |  17 | PD1 |
```

## Structure

```bash
lot-<your borad>
├── lot-API
│   ├── II2c.h
│   ├── ISpi.h
│   ├── IUart.h
│   ├── lot_def.h
│   ├── lot_gpio.h
│   ├── lot_time.h
│   └── ...
├── lot.h
├── I2c.h
├── Spi.h
├── Uart.h
└── ...
```

## Editing Makefile

If adding a.cpp source to lot-\<your board\>, add the source name to CXXSRCS in Makefile as shown below.

```make
CSRCS = \

SXXSRCS = a.cpp \

INCS_DIR = .\

```

## Code formatting

```bash
$ make clang
```
