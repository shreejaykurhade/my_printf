# printf Function Without stdio.h
my_printf implements a simplified version of the printf function and a custom malloc function (my_malloc). The printf implementation supports various format specifiers (like %d, %x, %f, etc.), while the my_malloc function provides basic dynamic memory allocation. The goal is to illustrate how essential C library functions can be built from scratch.

## Features:
1. Supports basic format specifiers: %d (Signed integers), %u (Unsigned integers), %x or %X (Hexadecimal lowercase/uppercase), %o (Octal), %f (Floating-point numbers), %s (Strings), %c (Characters), %p (Pointers) and %% (Literal percent symbol) .
2. Manually implements variadic argument handling without the stdarg.h library.
3. Provides custom string handling (puts) and character output (putchar) using write() system calls.
4. Custom simplified malloc function to allocate memory using heap.

## Functions Overview

### 1. reverse
Reverses a given string in place.

Arguments:
- str: The string to reverse.

Returns:
- None (modifies the input string directly).

### 2. itoa
Converts an integer to a string (decimal format).

Arguments:
- num: The integer to convert.
- buffer: A pointer to the buffer where the converted string will be stored.

Returns:
- None (stores the result in buffer).

### 3. utoa
Converts an unsigned integer to a string.

Arguments:
- num: The unsigned integer to convert.
- buffer: A pointer to the buffer where the converted string will be stored.

Returns:
- None (stores the result in buffer).

### 4. itoh
Converts an unsigned integer to a hexadecimal string.

Arguments:
- num: The integer to convert.
- buffer: A pointer to the buffer where the result will be stored.
- uppercase: If non-zero, the hexadecimal digits will be in uppercase.

Returns:
- None (stores the result in buffer).

### 5. itoo
Converts an unsigned integer to an octal string.

Arguments:
- num: The unsigned integer to convert.
- buffer: A pointer to the buffer where the result will be stored.

Returns:
- None (stores the result in buffer).

### 6. ftoa
Converts a floating-point number to a string.

Arguments:
- num: The floating-point number to convert.
- buffer: A pointer to the buffer where the result will be stored.
- precision: The number of digits after the decimal point.

Returns:
- None (stores the result in buffer).

### 7. my_malloc
Custom memory allocation function.

Arguments:
- size: The size of memory to allocate (in bytes).

Returns:
- A pointer to the allocated memory.
- Returns NULL if the memory cannot be allocated due to insufficient space.

### 8. putchar
Outputs a single character using write().

Arguments:
- x: The character to output.

Returns:
- None.

### 9. puts
Outputs a string using write().

Arguments:
- str: The string to output.

Returns:
- None.

### 10. strlen
Calculates the length of a string.

Arguments:
- str: The string whose length is to be calculated.

Returns:
- The length of the string (number of characters).

### 11. printf
A custom implementation of the printf function, supporting various format specifiers.

Arguments:
- fmt: The format string containing conversion specifiers.
- ... : Variable arguments depending on the format specifiers in fmt.

Returns:
- Always returns 0 (can be customized as needed).

## Variables Overview
### heap
A static array representing the heap memory (size: 1024 bytes) used by my_malloc to allocate memory.

### heap_index
Keeps track of the current position in the heap for memory allocation.

### buffer
A dynamic buffer allocated by my_malloc for temporary storage in functions like printf.

### State
A custom typedef representing the state of the program during parsing (Wait4char, Wait4fmt).

## Custom Functions:
### reverse
Purpose: This function reverses a string in place.
- Logic:
1. First, the function calculates the length of the input string.
2. It then swaps characters starting from both ends of the string, working towards the center. This process continues until all characters are reversed.

Example:
```ruby
char str[] = "hello";
reverse(str);  // After execution, str will be "olleh"
```

### itoa (Integer to ASCII)
Purpose: Converts an integer (int) into a string representation. It handles both positive and negative numbers.
- Logic:
1. If the number is 0, the function directly stores '0' in the buffer.
2. If the number is negative, the negative sign is stored in the buffer, and the number is converted to positive for further processing.
3. The function extracts digits by performing num % 10 to get the least significant digit and stores it in reverse order in the buffer.
4. Once all digits are extracted, the buffer is reversed to obtain the correct string representation of the number.

Example:
```ruby
char buffer[20];
itoa(-12345, buffer);  // buffer will contain "-12345"
```

### utoa (Unsigned Integer to ASCII)
Purpose: Converts an unsigned integer into its string representation in base 10 (decimal).
- Logic:
1. Works similarly to itoa but without handling negative numbers.
2. The number is repeatedly divided by 10, and digits are extracted from least significant to most significant. The extracted digits are stored in reverse order in the buffer.
3. The result is reversed to get the correct order of digits.

