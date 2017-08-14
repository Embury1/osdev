#ifndef _SERIAL_H_
#define _SERIAL_H_

#include "lib/stdint.h"

#define SERIAL_COM1_BASE        0x3F8

void serial_configure_baud_rate(uint16_t, uint16_t);
void serial_configure_line(uint16_t);
int32_t serial_is_transmit_fifo_empty(uint16_t);
void serial_write(uint16_t, char);

#endif