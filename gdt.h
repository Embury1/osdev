#ifndef _GDT_H_
#define _GDT_H_

#include "lib/stdint.h"

#define PL0 0x0
#define PL3 0x3

void gdt_init();

#endif