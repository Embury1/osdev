#include "io.h"
#include "fb.h"

#define FB_COLUMNS              80
#define FB_ROWS                 25

#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

static char *fb = (char *) 0x000B8000;
static uint16_t cursor_pos;

static void set_cursor(uint16_t pos)
{
    outb(FB_COMMAND_PORT,   FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,      ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT,   FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,      pos & 0x00FF);
}

static void move_cursor(uint8_t col, uint8_t row)
{
    set_cursor(cursor_pos = row * FB_COLUMNS + col);
}

__attribute__((unused)) static void move_cursor_back()
{
    if (cursor_pos != 0) {
        set_cursor(--cursor_pos);
    }
}

__attribute__((unused)) static void move_cursor_forward()
{
    set_cursor(++cursor_pos);
}

static void new_line()
{
    cursor_pos += FB_COLUMNS;
    set_cursor(cursor_pos);
}

static void carriage_return()
{
    cursor_pos -= cursor_pos % FB_COLUMNS;
    set_cursor(cursor_pos);
}

static void fb_write_cell(char c, uint8_t bg, uint8_t fg)
{
    fb[cursor_pos * 2] = c;
    fb[cursor_pos * 2 + 1] = ((bg & 0x0F) << 4) | (fg & 0x0F);
}

void fb_write(char *c, uint8_t bg, uint8_t fg)
{
    char *p = c;
    for (cursor_pos = 0; *p != '\0'; p++) {
        if (*p == '\n') {
            new_line();
            carriage_return();
        } else {
            fb_write_cell(*p, bg, fg);
            cursor_pos++;
        }
    }
    set_cursor(cursor_pos);
}

void fb_clear()
{
    uint32_t i, j;

    for (i = 0; i < FB_ROWS; ++i) {
        for (j = 0; j < FB_COLUMNS; ++j) {
            cursor_pos = i * FB_COLUMNS + j;
            fb_write_cell(' ', FB_BLACK, FB_WHITE);
        }
    }

    move_cursor(0, 0);
}