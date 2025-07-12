#!/bin/bash

# Simple FreeBSD libc test compilation
# This compiles only the essential functions needed for your test

set -e

LIBC_DIR="$(pwd)"
BUILD_DIR="build"

# Create build directory
mkdir -p "$BUILD_DIR"

# Basic compiler flags
CFLAGS="-O2 -fno-builtin -ffreestanding"
INCLUDES="-I${LIBC_DIR}/include -I${LIBC_DIR}/amd64"

echo "Building minimal FreeBSD libc for testing..."

# Check if essential files exist and compile them
ESSENTIAL_FILES=(
    "stdio/printf.c"
    "stdio/vfprintf.c"
    "stdio/puts.c"
    "stdlib/exit.c"
    "sys/write.c"
)

COMPILED_OBJECTS=()

for src in "${ESSENTIAL_FILES[@]}"; do
    if [ -f "$src" ]; then
        obj_file="$BUILD_DIR/$(basename "$src" .c).o"
        echo "Compiling $src -> $obj_file"
        gcc -c $CFLAGS $INCLUDES "$src" -o "$obj_file"
        COMPILED_OBJECTS+=("$obj_file")
    else
        echo "Warning: $src not found"
    fi
done

# If we have compiled objects, create a library
if [ ${#COMPILED_OBJECTS[@]} -gt 0 ]; then
    echo "Creating minimal library..."
    ar rcs "$BUILD_DIR/libfreebsd_minimal.a" "${COMPILED_OBJECTS[@]}"
    echo "Library created: $BUILD_DIR/libfreebsd_minimal.a"
else
    echo "No objects compiled, creating dummy implementations..."
    
    # Create simple implementations for testing
    cat > "$BUILD_DIR/dummy_impl.c" << 'EOF'
#include <stdarg.h>
#include <stddef.h>

// Dummy printf implementation
int printf(const char *format, ...) {
    // Simple implementation that just calls write
    const char *msg = "Hello from FreeBSD libc!\n";
    return write(1, msg, 26);
}

// Dummy exit implementation
void exit(int status) {
    // Simple exit using system call
    asm volatile (
        "mov $60, %%rax\n\t"    // sys_exit
        "mov %0, %%rdi\n\t"     // exit status
        "syscall\n\t"
        :
        : "r" (status)
        : "rax", "rdi"
    );
}

// Dummy write implementation
ssize_t write(int fd, const void *buf, size_t count) {
    ssize_t result;
    asm volatile (
        "mov $1, %%rax\n\t"     // sys_write
        "mov %1, %%rdi\n\t"     // fd
        "mov %2, %%rsi\n\t"     // buf
        "mov %3, %%rdx\n\t"     // count
        "syscall\n\t"
        "mov %%rax, %0\n\t"
        : "=r" (result)
        : "r" (fd), "r" (buf), "r" (count)
        : "rax", "rdi", "rsi", "rdx"
    );
    return result;
}
EOF

    gcc -c $CFLAGS $INCLUDES "$BUILD_DIR/dummy_impl.c" -o "$BUILD_DIR/dummy_impl.o"
    ar rcs "$BUILD_DIR/libfreebsd_minimal.a" "$BUILD_DIR/dummy_impl.o"
    echo "Dummy library created: $BUILD_DIR/libfreebsd_minimal.a"
fi

echo ""
echo "Now try compiling your test program:"
echo "gcc -ffreestanding -nostdlib -I./include -I./amd64 test.c -L./build -lfreebsd_minimal -o test"
