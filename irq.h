#ifndef _IRQ_H_
#define _IRQ_H_

#define PIC1_IRQ_0      0x0     /* system timer */
#define PIC1_IRQ_1      0x1     /* keyboard controller */
#define PIC1_IRQ_3      0x3     /* serial port COM 2 */
#define PIC1_IRQ_4      0x4     /* serial port COM 1 */
#define PIC1_IRQ_5      0x5     /* line print terminal 2 */
#define PIC1_IRQ_6      0x6     /* floppy controller */
#define PIC1_IRQ_7      0x7     /* line print terminal 1 */
#define PIC2_IRQ_8      0x0     /* RTC timer */
#define PIC2_IRQ_12     0x4     /* mouse controller */
#define PIC2_IRQ_13     0x5     /* math co-processor */
#define PIC2_IRQ_14     0x6     /* ATA channel 1 */
#define PIC2_IRQ_15     0x7     /* ATA channel 2 */

#endif /* _IRQ_H_ */