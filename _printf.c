#include "main.h"
#include <stdio.h>
#include <stdarg.h>

int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;

    va_start(args, format);

    while (*format)
    {
        if (*format != '%')
        {
            putchar(*format);
            count++;
        }
        else
        {
            format++;
            if (*format == '\0')
                break;
            if (*format == 'c')
            {
                char character = va_arg(args, int);
                putchar(character);
                count++;
            }
            else if (*format == 's')
            {
                char *string = va_arg(args, char *);
                if (string == NULL)
                    string = "(null)";
                while (*string)
                {
                    putchar(*string);
                    string++;
                    count++;
                }
            }
            else if (*format == '%')
            {
                putchar('%');
                count++;
            }
            else
            {
                putchar('%');
                putchar(*format);
                count += 2;
            }
        }
        format++;
    }

    va_end(args);

    return count;
}
