#include "lib/stdint.h"
#include "idt.h"
#include "interrupt.h"
#include "serial.h"

#define SEGSEL_KERNEL_CS                0x08

#define PL0                             0x0
#define PL3                             0x3

#define IDT_INTERRUPT_GATE_TYPE         0
#define IDT_TRAP_GATE_TYPE              1

#define IDT_TIMER_INTERRUPT_INDEX       0x20
#define IDT_KEYBOARD_INTERRUPT_INDEX    0x21

#define IDT_CREATE_GATE(idx) \
    idt_create_gate(idx, (uint32_t) &interrupt_handler_##idx,\
                     IDT_TRAP_GATE_TYPE, PL0);

#define DECLARE_INTERRUPT_HANDLER(i) void interrupt_handler_##i(void)

DECLARE_INTERRUPT_HANDLER(0);
DECLARE_INTERRUPT_HANDLER(1);
DECLARE_INTERRUPT_HANDLER(2);
DECLARE_INTERRUPT_HANDLER(3);
DECLARE_INTERRUPT_HANDLER(4);
DECLARE_INTERRUPT_HANDLER(5);
DECLARE_INTERRUPT_HANDLER(6);
DECLARE_INTERRUPT_HANDLER(7);
DECLARE_INTERRUPT_HANDLER(8);
DECLARE_INTERRUPT_HANDLER(9);
DECLARE_INTERRUPT_HANDLER(10);
DECLARE_INTERRUPT_HANDLER(11);
DECLARE_INTERRUPT_HANDLER(12);
DECLARE_INTERRUPT_HANDLER(12);
DECLARE_INTERRUPT_HANDLER(13);
DECLARE_INTERRUPT_HANDLER(14);
DECLARE_INTERRUPT_HANDLER(15);
DECLARE_INTERRUPT_HANDLER(16);
DECLARE_INTERRUPT_HANDLER(17);
DECLARE_INTERRUPT_HANDLER(18);
DECLARE_INTERRUPT_HANDLER(19);

DECLARE_INTERRUPT_HANDLER(32);
DECLARE_INTERRUPT_HANDLER(33);
DECLARE_INTERRUPT_HANDLER(34);
DECLARE_INTERRUPT_HANDLER(35);
DECLARE_INTERRUPT_HANDLER(36);
DECLARE_INTERRUPT_HANDLER(37);
DECLARE_INTERRUPT_HANDLER(38);
DECLARE_INTERRUPT_HANDLER(39);
DECLARE_INTERRUPT_HANDLER(40);
DECLARE_INTERRUPT_HANDLER(41);
DECLARE_INTERRUPT_HANDLER(42);
DECLARE_INTERRUPT_HANDLER(43);
DECLARE_INTERRUPT_HANDLER(44);
DECLARE_INTERRUPT_HANDLER(45);
DECLARE_INTERRUPT_HANDLER(46);
DECLARE_INTERRUPT_HANDLER(47);

struct idt_gate {
    uint16_t handler_low;
    uint16_t segsel;
    uint8_t always0;
    uint8_t flags;
    uint16_t handler_high;
} __attribute__((packed));
typedef struct idt_gate idt_gate_t;

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));
typedef struct idt_ptr idt_ptr_t;

extern void idt_load(uint32_t);

idt_gate_t idt_gates[IDT_GATE_COUNT];

static void idt_create_gate(uint8_t idx, uint32_t handler, uint8_t type, uint8_t pl)
{
    idt_gates[idx].handler_low = handler & 0x0000FFFF;
    idt_gates[idx].handler_high = (handler >> 16) & 0x0000FFFF;
    idt_gates[idx].segsel = SEGSEL_KERNEL_CS;
    idt_gates[idx].always0 = 0;
    idt_gates[idx].flags = (0x01 << 7) | ((pl & 0x03) << 5) | (0x01 << 3) | (0x01 << 2) | (0x01 << 1) | type;
}

void idt_init()
{
    idt_ptr_t idt_ptr;
    
    idt_ptr.limit = IDT_GATE_COUNT * sizeof(idt_gate_t) - 1;
    idt_ptr.base = (uint32_t) &idt_gates;

    /* Protected mode exceptions */
    IDT_CREATE_GATE(0);
    IDT_CREATE_GATE(1);
    IDT_CREATE_GATE(2);
    IDT_CREATE_GATE(3);
    IDT_CREATE_GATE(4);
    IDT_CREATE_GATE(5);
    IDT_CREATE_GATE(6);
    IDT_CREATE_GATE(7);
    IDT_CREATE_GATE(8);
    IDT_CREATE_GATE(9);
    IDT_CREATE_GATE(10);
    IDT_CREATE_GATE(11);
    IDT_CREATE_GATE(12);
    IDT_CREATE_GATE(13);
    IDT_CREATE_GATE(14);
    IDT_CREATE_GATE(15);
    IDT_CREATE_GATE(16);
    IDT_CREATE_GATE(17);
    IDT_CREATE_GATE(18);
    IDT_CREATE_GATE(19);

    /* IRQs */
    IDT_CREATE_GATE(32);
    IDT_CREATE_GATE(33);
    IDT_CREATE_GATE(34);
    IDT_CREATE_GATE(35);
    IDT_CREATE_GATE(36);
    IDT_CREATE_GATE(37);
    IDT_CREATE_GATE(38);
    IDT_CREATE_GATE(39);
    IDT_CREATE_GATE(40);
    IDT_CREATE_GATE(41);
    IDT_CREATE_GATE(42);
    IDT_CREATE_GATE(43);
    IDT_CREATE_GATE(44);
    IDT_CREATE_GATE(45);
    IDT_CREATE_GATE(46);
    IDT_CREATE_GATE(47);

    idt_load((uint32_t) &idt_ptr);
}