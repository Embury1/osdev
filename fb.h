#ifndef _FB_H_
#define _FB_H_

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

void fb_write_cell(unsigned int i, char c, unsigned char bg, unsigned char fg);
void fb_write(char *c, unsigned char bg, unsigned char fg);
void fb_move_cursor(unsigned short col, unsigned short row);
void fb_clear();

#endif