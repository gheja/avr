#include "spi.h"
#include "m25p16.h"

/**
  * Micron M25P16 Serial Flash Embedded Memory
  *
  * see:
  *  http://www.micron.com/~/media/documents/products/data-sheet/nor-flash/serial-nor/m25p/m25p16.pdf
  *  or http://www.farnell.com/datasheets/40260.pdf
  *
  */

void m25p16_init()
{
	spi_init_master();
}

void m25p16_write_enable()
{
	spi_select();
	spi_transfer(0x06);
	spi_deselect();
}

void m25p16_write_disable()
{
	spi_select();
	spi_transfer(0x04);
	spi_deselect();
}

void m25p16_sector_erase(uint8_t a3, uint8_t a2, uint8_t a1)
{
	// NOTE: once the operation completes the write will be disabled
	
	spi_select();
	spi_transfer(0xd8);
	spi_transfer(a3);
	spi_transfer(a2);
	spi_transfer(a1);
	spi_deselect();
}

void m25p16_wait_for_operation()
{
	uint8_t a;
	
	spi_select();
	// read status register
	spi_transfer(0x05);
	while (1)
	{
		// read the status register (dummy data from master)
		a = spi_transfer(0x00);
		
		// check if WIP (write in progress) bit set
		if ((a & 0x01) == 0)
		{
			break;
		}
		
		// we will check the status register here as often as possible,
		// this is not affecting the current operation
	}
	spi_deselect();
}

void m25p16_write_begin(uint8_t a3, uint8_t a2, uint8_t a1)
{
	spi_select();
	spi_transfer(0x02);
	spi_transfer(a3);
	spi_transfer(a2);
	spi_transfer(a1);
}

inline void m25p16_write_byte(uint8_t data)
{
	// NOTE: m25p16_write_begin() is needed before calling this
	
	spi_transfer(data);
}

void m25p16_write_end()
{
	// NOTE: m25p16_write_begin() is needed before calling this
	// NOTE: once the operation completes the write will be disabled
	
	spi_deselect();
}

void m25p16_read_begin(uint8_t a3, uint8_t a2, uint8_t a1)
{
	spi_select();
	spi_transfer(0x03);
	spi_transfer(a3);
	spi_transfer(a2);
	spi_transfer(a1);
}

inline uint8_t m25p16_read_byte()
{
	// NOTE: m25p16_read_begin() is needed before calling this
	
	// master sends dummy data only
	return spi_transfer(0x00);
}

void m25p16_read_end()
{
	// NOTE: m25p16_read_begin() is needed before calling this
	
	spi_deselect();
}