Example:
```ruby
char buffer[20];
utoa(54321, buffer);  // buffer will contain "54321"
```

### itoh (Integer to Hexadecimal)
Purpose: Converts an unsigned integer to its hexadecimal string representation.
- Logic:
1. Each digit of the number is extracted by performing num % 16. This produces a value between 0-15, which is mapped to hexadecimal characters (0-9 and a-f/A-F).
2. The digits are stored in reverse order in the buffer.
3. The buffer is then reversed to give the correct hexadecimal string.

Example:
```ruby
char buffer[20];
itoh(255, buffer, 0);  // buffer will contain "ff"
```

### itoo (Integer to Octal)
Purpose: Converts an unsigned integer to its octal string representation.
- Logic:
1. The number is repeatedly divided by 8, and the remainder (num % 8) gives the octal digits.
2. The digits are stored in reverse order in the buffer.
3. Finally, the buffer is reversed to obtain the correct octal string.

Example:
```ruby
char buffer[20];
itoo(255, buffer);  // buffer will contain "377"
```

### ftoa (Float to ASCII)
Purpose: Converts a floating-point number into its string representation with a specified precision.
- Logic:
1. The integer part of the floating-point number is extracted and converted to a string using itoa.
2. The fractional part is multiplied by 10^precision, effectively shifting the decimal point to the right.
3. The fractional part is then converted to an integer and appended to the buffer after a decimal point.

Example:
```ruby
char buffer[50];
ftoa(123.456, buffer, 3);  // buffer will contain "123.456"
```

### my_malloc
Purpose: Implements a basic memory allocation system using a statically allocated heap.
- Logic:
1. The heap is defined as a static array of bytes (char heap[HEAP_SIZE]).
2. The heap_index keeps track of the current position of the unallocated memory within the heap.
3. When my_malloc is called, it checks if the requested memory size can fit in the remaining heap space.
4. If there’s enough space, it increments the heap_index by the requested size and returns a pointer to the newly allocated memory. If not, it returns NULL.

Example:
```ruby
char *buffer = (char *)my_malloc(50);  // Allocates 50 bytes from the custom heap
if (buffer != NULL) {
    // Use the buffer
}
```

### putchar
Purpose: Outputs a single character to the console using the write system call.
- Logic:
1. This function uses write to output a single byte (the character) to file descriptor 1, which is the standard output.

Example:
```ruby
putchar('A');  // Prints 'A' to the console
```

### puts
Purpose: Outputs a string to the console using the write system call.
- Logic:
1. The function first calculates the string length using strlen.
2. It then calls write to print the entire string to the console in one system call.

Example:
```ruby
puts("Hello, World!");  // Prints "Hello, World!" to the console
```

### strlen
Purpose: Calculates the length of a string (number of characters excluding the null terminator).
- Logic:
1. The function iterates through the string character by character until the null terminator ('\0') is encountered.
2. It returns the total number of characters.

Example:
```ruby
int length = strlen("hello");  // length will be 5
```

### printf
Purpose: This is the custom printf implementation that formats and prints strings, numbers, and other data types.
- Logic:
1. The function parses the format string to identify conversion specifiers (such as %d, %s, etc.).
2. For each conversion specifier, it fetches the corresponding argument using va_arg.
3. The argument is converted to a string using the appropriate function (e.g., itoa for integers).
4. The converted string is printed to the console using puts or putchar.
5. Supported format specifiers:

  #### %s - String
  #### %d - Signed decimal integer
  #### %u - Unsigned decimal integer
  #### %x - Hexadecimal integer (lowercase)
  #### %X - Hexadecimal integer (uppercase)
  #### %o - Octal integer
  #### %f - Floating-point number
  #### %c - Character
  #### %p - Pointer
  #### %% - Literal percent symbol

Example:
```ruby
printf("Integer: %d, String: %s\n", 42, "Hello");  
// Output: "Integer: 42, String: Hello"
```

## Memory Management
The custom my_malloc function provides dynamic memory allocation using a statically allocated heap of size 1024 bytes by default. The heap is managed internally, and memory blocks are allocated sequentially. No memory deallocation (free) is implemented in this version, so the heap can be exhausted if too many allocations are made.

Example of Memory Allocation:
```ruby
char *dynamic_buffer = (char *)my_malloc(50);  // Allocates 50 bytes
if (dynamic_buffer != NULL) {
    // Use dynamic_buffer
}
```

