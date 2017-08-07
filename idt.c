#include "lib/stdint.h"
#include "idt.h"

struct idt_entry {
    uint16_t offset_low;
    uint16_t offset_high;
    
} __attribute__((packed));