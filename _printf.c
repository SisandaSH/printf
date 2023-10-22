#include "main.h"
#include <stdarg.h>
#include <unistd.h>

/**
 * _printf - Custom printf function
 * @format: The format string
 *
 * Return: the number of characters printed (excluding the null byte)
 */
int _printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    int printed_chars = 0;
    int buffer_index = 0;
    char buffer[BUFF_SIZE];

    while (*format)
    {
        if (*format != '%')
        {
            buffer[buffer_index++] = *format;
            if (buffer_index == BUFF_SIZE - 1)
            {
                write(1, buffer, buffer_index);
                printed_chars += buffer_index;
                buffer_index = 0;
            }
            else
            {
                printed_chars++;
            }
        }
        else
        {
            format++; /* Move past '%' */
            if (*format == '\0')
                break;

            switch (*format)
            {
                case 'c':
                {
                    char c = va_arg(args, int);
                    buffer[buffer_index++] = c;
                    if (buffer_index == BUFF_SIZE - 1)
                    {
                        write(1, buffer, buffer_index);
                        printed_chars += buffer_index;
                        buffer_index = 0;
                    }
                    else
                    {
                        printed_chars++;
                    }
                    break;
                }

                case 's':
                {
                    char *str = va_arg(args, char *);
                    if (str == NULL)
                        str = "(null)";

                    while (*str)
                    {
                        buffer[buffer_index++] = *str;
                        if (buffer_index == BUFF_SIZE - 1)
                        {
                            write(1, buffer, buffer_index);
                            printed_chars += buffer_index;
                            buffer_index = 0;
                        }
                        else
                        {
                            printed_chars++;
                        }
                        str++;
                    }
                    break;
                }

                case '%':
                {
                    buffer[buffer_index++] = '%';
                    if (buffer_index == BUFF_SIZE - 1)
                    {
                        write(1, buffer, buffer_index);
                        printed_chars += buffer_index;
                        buffer_index = 0;
                    }
                    else
                    {
                        printed_chars++;
                    }
                    break;
                }

                default:
                {
                    buffer[buffer_index++] = '%';
                    buffer[buffer_index++] = *format;
                    if (buffer_index >= BUFF_SIZE - 2)
                    {
                        write(1, buffer, buffer_index);
                        printed_chars += buffer_index;
                        buffer_index = 0;
                    }
                    else
                    {
                        printed_chars += 2;
                    }
                }
            }
        }
        format++;
    }

    write(1, buffer, buffer_index);
    printed_chars += buffer_index;

    va_end(args);

    return printed_chars;
}
