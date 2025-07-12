/* improved_printf.c - Better printf implementation */
#include "freebsd_compat.h"
#include <stdarg.h>

/* System call wrappers */
static long syscall1(long n, long a1) {
    long ret;
    asm volatile ("syscall" : "=a"(ret) : "a"(n), "D"(a1) : "rcx", "r11", "memory");
    return ret;
}

static long syscall3(long n, long a1, long a2, long a3) {
    long ret;
    asm volatile ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2), "d"(a3) : "rcx", "r11", "memory");
    return ret;
}

/* Basic write implementation */
ssize_t write(int fd, const void *buf, size_t count) {
    return syscall3(SYS_write, fd, (long)buf, count);
}

/* Exit implementation */
void exit(int status) {
    syscall1(SYS_exit, status);
    __builtin_unreachable();
}

/* Simple string length */
size_t strlen(const char *s) {
    size_t len = 0;
    while (s[len]) len++;
    return len;
}

/* Helper function to convert integer to string */
static int int_to_string(int num, char *str) {
    int i = 0;
    int is_negative = 0;
    
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return i;
    }
    
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }
    
    /* Convert digits */
    while (num > 0) {
        str[i++] = (num % 10) + '0';
        num /= 10;
    }
    
    if (is_negative) {
        str[i++] = '-';
    }
    
    str[i] = '\0';
    
    /* Reverse the string */
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
    
    return i;
}

/* Improved printf implementation */
int printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    int written = 0;
    const char *p = format;
    
    while (*p) {
        if (*p == '%' && *(p + 1)) {
            p++; /* Skip '%' */
            
            switch (*p) {
                case 's': {
                    char *str = va_arg(args, char*);
                    if (str) {
                        size_t len = strlen(str);
                        write(1, str, len);
                        written += len;
                    }
                    break;
                }
                case 'd': {
                    int num = va_arg(args, int);
                    char buffer[32];
                    int len = int_to_string(num, buffer);
                    write(1, buffer, len);
                    written += len;
                    break;
                }
                case 'c': {
                    char c = (char)va_arg(args, int);
                    write(1, &c, 1);
                    written += 1;
                    break;
                }
                case '%': {
                    write(1, "%", 1);
                    written += 1;
                    break;
                }
                default: {
                    /* Unknown format specifier, just print it */
                    write(1, "%", 1);
                    write(1, p, 1);
                    written += 2;
                    break;
                }
            }
        } else {
            write(1, p, 1);
            written += 1;
        }
        p++;
    }
    
    va_end(args);
    return written;
}

/* Basic puts implementation */
int puts(const char *s) {
    size_t len = strlen(s);
    write(1, s, len);
    write(1, "\n", 1);
    return len + 1;
}
