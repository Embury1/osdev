#ifndef _SERIAL_H_
#define _SERIAL_H_

#define SERIAL_COM1_BASE        0x3F8

void serial_configure_baud_rate(unsigned short com, unsigned short divisor);
void serial_configure_line(unsigned short com);
int serial_is_transmit_fifo_empty(unsigned short com);
void serial_write(unsigned short com, char *c);

#endif