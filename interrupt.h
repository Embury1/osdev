#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

#include "lib/stdint.h"
#include "idt.h"

struct idt_info {
    uint32_t idt_index;
    uint32_t error_code;
} __attribute__((packed));
typedef struct idt_info idt_info_t;

struct cpu_state {
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t edx;
    uint32_t ecx;
    uint32_t ebx;
    uint32_t eax;
    uint32_t esp;
} __attribute__((packed));
typedef struct cpu_state cpu_state_t;

struct stack_state {
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t user_esp; /* not always safe to dereference! */
    uint32_t user_ss; /* not always safe to dereference! */
} __attribute__((packed));
typedef struct stack_state stack_state_t;

typedef void (*interrupt_handler_t)(cpu_state_t, idt_info_t, stack_state_t);

uint32_t register_interrupt_handler(uint32_t, interrupt_handler_t);

extern void enable_interrupts();
extern void disable_interrupts();

#endif