Code Flow
- Input Parsing: The printf function parses the format string to identify conversion specifiers.
- Argument Handling: For each conversion specifier, the appropriate function (itoa, utoa, etc.) is called to convert the argument into a string.
- Dynamic Memory Allocation: Whenever temporary buffers are needed, they are allocated using my_malloc.
- Output: The converted strings are printed to the console using puts or putchar.

## Compilation and Execution
To compile the project:
```ruby
gcc -o custom_printf custom_printf.c
./custom_printf
```

## Notes
- Memory Deallocation: Implementing a my_free function to allow deallocation of memory.
- Error Handling: Improve error handling in the my_malloc function for cases where allocation fails.
- Support for More Format Specifiers: Expand the printf function to support additional specifiers such as %e (scientific notation), %g, and field width/precision specifiers.

# How It Works (Demo Program):
```ruby
#include <unistd.h>
#include <stdarg.h>  // For handling variadic arguments
#include <stdbool.h> // For boolean logic (true/false)

// Bitwise flag for state machine
#define Wait4char   1   // 0001 bitwise flag
#define Wait4fmt    2   // 0010 bitwise flag

typedef unsigned char State;

// function macro for putchar (writing 1 character to stdout)
#define putchar(x)  write(1, chardup(x), 1)

// Helper function to duplicate a single character as a string
char *chardup(const char c) {
    static char buf[2];
    buf[0] = c;
    buf[1] = '\0';  // Null-terminate the string
    return buf;
}

// Helper function to compute string length
unsigned int strlen(const char *str) {
    unsigned int count = 0;
    while (*str++) count++;  // Increment count until null-terminator is reached
    return count;
}

// Helper function to output a string
void puts(const char *str) {
    unsigned int n = strlen(str);
    if (n > 0) {
        write(1, str, n);  // Write the string to stdout
    }
}

// Convert an integer to string
void itoa(int num, char *buffer) {
    char *p = buffer;
    bool is_negative = (num < 0);

    if (is_negative) {
        num = -num;
        *p++ = '-';
    }

    char *start = p;

    do {
        *p++ = (num % 10) + '0';
        num /= 10;
    } while (num > 0);

    *p-- = '\0';

    // Reverse the digits in buffer
    while (start < p) {
        char temp = *start;
        *start++ = *p;
        *p-- = temp;
    }
}

// Convert a float to string with a given precision (number of decimal places)
void ftoa(float num, char *buffer, int precision) {
    int whole = (int)num;
    itoa(whole, buffer);  // Convert the integer part

    while (*buffer) buffer++;  // Move to the end of the integer string
    *buffer++ = '.';  // Add decimal point

    num = num - whole;  // Get the fractional part
    for (int i = 0; i < precision; i++) {
        num *= 10;
        *buffer++ = (int)num + '0';
        num -= (int)num;
    }
    *buffer = '\0';
}

// Handle the custom printf function for integers, floats, doubles, and strings
int printf(const char *fmt, ...) { // ... means can be infinite number of arguments passed
    va_list args;      // Declare a variable to hold the variable argument list from ...
    const char *p;     // Pointer for iterating through the format string
    char buffer[100];  // Buffer for number conversions

    va_start(args, fmt);  // Initialize the variable argument list

    // Loop through the format string
    for (p = fmt; *p; p++) {
        if (*p == '%') {  // Format specifier found
            p++;  // Move to the specifier character

            switch (*p) {
                case 's': {  // String
                    char *str_arg = va_arg(args, char*);
                    puts(str_arg);
                    break;
                }
                case 'd': {  // Integer
                    int int_arg = va_arg(args, int);  // extracts the next argument from the variadic argument list args that has been passed to the printf() function.
                    itoa(int_arg, buffer);  // Convert integer to string
                    puts(buffer);
                    break;
                }
                case 'f': {  // Float
                    double float_arg = va_arg(args, double);
                    ftoa(float_arg, buffer, 6);  // Convert float to string (6 decimal places)
                    puts(buffer);
                    break;
                }
                case 'c': {  // Character
                    char char_arg = (char)va_arg(args, int);  // Char promoted to int in variadic args
                    putchar(char_arg);
                    break;
                }
                case '%': {  // Literal '%'
                    putchar('%');
                    break;
                }
                default: {
                    putchar('%');  // Print '%' for unsupported formats
                    putchar(*p);   // Print the unsupported specifier
                    break;
                }
            }
        } else {
            putchar(*p);  // Print regular characters
        }
    }

    va_end(args);  // Clean up the variable argument list
    return 0;
}

int main() {
    // Testing the custom printf function
    printf("String: %s\n", "Hello, World!");
    printf("Integer: %d\n", 12345);
    printf("Float: %f\n", 123.456);
    printf("Character: %c\n", 'A');
    printf("Literal Percent: %%\n");
    printf("Here is input of %d %f %s %f ",2,24.232,"hello there",12.3333332);

    return 0;
}
```
The core logic revolves around processing the format string and variadic arguments manually using a custom implementation of va_list. Here’s an explanation of the components and logic:
  ### 1. Custom va_list Implementation:
  We define our own macros to simulate the behavior of va_list, va_start, va_arg, and va_end:

  - va_list is defined as a char*, a pointer to the location on the stack where the variable arguments are stored.
  - va_start initializes the va_list to point to the first argument after the fixed parameters.
  - va_arg retrieves the next argument from the list, moving the pointer to the next position.
  - va_end is used to clean up, though it’s optional.
      ```ruby
      typedef char* va_list;  // Define va_list as a char pointer

      #define _INTSIZEOF(n) ((sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1))  // Align size to int

      #define va_start(ap, v) (ap = (va_list)&v + _INTSIZEOF(v))  // Initialize va_list
      #define va_arg(ap, type) (*(type *)((ap += _INTSIZEOF(type)) - _INTSIZEOF(type)))  // Retrieve argument
      #define va_end(ap) (ap = (va_list)0)  // End va_list

      ```
  ### 2. Output Functions:
  - putchar(x): Outputs a single character to the console by duplicating it in a buffer and calling write().
  - puts(str): Outputs a string by calculating its length and calling write() with the entire string.
  ### 3. Helper Functions:
  - chardup(char): Converts a character into a null-terminated string to be printed with write().
  - itoa(int, char*): Converts an integer into a string (reverse order) and handles negative numbers.
  - ftoa(float, char*, int): Converts a float to a string with a given precision for decimal points.
  ### 4. Custom printf() Function:
  The printf() function takes a format string and a variable number of arguments. It processes each character in the format string:

  - If a % symbol is encountered, the function expects a format specifier and handles the corresponding argument (string, integer, float, or character).
  - Otherwise, it simply outputs the character.
      ```ruby
      if (*p == '%') {
      p++;  // Move to the format specifier
      switch (*p) {
          case 's': {
              char *str_arg = va_arg(args, char*);
              puts(str_arg);
              break;
          }
          case 'd': {
              int int_arg = va_arg(args, int);
              itoa(int_arg, buffer);  // Convert integer to string
              puts(buffer);
              break;
          }
          case 'f': {
              double float_arg = va_arg(args, double);
              ftoa(float_arg, buffer, 6);  // Convert float to string with precision
              puts(buffer);
              break;
          }
          case 'c': {
              char char_arg = (char)va_arg(args, int);  // Char promoted to int in variadic args
              putchar(char_arg);
              break;
          }
          case '%': {
              putchar('%');
              break;
          }
          default: {
              putchar('%');
              putchar(*p);  // Unsupported format
              break;
          }
        }
      } else {
      putchar(*p);  // Output regular characters
      }

      ```
  ## How to use it: 
  1. Clone or copy the code:
     - Place the code in a .c file (e.g., custom_printf.c).
     - 
  2. Compile the code using a C compiler (e.g., gcc):
      ```ruby
      gcc custom_printf.c -o my_printf
      ```

  3. Run the program:
      ```ruby
      ./my_printf
      ```

  4. Modify the main() function to test different inputs:
      ```ruby
      int main() {
      printf("String: %s\n", "Hello, World!");
      printf("Integer: %d\n", 12345);
      printf("Float: %f\n", 123.456);
      printf("Character: %c\n", 'A');
      printf("Literal Percent: %%\n");
      return 0;
      }
      ```

  ## Functions Breakdown:
  1. putchar(x): Outputs a single character using the write() system call.
  2. puts(str): Outputs a string by calculating its length and writing it to stdout.
  3. itoa(num, buffer): Converts an integer into a string, handles negative numbers, and reverses the digits in the string.
  4. ftoa(float, buffer, precision): Converts a floating-point number into a string, with a specified precision for the fractional part.
  5. printf(fmt, ...): Custom implementation of the printf function. It parses the format string and handles various data types using the custom variadic argument handling.

## Notes:
1. Precision for floats: You can adjust the number of decimal places for float formatting by modifying the precision parameter in the ftoa() function.
2. Expanding functionality: To handle more format specifiers (e.g., hex, octal), simply add more cases in the switch statement in printf().
    




      
