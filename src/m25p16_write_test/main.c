#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include "../lib/spi.h"
#include "../lib/m25p16.h"

#define BIT_SET(x,y) x |= _BV(y)
#define BIT_CLEAR(x,y) x &= ~(_BV(y))
#define BIT_TOGGLE(x,y) x ^= _BV(y)
#define BIT_WAVE(x,y) BIT_SET(x,y); _delay_ms(150); BIT_CLEAR(x,y); _delay_ms(150);

#define LED_PORT PORTB
#define LED_DDR DDRB
#define LED_PIN PB0

void static inline led_init()
{
	LED_DDR |= (1 << LED_PIN);
}

void static inline led_on()
{
	BIT_SET(LED_PORT, LED_PIN);
}

void static inline led_off()
{
	BIT_CLEAR(LED_PORT, LED_PIN);
}

void main(void)
{
	uint8_t a, i;
	
	led_init();
	led_on();
	
	m25p16_init();
	
	m25p16_write_enable();
	m25p16_sector_erase(0x00, 0x02, 0x00);
	m25p16_wait_for_operation();
	
	m25p16_write_enable();
	m25p16_write_begin(0x00, 0x02, 0x00);
	m25p16_write_byte(0x01);
	m25p16_write_byte(0x55);
	m25p16_write_byte(0xaa);
	m25p16_write_byte(0x42);
	m25p16_write_end();
	m25p16_wait_for_operation();
	
	m25p16_read_begin(0x00, 0x02, 0x00);
	m25p16_read_byte();
	m25p16_read_byte();
	m25p16_read_byte();
	m25p16_read_byte();
	m25p16_read_end();
	
	led_off();
	
	while (1)
	{
	}
}
