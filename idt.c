#include "lib/stdint.h"
#include "idt.h"

#define SEGSEL_KERNEL_CS                0x08

#define IDT_ENTRY_COUNT                 256

#define IDT_INTERRUPT_ENTRY_TYPE        0
#define IDT_TRAP_ENTRY_TYPE             1

#define IDT_CREATE_ENTRY(idx) \
    idt_create_entry(idx, (uint32_t) &interrupt_handler_##idx,\
                     IDT_TRAP_ENTRY_TYPE, PL0);

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

struct idt_entry {
    uint16_t base_low;
    uint16_t segsel;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_high;
} __attribute__((packed));
typedef struct idt_entry idt_entry_t;

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));
typedef struct idt_ptr idt_ptr_t;

extern void idt_load();

void idt_create_entry(idt_entry_t *idt_entry, uint32_t handler, uint8_t type, uint8_t pl)
{
    idt_entry->base_low = handler & 0x0000FFFF;
    idt_entry->base_high = (handler >> 16) & 0x0000FFFF;
    idt_entry->segsel = SEGSEL_KERNEL_CS;
    idt_entry->always0 = 0;
    idt_entry->flags = (0x01 << 7) | ((pl & 0x03) << 5) | (0x01 << 3) | (0x01 << 2) | (0x01 << 1) | type;
}

void idt_init()
{
    idt_entry_t idt_entries[IDT_CREATE_ENTRY];
    idt_ptr_t idt_ptr;
    
    idt_ptr.limit = IDT_ENTRY_COUNT * sizeof(idt_entry_t) - 1;
    idt_ptr.base = (uint32_t) &idt;

    IDT_CREATE_ENTRY(0);
}