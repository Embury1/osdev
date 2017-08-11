#include "lib/stdint.h"
#include "io.h"

#define PIC1_COMMAND_PORT       0x20
#define PIC2_COMMAND_PORT       0xA0

#define PIC1_DATA_PORT          PIC1_COMMAND_PORT + 1
#define PIC2_DATA_PORT          PIC2_COMMAND_PORT + 1

#define PIC1_ICW1               0x11                    /* Initialize the PIC and enable ICW4 */
#define PIC2_ICW1               PIC1_ICW2

#define PIC1_ICW2               0x20                    /* IRQ 0-7 mapped to IDT indexes 32-39 */
#define PIC2_ICW2               0x28                    /* IRQ 8-15 mapped to IDT indexes 40-47 */

#define PIC1_ICW3               0x04
#define PIC2_ICW3               0x02

#define PIC1_ICW4               0x01
#define PIC2_ICW4               PIC1_ICW4

#define PIC_EOI                 0x20                    /* End-of-interrupt command code */

void pic_send_eoi()
{
    outb(PIC1_COMMAND_PORT, PIC_EOI);
    outb(PIC2_COMMAND_PORT, PIC_EOI);
}

void pic_init()
{
    /* Restart the PICs */
    outb(PIC1_COMMAND_PORT, PIC1_ICW1);
    outb(PIC2_COMMAND_PORT, PIC2_ICW1);

    /* Set vector offsets */
    outb(PIC1_DATA_PORT, PIC1_ICW2);
    outb(PIC2_DATA_PORT, PIC2_ICW2);

    /* Setup cascading */
    outb(PIC1_DATA_PORT, PIC1_ICW3);
    outb(PIC2_DATA_PORT, PIC2_ICW3);

    /* Set 8085 mode */
    outb(PIC1_DATA_PORT, PIC1_ICW4);
    outb(PIC2_DATA_PORT, PIC2_ICW4);

    /* Mask IRQs */
    outb(PIC1_DATA_PORT, 0xEC);
    outb(PIC2_DATA_PORT, 0xFF);
}