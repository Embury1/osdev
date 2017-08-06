#ifndef _GDT_H_
#define _GDT_H_

struct gdt {
    unsigned short size;
    unsigned int address;
} __attribute__((packed));

#endif