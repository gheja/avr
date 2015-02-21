m25p16 write huge
=================

This tool is intended to be used to populate (write the initial contents
of) the M25P16 Serial Flash Memory.

It is working by placing the data in the program memory of AVR (Flash)
and then transmitting that data to the M25P16.

There is a generator under the *generator* subdirectory that outputs the
code snipplet that needs to be inserted into main.c in order to do the
programming.

The generator and the program can handle larger amounts of data than the
AVR Flash itself by splitting the data into more so called pages and
introducing a pre-processor identifier called PAGE that tells which page
should be compiled into the program. (Note: you might need to tune the
SECTOR_COUNT in generator/generator.c).

The MEM_START parameter defines which address the M25P16 should start to
write its memory. As the M25P16 uses 256 byte long sectors, the 
*m25p16 write huge* (and the generator) takes this into account.
The MEM_START parameter addresses these sectors (so if MEM_START is set
to 0x1234 then the first byte address written is 0x123400).

It is not the best way to do the job but it is certanly a quick and easy
one.
