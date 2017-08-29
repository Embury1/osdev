#include "lib/stddef.h"
#include "lib/stdint.h"
#include "fb.h"
#include "gdt.h"
#include "idt.h"
#include "keyboard.h"
#include "pic.h"
#include "serial.h"
#include "interrupt.h"
#include "log.h"
#include "multiboot.h"

typedef void (*call_module_t) (void);

void kmain(uint32_t ebx)
{
    call_module_t start_program = NULL;
    multiboot_info_t *mb_info = (multiboot_info_t *) ebx;

    disable_interrupts();

    fb_clear();
    fb_write("Welcome to EmbOS", FB_BLACK, FB_LIGHT_BLUE);
    fb_move_cursor(16, 0);

    gdt_init();
    idt_init();
    pic_init();
    kbd_init();
    
    serial_configure_baud_rate(SERIAL_COM1_BASE, 0x03);
    serial_configure_line(SERIAL_COM1_BASE);

    enable_interrupts();

    if ((mb_info->flags & 4) == 4 && mb_info->mods_count == 1) {
        uint32_t *module = (uint32_t *) mb_info->mods_addr;
        log_debug("kmain", "module found at address %x", module[0]);
        log_debug("kmain", "what is this set to? %x", module[1]);
        if (module[2])
            log_debug("kmain", "%s", module[2]);
        start_program = (call_module_t) module;
        start_program();
    } else if (mb_info->mods_count > 1) {
        log_error("kmain", "more than one module found");
    } else {
        log_error("kmain", "no modules found");
    }
}