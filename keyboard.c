#include "fb.h"
#include "interrupt.h"
#include "io.h"
#include "keyboard.h"
#include "log.h"
#include "pic.h"

#define UNUSED_ARGUMENT(x)  (void) x;

#define KBD_BUFFER_SIZE     512
#define KBD_DATA_PORT       0x60
#define KBD_STATUS_PORT     0x64
#define KBD_IRQ             0x21

struct kbd_buffer {
    uint8_t buffer[KBD_BUFFER_SIZE];
    uint8_t *head;
    uint8_t *tail;
    uint32_t count;
};
typedef struct kbd_buffer kbd_buffer_t;
static kbd_buffer_t kbd_buffer;

uint8_t kbd_read_scancode()
{
    return inb(KBD_DATA_PORT);
}

void kbd_callback(cpu_state_t cpu_state, idt_info_t info, stack_state_t stack_state)
{
    UNUSED_ARGUMENT(cpu_state);
    UNUSED_ARGUMENT(info);
    UNUSED_ARGUMENT(stack_state);

    if (kbd_buffer.count < KBD_BUFFER_SIZE) {
        *kbd_buffer.tail++ = kbd_read_scancode();
        ++kbd_buffer.count;

        log_debug("kbd_callback", "Scancode read %x", kbd_buffer.tail);

        if (kbd_buffer.tail == kbd_buffer.buffer + KBD_BUFFER_SIZE)
            kbd_buffer.tail = kbd_buffer.buffer;
    }

    pic_send_eoi();
}

void kbd_clear_buffer()
{
    while ((inb(KBD_STATUS_PORT) & 1) == 1)
        inb(KBD_DATA_PORT);
}

void kbd_init()
{
    kbd_clear_buffer();

    register_interrupt_handler(KBD_IRQ, kbd_callback);

    kbd_buffer.count = 0;
    kbd_buffer.head = kbd_buffer.buffer;
    kbd_buffer.tail = kbd_buffer.buffer;
}