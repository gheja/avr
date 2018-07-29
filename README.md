# Some AVR-related libraries, tools and the like

## Libraries

### SPI (Serial Peripheral Interface)

A basic library for entering master mode, selecting and deselecting slave, and transmit/receive data.

See: [src/lib](src/lib)


### Micron M25P16 Serial Flash Embedded Memory

A library for handling the M25P16 flash memory on AVR supporting the following:
  * enable write mode
  * disable write mode
  * erease sectors
  * write data
  * read data

See: [src/lib](src/lib)


## Tools and examples

### Micron M25P16 data transfer

Example:

See: [src/m25p16_write_test](src/m25p16_write_test)

Tool to send larger amount of data in parts:

See: [src/m25p16_write_test](src/m25p16_write_test)

Tool to cut data into parts and generate source for it:

See: [src/m25p16_write_huge/generator](src/m25p16_write_huge/generator)


## license
MIT License

Copyright (c) 2015-2017 Gabor Heja

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
