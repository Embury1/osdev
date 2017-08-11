#include "lib/stdint.h"
#include "fb.h"
#include "gdt.h"
#include "idt.h"
#include "pic.h"
#include "serial.h"


void kmain()
{
    fb_clear();
    fb_write((uint8_t *) "Welcome to EmbOS", FB_BLACK, FB_LIGHT_BLUE);
    fb_move_cursor(16, 0);

    serial_configure_baud_rate(SERIAL_COM1_BASE, 0x03);
    serial_configure_line(SERIAL_COM1_BASE);
    serial_write(SERIAL_COM1_BASE, (uint8_t *) "[DEBUG] COM1 initialized");

    gdt_init();
    idt_init();
    pic_init();
}