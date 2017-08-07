#include "gdt.h"
#include "serial.h"

#define SEGMENT_BASE        0
#define SEGMENT_LIMIT       0xFFFFF

#define CODE_RX_TYPE        0xA
#define DATA_RW_TYPE        0x2

#define GDT_ENTRIES_COUNT   5

struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));
typedef struct gdt_entry gdt_entry_t;

struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));
typedef struct gdt_ptr gdt_ptr_t;

void gdt_load(uint32_t);

static void gdt_create_entry(gdt_entry_t *gdt_entry, uint8_t pl, uint8_t type)
{
    gdt_entry->base_low      = (SEGMENT_BASE & 0xFFFF);
    gdt_entry->base_mid      = (SEGMENT_BASE >> 16) & 0xFF;
    gdt_entry->base_high     = (SEGMENT_BASE >> 24) & 0xFF;

    gdt_entry->limit_low     = (SEGMENT_LIMIT & 0xFFFF);

    gdt_entry->granularity   |= (0x01 << 7) | (0x01 << 6) | 0x0F;
    gdt_entry->access = (0x01 << 7) | ((pl & 0x03) << 5) | (0x01 << 4) | (type & 0x0F);
}

void gdt_init()
{
    gdt_entry_t gdt_entries[GDT_ENTRIES_COUNT];
    gdt_ptr_t gdt_ptr;

    gdt_ptr.limit = sizeof(gdt_entry_t) * GDT_ENTRIES_COUNT;
    gdt_ptr.base = (uint32_t)&gdt_entries;

    gdt_create_entry(&gdt_entries[0], 0, 0);
    gdt_create_entry(&gdt_entries[1], PL0, CODE_RX_TYPE);
    gdt_create_entry(&gdt_entries[2], PL0, DATA_RW_TYPE);
    gdt_create_entry(&gdt_entries[3], PL3, CODE_RX_TYPE);
    gdt_create_entry(&gdt_entries[4], PL3, DATA_RW_TYPE);

    gdt_load((uint32_t)&gdt_ptr);
}