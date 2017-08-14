#include "lib/stdint.h"
#include "fb.h"
#include "gdt.h"
#include "idt.h"
#include "keyboard.h"
#include "pic.h"
#include "serial.h"
#include "interrupt.h"
#include "log.h"

void kmain()
{
    disable_interrupts();

    fb_clear();
    fb_write((uint8_t *) "Welcome to EmbOS", FB_BLACK, FB_LIGHT_BLUE);
    fb_move_cursor(16, 0);

    serial_configure_baud_rate(SERIAL_COM1_BASE, 0x03);
    serial_configure_line(SERIAL_COM1_BASE);

    gdt_init();
    idt_init();
    pic_init();
    kbd_init();

    enable_interrupts();

    log_debug("kmain", "debug\n");
    log_info("kmain", "info\n");
    log_error("kmain", "error\n");

    log_debug("kmain", "%s %x %c\n", "string", 123, 'c');
}