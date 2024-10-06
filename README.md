# printf Function Without stdio.h
This project implements a custom version of the printf() function in C without using the stdio.h library. Instead of relying on the standard va_list, va_start, va_arg, and va_end from stdarg.h, this code manually manages variable-length arguments, allowing the function to handle multiple argument types like strings, integers, floats, and characters.

## Features:
1. Supports basic format specifiers: %s (string), %d (integer), %f (float), %c (character), and %% (literal percent sign).
2. Manually implements variadic argument handling without the stdarg.h library.
3. Provides custom string handling (puts) and character output (putchar) using write() system calls.

## How It Works:
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
      gcc custom_printf.c -o custom_printf
      ```

  3. Run the program:
      ```ruby
      ./custom_printf
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

  ## Notes
  - Precision for floats: You can adjust the number of decimal places for float formatting by modifying the precision parameter in the ftoa() function.
  - Expanding functionality: To handle more format specifiers (e.g., hex, octal), simply add more cases in the switch statement in printf().
    




      
