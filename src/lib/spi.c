#include <avr/io.h>
#include "spi.h"

/**
  * Thank you, Yash at maxEmbedded for the quick howto
  * http://maxembedded.com/2013/11/the-spi-of-the-avr/
  */

void spi_init_master()
{
	// set MOSI, SCK, !SS as output
	DDRB |= (1<<PB3) | (1<<PB5) | (1<<PB2);
	
	// enable SPI
	// set mode to master
	// set prescaler to Fosc/4 (000)
	SPCR = (1<<SPE) | (1<<MSTR);
}

uint8_t spi_transfer(uint8_t data)
{
	// load data into the buffer
	SPDR = data;
	
	// wait until transmission complete
	while (!(SPSR & (1<<SPIF)))
	{
	}
	
	// return received data
	return SPDR;
}

void spi_select()
{
	// drive the !SS low
	PORTB &= ~(1 << PB2);
}

void spi_deselect()
{
	// drive the !SS high
	PORTB |= (1 << PB2);
}
