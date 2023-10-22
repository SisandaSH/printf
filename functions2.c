#include "main.h"
#include <stdio.h>
#include <stdarg.h>

/**
 * _printf - Custom printf function
 * @format: The format string
 * @...: The variable arguments
 *
 * Return: The number of characters printed (excluding the null byte)
 */
int _printf(const char *format, ...)
{
    va_list args;
    int printed_chars = 0;

    va_start(args, format);

    while (*format)
    {
        if (*format != '%')
        {
            putchar(*format);
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
                putchar(c);
                printed_chars++;
            }
            else if (*format == 's')
            {
                char *str = va_arg(args, char *);
                if (str == NULL)
                    str = "(null)";
                while (*str)
                {
                    putchar(*str);
                    str++;
                    printed_chars++;
                }
            }
            else if (*format == '%')
            {
                putchar('%');
                printed_chars++;
            }
            else
            {
                putchar('%');
                putchar(*format);
                printed_chars += 2;
            }
        }
        format++;
    }

    va_end(args);

    return printed_chars;
}
