#ifndef _M25P16_H_
#define _M25P16_H_

void m25p16_init();
void m25p16_write_enable();
void m25p16_write_disable();
void m25p16_sector_erase(uint8_t a3, uint8_t a2, uint8_t a1);
void m25p16_wait_for_operation();
void m25p16_write_begin(uint8_t a3, uint8_t a2, uint8_t a1);
void m25p16_write_byte(uint8_t data);
void m25p16_write_end();
void m25p16_read_begin(uint8_t a3, uint8_t a2, uint8_t a1);
uint8_t m25p16_read_byte();
void m25p16_read_end();

#endif