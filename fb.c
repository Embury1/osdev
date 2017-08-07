#include "io.h"
#include "fb.h"

char *fb = (char *) 0x000B8000;

void fb_write_cell(unsigned int i, char c, unsigned char bg, unsigned char fg)
{
    fb[i * 2] = c;
    fb[i * 2 + 1] = ((bg & 0x0F) << 4) | (fg & 0x0F);
}

void fb_write(char *c, unsigned char bg, unsigned char fg)
{
    unsigned int i = 0;
    char *p = 0;
    while (*(p = c + i) != '\0')
        fb_write_cell(i++, *p, bg, fg);
}

void fb_move_cursor(unsigned short col, unsigned short row)
{
    unsigned short pos = row * FB_COLUMNS + col;

    outb(FB_COMMAND_PORT,   FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,      ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT,   FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,      pos & 0x00FF);
}

void fb_clear()
{
    unsigned int i, j;
    for (i = 0; i < FB_ROWS; ++i) {
        for (j = 0; j < FB_COLUMNS; ++j) {
            fb_write_cell(i * FB_COLUMNS + j, ' ', FB_BLACK, FB_WHITE);
        }
    }
    fb_move_cursor(0, 0);
}