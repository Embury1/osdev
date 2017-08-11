#include "lib/stdint.h"
#include "io.h"

#define PIC1_COMMAND_PORT       0x20
#define PIC1_DATA_PORT          0x21

#define PIC2_COMMAND_PORT       0xA0
#define PIC2_DATA_PORT          0xA1

/* The PIC interrupts have been remapped */
#define PIC1_START_INTERRUPT    0x20
#define PIC2_START_INTERRUPT    0x28
#define PIC2_END_INTERRUPT      PIC2_START_INTERRUPT + 7

#define PIC_ACK                 0x20

/** pic_aknowledge:
 *  Acknowledges an interrupt from either PIC 1 or PIC 2.
 *  
 *  @param interrupt The number of the interrupt
 */
void pic_aknowledge(uint32_t interrupt)
{
    if (interrupt < PIC1_START_INTERRUPT || interrupt > PIC2_END_INTERRUPT)
        return;
    
    if (interrupt < PIC2_START_INTERRUPT)
        outb(PIC1_COMMAND_PORT, PIC_ACK);
    else
        outb(PIC2_COMMAND_PORT, PIC_ACK);
}