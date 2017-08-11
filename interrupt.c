#include "lib/stddef.h"
#include "interrupt.h"
#include "serial.h"

static interrupt_handler_t interrupt_handlers[IDT_GATE_COUNT];

uint32_t register_interrupt_handler(uint32_t interrupt, interrupt_handler_t handler)
{
    if (interrupt > 255)
        return 1;
    
    if (interrupt_handlers[interrupt] != NULL)
        return 1;
    
    interrupt_handlers[interrupt] = handler;

    return 0;
}

void interrupt_handler(cpu_state_t cpu_state, idt_info_t info, stack_state_t stack_state)
{
    serial_write(SERIAL_COM1_BASE, (uint8_t *) "[DEBUG] interrupt_handler\n");
    if (interrupt_handlers[info.idt_index] != NULL) {
        serial_write(SERIAL_COM1_BASE, (uint8_t *) "[DEBUG] Found handler\n");
        interrupt_handlers[info.idt_index](cpu_state, info, stack_state);
    } else {
        /* log the unhandled interrupt */
        serial_write(SERIAL_COM1_BASE, (uint8_t *) "[ERROR] Unhandled interrupt\n");
    }
}