#ifndef _SPI_H_
#define _SPI_H_

#include <avr/io.h>

void spi_init_master();
uint8_t spi_transfer(uint8_t data);
void spi_select();
void spi_deselect();

#endif
