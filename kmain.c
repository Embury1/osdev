#include "fb.h"

void kmain()
{
    fb_clear();
    fb_write("Welcome to EmbOS", FB_BLACK, FB_LIGHT_BLUE);
    fb_move_cursor(16, 0);
}