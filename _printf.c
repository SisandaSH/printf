#include <stdarg.h>
#include <stdio.h>

#define BUFF_SIZE 1024

void print_buffer(char *buffer, int *index) {
    if (*index > 0) {
        fwrite(buffer, sizeof(char), *index, stdout);
        *index = 0;
    }
}

void _printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    char buffer[BUFF_SIZE];
    int buffer_index = 0;

    while (*format != '\0') {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 'd':
                case 'i': {
                    int i = va_arg(args, int);
                    buffer_index += snprintf(buffer + buffer_index, BUFF_SIZE - buffer_index, "%d", i);
                    break;
                }
                case 's': {
                    char *s = va_arg(args, char*);
                    buffer_index += snprintf(buffer + buffer_index, BUFF_SIZE - buffer_index, "%s", s);
                    break;
                }
                default:
                    buffer[buffer_index++] = '%';
                    buffer[buffer_index++] = *format;
            }
        } else {
            buffer[buffer_index++] = *format;
        }

        if (buffer_index >= BUFF_SIZE) {
            print_buffer(buffer, &buffer_index);
        }

        format++;
    }

    print_buffer(buffer, &buffer_index);

    va_end(args);
}
