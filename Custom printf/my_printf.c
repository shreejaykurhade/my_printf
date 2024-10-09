#include <unistd.h>
#include <stddef.h>

// Custom va_list macros
typedef char* va_list;

#define _INTSIZEOF(n) ((sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1))
#define va_start(ap, v) (ap = (va_list)&v + _INTSIZEOF(v))
#define va_arg(ap, type) (*(type *)((ap += _INTSIZEOF(type)) - _INTSIZEOF(type)))
#define va_end(ap) (ap = (va_list)0)

#define Wait4char 1   // 0001 
#define Wait4fmt  2   // 0010

typedef unsigned char State;

// Helper function to reverse a string
void reverse(char *str) {
    int len = 0, i;
    while (str[len]) len++;
    for (i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

// Function to convert integers to string
void itoa(int num, char *buffer) {
    int i = 0, is_negative = 0;
    if (num == 0) {
        buffer[i++] = '0';
    } else if (num < 0) {
        is_negative = 1;
        num = -num;
    }
    while (num != 0) {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }
    if (is_negative) {
        buffer[i++] = '-';
    }
    buffer[i] = '\0';
    reverse(buffer);
}

// Function to convert unsigned integers to string
void utoa(unsigned int num, char *buffer) {
    int i = 0;
    if (num == 0) {
        buffer[i++] = '0';
    }
    while (num != 0) {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }
    buffer[i] = '\0';
    reverse(buffer);
}

// Convert integer to hexadecimal string
void itoh(unsigned int num, char *buffer, int uppercase) {
    const char *hex = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
    int i = 0;
    do {
        buffer[i++] = hex[num % 16];
        num /= 16;
    } while (num);
    buffer[i] = '\0';
    reverse(buffer);
}

// Convert integer to octal string
void itoo(unsigned int num, char *buffer) {
    int i = 0;
    do {
        buffer[i++] = (num % 8) + '0';
        num /= 8;
    } while (num);
    buffer[i] = '\0';
    reverse(buffer);
}

// Convert float to string
void ftoa(double num, char *buffer, int precision) {
    int int_part = (int)num;
    double frac_part = num - int_part;
    itoa(int_part, buffer);

    if (precision > 0) {
        char *p = buffer;
        while (*p) p++;  // Move to the end of the string
        *p++ = '.';

        for (int i = 0; i < precision; i++) {
            frac_part *= 10;
        }
        itoa((int)frac_part, p);
    }
}

// Custom malloc implementation
#define HEAP_SIZE 1024
static char heap[HEAP_SIZE];
static size_t heap_index = 0;

void *my_malloc(size_t size) {
    if (heap_index + size > HEAP_SIZE) {
        return NULL; // Out of memory
    }
    void *ptr = &heap[heap_index];
    heap_index += size;
    return ptr;
}

// Function to output a single character using write()
#define putchar(x)  write(1, chardup(x), 1)
char *chardup(const char c) {
    static char buf[2]; // buffer of 2 bytes
    buf[0] = c;
    buf[1] = '\0';
    return buf;
}

// Function to output strings
unsigned int strlen(const char *str) {
    unsigned int count = 0;
    while (*str++) count++;
    return count;
}

void puts(const char *str) {
    unsigned int n = strlen(str);
    if (n > 0) {
        write(1, str, n);
    }
}

// The custom printf implementation
int printf(const char *fmt, ...) {
    va_list args;
    char *buffer = (char*)my_malloc(100);  // Dynamic buffer for conversions
    const char *p;
    va_start(args, fmt);

    for (p = fmt; *p; p++) {
        if (*p == '%') {
            p++;  // Move to the format specifier
            int width = 0;
            int left_align = 0;
            int zero_pad = 0;

            // Parse flags
            if (*p == '-') {
                left_align = 1;
                p++;
            }
            if (*p == '0') {
                zero_pad = 1;
                p++;
            }

            // Parse field width
            while (*p >= '0' && *p <= '9') {
                width = width * 10 + (*p - '0');
                p++;
            }

            switch (*p) {
                case 's': {
                    char *str_arg = va_arg(args, char*);
                    puts(str_arg);
                    break;
                }
                case 'd': {
                    int int_arg = va_arg(args, int);
                    itoa(int_arg, buffer);
                    puts(buffer);
                    break;
                }
                case 'u': {
                    unsigned int uint_arg = va_arg(args, unsigned int);
                    utoa(uint_arg, buffer);
                    puts(buffer);
                    break;
                }
                case 'x': {
                    unsigned int hex_arg = va_arg(args, unsigned int);
                    itoh(hex_arg, buffer, 0);
                    puts(buffer);
                    break;
                }
                case 'X': {
                    unsigned int hex_arg = va_arg(args, unsigned int);
                    itoh(hex_arg, buffer, 1);
                    puts(buffer);
                    break;
                }
                case 'o': {
                    unsigned int octal_arg = va_arg(args, unsigned int);
                    itoo(octal_arg, buffer);
                    puts(buffer);
                    break;
                }
                case 'f': {
                    double float_arg = va_arg(args, double);
                    ftoa(float_arg, buffer, 6);  // Default precision = 6
                    puts(buffer);
                    break;
                }
                case 'c': {
                    char char_arg = (char)va_arg(args, int);  // Char promoted to int in variadic args
                    putchar(char_arg);
                    break;
                }
                case 'p': {
                    unsigned long ptr_arg = (unsigned long)va_arg(args, void*);
                    puts("0x");
                    itoh(ptr_arg, buffer, 0);
                    puts(buffer);
                    break;
                }
                case '%': {
                    putchar('%');
                    break;
                }
                default: {
                    putchar('%');
                    putchar(*p);
                    break;
                }
            }
        } else {
            putchar(*p);  // Output regular characters
        }
    }
    va_end(args);
    return 0;
}

int main() {
    printf("String: %s\n", "Hell oWorld");
    printf("Integer: %d\n", 12345);
    printf("Unsigned: %u\n", 54321);
    printf("Hex: %x\n", 255);
    printf("Octal: %o\n", 255);
    printf("Float: %f\n", 123.456);
    printf("Char: %c\n", 'A');
    printf("Pointer: %p\n", &main);
    printf("Literal Percent: %%\n");

    return 0;
}
