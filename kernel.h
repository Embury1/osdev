#ifndef _KERNEL_H_
#define _KERNEL_H_

#include "fb.h"

void panic(char *msg)
{
    fb_clear();
    fb_write("*** KERNEL PANIC ***\n", FB_BLACK, FB_RED);
    fb_write(msg, FB_BLACK, FB_RED);

    while (1)
        ;
}

#endif /* _KERNEL_H_ */