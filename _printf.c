#include <stdarg.h>
#include <unistd.h>
#include "main.h"

int _printf(const char *format, ...)
{
    va_list args;
    int printed_chars = 0;

    va_start(args, format);

    while (*format)
    {
        if (*format != '%')
        {
            write(1, format, 1);
            printed_chars++;
        }
        else
        {
            format++;
            if (*format == '\0')
                break;
            if (*format == 'c')
            {
                char c = va_arg(args, int);
                write(1, &c, 1);
                printed_chars++;
            }
            else if (*format == 's')
            {
                char *str = va_arg(args, char *);
                if (str == NULL)
                    str = "(null)";
                while (*str)
                {
                    write(1, str, 1);
                    str++;
                    printed_chars++;
                }
            }
            else if (*format == '%')
            {
                write(1, "%", 1);
                printed_chars++;
            }
            else
            {
                write(1, "%", 1);
                write(1, format, 1);
                printed_chars += 2;
            }
        }
        format++;
    }

    va_end(args);

    return printed_chars;
}
