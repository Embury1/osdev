#include "log.h"
#include "serial.h"

#define LOG_PORT    SERIAL_COM1_BASE

static void _log_dec(uint32_t uival)
{
    char digits[] = "0123456789";
    
}

static void _log_hex(uint32_t uival)
{
    char digits[] = "0123456789ABCDEF";
    int res = uival;
    int rem = 0;
    char hex[16] = "";
    char *head = hex;
    char *tail = hex;

    do {
        rem = res % 16;
        res = res / 16;
        *head++ = digits[rem];
    } while (res > 0);

    *head-- = '\0';

    while (tail < head) {
        *tail ^= *head;
        *head ^= *tail;
        *tail ^= *head;
        ++tail;
        --head;
    }

    serial_write(LOG_PORT, '0');
    serial_write(LOG_PORT, 'x');

    for (head = hex; *head; head++)
        serial_write(LOG_PORT, *head);
}

static void _log_write(char *fmt, va_list args)
{
    uint32_t uival;
    char *sval;

    for (; *fmt; ++fmt) {
        if (*fmt != '%') {
            serial_write(LOG_PORT, *fmt);
            continue;
        }

        switch (*++fmt) {
        case 'c':
            uival = va_arg(args, uint32_t);
            serial_write(LOG_PORT, (uint8_t) uival);
            break;
        case 's':
            sval = va_arg(args, char *);
            for (; *sval; ++sval)
                serial_write(LOG_PORT, *sval);
            break;
        case 'd':
            break;
        case 'x':
            uival = va_arg(args, uint32_t);
            _log_hex(uival);
            break;
        case '%':
            serial_write(LOG_PORT, *fmt);
            break;
        }
    }
}

static void log_write(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    _log_write(fmt, args);
    va_end(args);
}

void log_debug(char *fn_name, char *fmt, ...)
{
    va_list args;
    log_write("[DEBUG] %s: ", fn_name);
    va_start(args, fmt);
    _log_write(fmt, args);
    va_end(args);
}

void log_info(char *fn_name, char *fmt, ...)
{
    va_list args;
    log_write("[INFO] %s: ", fn_name);
    va_start(args, fmt);
    _log_write(fmt, args);
    va_end(args);
}

void log_error(char *fn_name, char *fmt, ...)
{
    va_list args;
    log_write("[ERROR] %s: ", fn_name);
    va_start(args, fmt);
    _log_write(fmt, args);
    va_end(args);
}