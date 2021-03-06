#include "gdt.h"
#include "serial.h"

#define SEGMENT_BASE        0
#define SEGMENT_LIMIT       0xFFFFF

#define CODE_RX_TYPE        0xA
#define DATA_RW_TYPE        0x2

#define GDT_ENTRIES_COUNT   4

#define TSS_SEGSEL          0x18

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

static gdt_entry_t gdt_entries[GDT_ENTRIES_COUNT];
static tss_t tss;

void gdt_load(uint32_t);
void tss_load(uint32_t);

static void gdt_create_entry(uint32_t n, uint8_t pl, uint8_t type)
{
    gdt_entries[n].base_low      = (SEGMENT_BASE & 0xFFFF);
    gdt_entries[n].base_mid      = (SEGMENT_BASE >> 16) & 0xFF;
    gdt_entries[n].base_high     = (SEGMENT_BASE >> 24) & 0xFF;

    gdt_entries[n].limit_low     = (SEGMENT_LIMIT & 0xFFFF);

    gdt_entries[n].granularity   |= (0x01 << 7) | (0x01 << 6) | 0x0F;
    gdt_entries[n].access = (0x01 << 7) | ((pl & 0x03) << 5) | (0x01 << 4) | (type & 0x0F);
}

static void tss_create_entry(uint32_t n, uint32_t tss_addr)
{
    gdt_entries[n].base_low     = (tss_addr & 0xFFFF);
    gdt_entries[n].base_mid     = (tss_addr >> 16) & 0xFF;
    gdt_entries[n].base_high    = (tss_addr >> 24) & 0xFF;

    gdt_entries[n].limit_low    = sizeof(tss_t) - 1;

    gdt_entries[n].access = (0x01 << 7) | (0x01 << 3) | (0x01);
    gdt_entries[n].granularity = 0;
}

void gdt_init()
{
    gdt_ptr_t gdt_ptr;

    gdt_ptr.limit = sizeof(gdt_entry_t) * GDT_ENTRIES_COUNT;
    gdt_ptr.base = (uint32_t)&gdt_entries;

    gdt_create_entry(0, 0, 0);
    gdt_create_entry(1, PL0, CODE_RX_TYPE);
    gdt_create_entry(2, PL0, DATA_RW_TYPE);
    // gdt_create_entry(3, PL3, CODE_RX_TYPE);
    // gdt_create_entry(4, PL3, DATA_RW_TYPE);
    tss_create_entry(3, (uint32_t) &tss);

    gdt_load((uint32_t)&gdt_ptr);

    tss_load(TSS_SEGSEL);
}

void tss_set_stack(uint16_t segsel, uint32_t addr)
{
    tss.esp0 = addr;
    tss.ss0 = segsel;
}