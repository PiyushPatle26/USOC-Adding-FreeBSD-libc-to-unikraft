#!/bin/bash

# Create a minimal FreeBSD libc implementation that works on Linux
# This extracts and compiles only the essential, self-contained functions

set -e

LIBC_DIR="$(pwd)"
BUILD_DIR="build"

mkdir -p "$BUILD_DIR"

echo "Creating minimal FreeBSD libc implementation..."

# Create a minimal xlocale.h header to satisfy dependencies
cat > "$BUILD_DIR/xlocale.h" << 'EOF'
/* Minimal xlocale.h for FreeBSD libc compatibility */
#ifndef _XLOCALE_H_
#define _XLOCALE_H_

typedef struct _locale *locale_t;

#endif /* _XLOCALE_H_ */
EOF

# Create basic FreeBSD compatibility headers
cat > "$BUILD_DIR/freebsd_compat.h" << 'EOF'
/* FreeBSD compatibility definitions */
#ifndef _FREEBSD_COMPAT_H_
#define _FREEBSD_COMPAT_H_

#include <sys/types.h>
#include <stdint.h>
#include <stddef.h>

/* Basic type definitions */
#ifndef __BEGIN_DECLS
#ifdef __cplusplus
#define __BEGIN_DECLS extern "C" {
#define __END_DECLS }
#else
#define __BEGIN_DECLS
#define __END_DECLS
#endif
#endif

#ifndef __FBSDID
#define __FBSDID(s)
#endif

/* System call numbers for x86_64 */
#define SYS_write 1
#define SYS_exit 60

#endif /* _FREEBSD_COMPAT_H_ */
EOF

# Create a minimal implementation with system calls
cat > "$BUILD_DIR/minimal_libc.c" << 'EOF'
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

/* Simple printf implementation (very basic) */
int printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    /* For now, just handle simple string printing */
    if (format[0] == '%' && format[1] == 's' && format[2] == '\n' && format[3] == '\0') {
        char *str = va_arg(args, char*);
        write(1, str, strlen(str));
        write(1, "\n", 1);
        va_end(args);
        return strlen(str) + 1;
    }
    
    /* Default: just print the format string */
    size_t len = strlen(format);
    write(1, format, len);
    va_end(args);
    return len;
}

/* Basic puts implementation */
int puts(const char *s) {
    size_t len = strlen(s);
    write(1, s, len);
    write(1, "\n", 1);
    return len + 1;
}
EOF

# Try to find and use some actual FreeBSD source files that don't have complex dependencies
echo "Looking for self-contained FreeBSD libc functions..."

# Check if we have some basic string functions
SIMPLE_FUNCTIONS=(
    "string/strlen.c"
    "string/strcpy.c"
    "string/strcmp.c"
    "string/memcpy.c"
    "string/memset.c"
    "string/memcmp.c"
)

CFLAGS="-O2 -fno-builtin -ffreestanding -I${BUILD_DIR} -I${LIBC_DIR}/include"

# Compile our minimal implementation
echo "Compiling minimal implementation..."
gcc -c $CFLAGS "$BUILD_DIR/minimal_libc.c" -o "$BUILD_DIR/minimal_libc.o"

OBJECTS=("$BUILD_DIR/minimal_libc.o")

# Try to compile simple string functions if they exist and are self-contained
for func in "${SIMPLE_FUNCTIONS[@]}"; do
    if [ -f "$func" ]; then
        echo "Trying to compile $func..."
        obj_file="$BUILD_DIR/$(basename "$func" .c).o"
        if gcc -c $CFLAGS "$func" -o "$obj_file" 2>/dev/null; then
            echo "Successfully compiled $func"
            OBJECTS+=("$obj_file")
        else
            echo "Failed to compile $func (has dependencies)"
        fi
    fi
done

# Create the library
echo "Creating static library..."
ar rcs "$BUILD_DIR/libfreebsd_minimal.a" "${OBJECTS[@]}"

echo ""
echo "Minimal FreeBSD libc created successfully!"
echo "Library: $BUILD_DIR/libfreebsd_minimal.a"
echo ""
echo "Test with your program:"
echo "gcc -ffreestanding -nostdlib -I./include -I./amd64 test.c -L./build -lfreebsd_minimal -o test"
echo ""
echo "If that works, you can run: ./test"
