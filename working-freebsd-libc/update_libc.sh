#!/bin/bash

# Update the FreeBSD libc implementation with improved printf

set -e

LIBC_DIR="$(pwd)"
BUILD_DIR="build"

echo "Updating FreeBSD libc with improved printf..."

# Replace the minimal_libc.c with improved version
cp improved_printf.c "$BUILD_DIR/minimal_libc.c"

# Compile the improved version
CFLAGS="-O2 -fno-builtin -ffreestanding -I${BUILD_DIR} -I${LIBC_DIR}/include"
gcc -c $CFLAGS "$BUILD_DIR/minimal_libc.c" -o "$BUILD_DIR/minimal_libc.o"

# Get existing objects (the string functions we compiled successfully)
OBJECTS=("$BUILD_DIR/minimal_libc.o")

# Add the string functions that compiled successfully
for obj in "$BUILD_DIR"/*.o; do
    if [[ "$(basename "$obj")" != "minimal_libc.o" ]]; then
        OBJECTS+=("$obj")
    fi
done

# Rebuild the library
echo "Rebuilding static library..."
ar rcs "$BUILD_DIR/libfreebsd_minimal.a" "${OBJECTS[@]}"

echo ""
echo "FreeBSD libc updated with improved printf!"
echo "Test with:"
echo "gcc -ffreestanding -nostdlib -I./include -I./amd64 better_test.c -L./build -lfreebsd_minimal -o better_test"
echo "./better_test"
