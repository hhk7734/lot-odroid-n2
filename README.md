# lot-API

## Pin mapping

Pin mapping is based on the pinouts of the datasheet.

### LOT

Set port numbers in alphabetical order.  
Set pin numbers by the combination of the port numbers and pin numbers in the ports.

### PHY

Set the pin numbers in physical order.

#### Examples

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

## Code formatting

```bash
$ clang-format -style=file -i -verbose <file>
```

```bash
$ make clang
```

## Project structure

```bash
lot
├── lot-API
│   ├── ...
│   └── ...
├── ...
└── ...
```
