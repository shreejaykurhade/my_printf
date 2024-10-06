### Project Overview: Custom printf Function Without stdio.h
This project implements a custom version of the printf() function in C without using the stdio.h library. Instead of relying on the standard va_list, va_start, va_arg, and va_end from stdarg.h, this code manually manages variable-length arguments, allowing the function to handle multiple argument types like strings, integers, floats, and characters.

## Features:
Supports basic format specifiers: %s (string), %d (integer), %f (float), %c (character), and %% (literal percent sign).
Manually implements variadic argument handling without the stdarg.h library.
Provides custom string handling (puts) and character output (putchar) using write() system calls.
# How It Works:
The core logic revolves around processing the format string and variadic arguments manually using a custom implementation of va_list. Here’s an explanation of the components and logic:

1. Custom va_list Implementation:
We define our own macros to simulate the behavior of va_list, va_start, va_arg, and va_end:

va_list is defined as a char*, a pointer to the location on the stack where the variable arguments are stored.
va_start initializes the va_list to point to the first argument after the fixed parameters.
va_arg retrieves the next argument from the list, moving the pointer to the next position.
va_end is used to clean up, though it’s optional.

# Macros:
```
typedef char* va_list;  // Define va_list as a char pointer

#define _INTSIZEOF(n) ((sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1))  // Align size to int

#define va_start(ap, v) (ap = (va_list)&v + _INTSIZEOF(v))  // Initialize va_list
#define va_arg(ap, type) (*(type *)((ap += _INTSIZEOF(type)) - _INTSIZEOF(type)))  // Retrieve argument
#define va_end(ap) (ap = (va_list)0)  // End va_list
```
2. Output Functions:
putchar(x): Outputs a single character to the console by duplicating it in a buffer and calling write().
puts(str): Outputs a string by calculating its length and calling write() with the entire string.
3. Helper Functions:
chardup(char): Converts a character into a null-terminated string to be printed with write().
itoa(int, char*): Converts an integer into a string (reverse order) and handles negative numbers.
ftoa(float, char*, int): Converts a float to a string with a given precision for decimal points.
4. Custom printf() Function:
The printf() function takes a format string and a variable number of arguments. It processes each character in the format string:

If a % symbol is encountered, the function expects a format specifier and handles the corresponding argument (string, integer, float, or character).
Otherwise, it simply outputs the character.
Example of handling different formats:
