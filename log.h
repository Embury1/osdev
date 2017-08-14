#ifndef _LOG_H_
#define _LOG_H_

#include "lib/stdarg.h"
#include "lib/stdint.h"

void log_debug(char *, char *, ...);
void log_info(char *, char *, ...);
void log_error(char *, char *, ...);

#endif /* _LOG_H_ */    