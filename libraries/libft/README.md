# 📚 Libft

[![42](https://img.shields.io/badge/42-Project-blue)](https://42.fr)
[![C](https://img.shields.io/badge/Language-C-green)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Build Status](https://img.shields.io/badge/Build-Passing-brightgreen)](https://github.com/lahermaciel/libft)

> A comprehensive C library implementing essential functions for 42 School projects and general C programming.

## 🚀 Overview

Libft is a custom C library that reimplements standard C library functions and provides additional utility functions. This library serves as the foundation for many 42 School projects and demonstrates proficiency in C programming, memory management, and algorithm implementation.

## ✨ Features

### 🔤 Character Functions
- **Character classification**: `ft_isalpha`, `ft_isdigit`, `ft_isalnum`, `ft_isascii`, `ft_isprint`
- **Character manipulation**: `ft_tolower`, `ft_toupper`
- **Whitespace detection**: `ft_isspace`

### 🧠 Memory Functions
- **Memory operations**: `ft_memset`, `ft_bzero`, `ft_memcpy`, `ft_memmove`, `ft_memchr`, `ft_memcmp`
- **Dynamic allocation**: `ft_calloc`, `ft_realloc`, `ft_realloc_and_clear`

### 📝 String Functions
- **String manipulation**: `ft_strlen`, `ft_strcpy`, `ft_strlcpy`, `ft_strlcat`, `ft_strdup`
- **String comparison**: `ft_strcmp`, `ft_strncmp`, `ft_strnstr`
- **String search**: `ft_strchr`, `ft_strrchr`
- **String creation**: `ft_substr`, `ft_strjoin`, `ft_strtrim`, `ft_strmapi`, `ft_striteri`
- **String splitting**: `ft_split`

### 🔧 Enhanced String Functions (Project-Specific)
- **`ft_strjoin2`**: Enhanced string joining with automatic memory management

### 🔢 Conversion Functions
- **Number conversion**: `ft_atoi`, `ft_itoa`

### 📤 Output Functions
- **Formatted output**: `ft_printf`, `ft_printf_fd`
- **Array printing**: `%a`, `%A`, `%t`, `%T` (space/newline separated, with/without quotes)
- **Basic output**: `ft_putchar_fd`, `ft_putstr_fd`, `ft_putendl_fd`, `ft_putnbr_fd`

### 🔗 Linked List Functions
- **List management**: `ft_lstnew`, `ft_lstadd_front`, `ft_lstadd_back`, `ft_lstsize`, `ft_lstlast`
- **List operations**: `ft_lstdelone`, `ft_lstclear`, `ft_lstiter`, `ft_lstmap`

### 📄 File I/O
- **Line reading**: `get_next_line` (bonus)

### 🛠️ Array Utilities
- **Array management**: `ft_arraylen`, `ft_free_array`, `ft_rm_from_array`, `ft_swap`

## 📁 Project Structure

```
libft/
├── include/
│   └── libft.h          # Main header file
├── src/
│   ├── ft_*.c           # All source files
│   └── get_next_line_*.c # Bonus files
├── Makefile             # Build configuration
├── README.md            # This file
└── test_libft.c         # Test suite
```

## 🏗️ Installation

### Prerequisites
- GCC compiler
- Make
- Standard C library

### Building the Library

```bash
# Clone the repository
git clone https://github.com/lahermaciel/libft.git
cd libft

# Build the library (includes automatic norminette check)
make

# Clean object files
make clean

# Clean everything (including norminette logs)
make fclean

# Rebuild
make re

# Run norminette check manually
make norm
```

The build process will create `libft.a`, a static library containing all the functions. **The build automatically runs norminette checking** to ensure code compliance with 42 School standards.

## 📖 Usage

### Including the Library

```c
#include "include/libft.h"
```

### Compiling with Libft

```bash
# Compile your program with libft
gcc -Wall -Wextra -Werror your_program.c -L. -lft

# Or specify the library directly
gcc -Wall -Wextra -Werror your_program.c libft.a
```

### Example Usage

```c
#include "include/libft.h"
#include <stdio.h>

int main(void)
{
    char *str = "Hello, World!";
    char *sub = ft_substr(str, 0, 5);
    
    printf("Original: %s\n", str);
    printf("Substring: %s\n", sub);
    
    free(sub);
    return (0);
}
```

## 🧪 Testing

The library includes comprehensive testing to ensure all functions work correctly:

```bash
# Run basic tests
make test

# Run memory tests with valgrind
make memtest

# Run norminette check manually
make norm
```

## 🔍 Build Process & Quality Assurance

### Automatic Norminette Checking
The build process includes automatic norminette checking to ensure 42 School compliance:

- **Automatic**: Norminette runs automatically after successful compilation
- **Silent**: Output is logged to `.norminette.log` for review
- **Smart**: Only shows errors if found, otherwise confirms compliance
- **Integrated**: Part of the main build process, not a separate step

### Build Flow
1. **Compilation**: Compiles all source files to object files
2. **Archiving**: Creates `libft.a` static library
3. **Quality Check**: Runs norminette validation
4. **Success**: Confirms library creation and compliance

### Make Targets

| Target | Description |
|--------|-------------|
| `make` | Build library with automatic norminette check |
| `make clean` | Remove object files |
| `make fclean` | Remove all generated files (including logs) |
| `make re` | Clean and rebuild |
| `make norm` | Run norminette check manually |
| `make test` | Run comprehensive tests |
| `make memtest` | Run memory tests with valgrind |

## 📋 Function Reference

### Character Functions
| Function | Description | Return Type |
|----------|-------------|-------------|
| `ft_isalpha` | Check if character is alphabetic | `int` |
| `ft_isdigit` | Check if character is digit | `int` |
| `ft_isalnum` | Check if character is alphanumeric | `int` |
| `ft_isascii` | Check if character is ASCII | `int` |
| `ft_isprint` | Check if character is printable | `int` |
| `ft_tolower` | Convert character to lowercase | `int` |
| `ft_toupper` | Convert character to uppercase | `int` |

### Memory Functions
| Function | Description | Return Type |
|----------|-------------|-------------|
| `ft_memset` | Fill memory with constant byte | `void *` |
| `ft_bzero` | Zero out memory | `void` |
| `ft_memcpy` | Copy memory area | `void *` |
| `ft_memmove` | Move memory area | `void *` |
| `ft_memchr` | Search for character in memory | `void *` |
| `ft_memcmp` | Compare memory areas | `int` |
| `ft_calloc` | Allocate and zero memory | `void *` |

### String Functions
| Function | Description | Return Type |
|----------|-------------|-------------|
| `ft_strlen` | Calculate string length | `size_t` |
| `ft_strcpy` | Copy string | `char *` |
| `ft_strlcpy` | Copy string with size limit | `size_t` |
| `ft_strlcat` | Concatenate string with size limit | `size_t` |
| `ft_strdup` | Duplicate string | `char *` |
| `ft_strchr` | Find first occurrence of character | `char *` |
| `ft_strrchr` | Find last occurrence of character | `char *` |
| `ft_strcmp` | Compare strings | `int` |
| `ft_strncmp` | Compare strings with length limit | `int` |
| `ft_strnstr` | Find substring in string | `char *` |
| `ft_substr` | Extract substring | `char *` |
| `ft_strjoin` | Concatenate strings | `char *` |
| `ft_strtrim` | Trim string | `char *` |
| `ft_split` | Split string into array | `char **` |
| `ft_strmapi` | Apply function to each character | `char *` |
| `ft_striteri` | Apply function to each character with index | `void` |

## 🔧 Enhanced Functions

This library includes both standard libft functions and enhanced versions for specific projects:

### ft_strjoin2 vs ft_strjoin
- **ft_strjoin**: Standard libft function with const parameters
- **ft_strjoin2**: Enhanced version with automatic memory management
  - Accepts non-const `char*` parameters
  - Includes memory management flags (1=frees s1, 2=frees s2, 3=frees both)
  - Handles NULL inputs gracefully
  - Uses `ft_calloc` for better memory safety

### Printf Array Format Specifiers
Both `ft_printf` and `ft_printf_fd` support special array format specifiers:
- **`%a`**: Print array elements separated by spaces
- **`%A`**: Print array elements in quotes, separated by spaces
- **`%t`**: Print array elements separated by newlines
- **`%T`**: Print array elements in quotes, separated by newlines

Example usage:
```c
char *arr[] = {"hello", "world", "test", NULL};
ft_printf("Array: %a\n", arr);        // Output: Array: hello world test 
ft_printf("Array: %A\n", arr);        // Output: Array: "hello" "world" "test" 
ft_printf("Array:\n%t\n", arr);       // Output: Array:\nhello\nworld\ntest\n
ft_printf("Array:\n%T\n", arr);       // Output: Array:\n"hello"\n"world"\n"test"\n
```

## 🎯 42 School Compliance

This library is designed to meet 42 School requirements:

- ✅ **Norme compliant**: Follows 42's coding standards (automatically verified)
- ✅ **Memory safe**: Proper memory allocation and deallocation
- ✅ **Error handling**: Robust error checking and NULL handling
- ✅ **Documentation**: Comprehensive function documentation
- ✅ **Testing**: Thoroughly tested functions
- ✅ **Quality assurance**: Automatic norminette checking in build process

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request. For major changes, please open an issue first to discuss what you would like to change.

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request


## 👨‍💻 Author

**Laher Maciel**
- GitHub: [@lahermaciel](https://github.com/lahermaciel)
- 42 School: [@lawences](https://profile-v3.intra.42.fr/users/lawences)

## 🙏 Acknowledgments

- 42 School for the project requirements and learning framework
- The C programming community for best practices and inspiration
- Contributors and reviewers who helped improve this library

---

<div align="center">
  <p>Made at Lisbon 42 School</p>
</div>
