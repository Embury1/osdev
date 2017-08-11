#include "lib/stdint.h"
#include "io.h"

/* Master PIC */
#define PIC1_COMMAND_PORT       0x20
#define PIC1_DATA_PORT          0x21
#define PIC1_OFFSET             0x20
#define PIC1_TO_PIC2            0x04

/* Slave PIC */
#define PIC2_COMMAND_PORT       0xA0
#define PIC2_DATA_PORT          0xA1
#define PIC2_OFFSET             0x28
#define PIC2_END                PIC2_OFFSET + 7
#define PIC2_TO_PIC1            0x02

#define PIC_EOI                 0x20                /* End-of-interrupt command code */
#define PIC_8086                0x01

void pic_send_eoi(uint32_t interrupt)
{
    if (interrupt < PIC1_OFFSET || interrupt > PIC2_END)
        return;
    
    if (interrupt >= PIC2_OFFSET)
        outb(PIC2_COMMAND_PORT, PIC_EOI);

    outb(PIC1_COMMAND_PORT, PIC_EOI);
}

void pic_init()
{
    /* Restart the PICs */
    outb(PIC1_COMMAND_PORT, PIC_EOI);
    outb(PIC2_COMMAND_PORT, PIC_EOI);

    /* Set vector offsets */
    outb(PIC1_DATA_PORT, PIC1_OFFSET);
    outb(PIC2_DATA_PORT, PIC2_OFFSET);

    /* Setup cascading */
    outb(PIC1_DATA_PORT, PIC1_TO_PIC2);
    outb(PIC2_DATA_PORT, PIC2_TO_PIC1);

    /* Set 8085 mode */
    outb(PIC1_DATA_PORT, PIC_8086);
    outb(PIC2_DATA_PORT, PIC_8086);
}