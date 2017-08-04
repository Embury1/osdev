#include "io.h"

#define FB_BLACK                0
#define FB_BLUE                 1
#define FB_GREEN                2
#define FB_CYAN                 3
#define FB_RED                  4
#define FB_MAGENTA              5
#define FB_BROWN                6
#define FB_LIGHT_GREY           7
#define FB_DARK_GREY            8
#define FB_LIGHT_BLUE           9
#define FB_LIGHT_GREEN          10
#define FB_LIGHT_CYAN           11
#define FB_LIGHT_RED            12
#define FB_LIGHT_MAGENTA        13
#define FB_LIGHT_BROWN          14
#define FB_WHITE                15

#define FB_COLUMNS              80
#define FB_ROWS                 25

#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

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

void kmain()
{
    fb_clear();
    fb_write("Welcome to EmbOS", FB_BLACK, FB_LIGHT_BLUE);
    fb_move_cursor(16, 0);
}