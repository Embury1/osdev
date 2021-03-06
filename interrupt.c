#include "lib/stddef.h"
#include "interrupt.h"
#include "log.h"

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
    log_debug("interrupt_handler", "irq %x fired", info.idt_index);

    if (interrupt_handlers[info.idt_index] != NULL) {
        interrupt_handlers[info.idt_index](cpu_state, info, stack_state);
    } else {
        log_error("interrupt_handler", "unhandled interrupt %x", info.idt_index);
    }
}