#!/bin/bash

# FreeBSD libc compilation script
# This script compiles essential FreeBSD libc source files

set -e

LIBC_DIR="$(pwd)"
BUILD_DIR="build"
ARCH="amd64"  # x86_64 architecture

# Create build directory
mkdir -p "$BUILD_DIR"

# Compiler flags
CFLAGS="-O2 -pipe -fno-strict-aliasing -Wno-uninitialized -Wno-pointer-sign -Wno-empty-body -Wno-string-plus-int -Wno-unused-const-variable -Wno-tautological-compare -Wno-unused-value -Wno-parentheses-equality -Wno-unused-function -Wno-enum-conversion -Wno-unused-local-typedef -Wno-address-of-packed-member -Wno-switch -Wno-switch-enum -Wno-knr-promoted-parameter -Wno-parentheses -Qunused-arguments"

# Include paths
INCLUDES="-I${LIBC_DIR}/include -I${LIBC_DIR}/${ARCH} -I${LIBC_DIR}/stdio -I${LIBC_DIR}/stdlib -I${LIBC_DIR}/string -I${LIBC_DIR}/gen -I${LIBC_DIR}/sys"

# Essential source files to compile
ESSENTIAL_SOURCES=(
    # Basic I/O
    "stdio/printf.c"
    "stdio/vfprintf.c"
    "stdio/fflush.c"
    "stdio/fwrite.c"
    "stdio/putchar.c"
    "stdio/puts.c"
    "stdio/fputc.c"
    "stdio/fputs.c"
    "stdio/vprintf.c"
    "stdio/snprintf.c"
    "stdio/vsnprintf.c"
    "stdio/vasprintf.c"
    "stdio/asprintf.c"
    "stdio/fopen.c"
    "stdio/fclose.c"
    "stdio/fread.c"
    "stdio/ferror.c"
    "stdio/feof.c"
    "stdio/clearerr.c"
    "stdio/fileno.c"
    "stdio/setvbuf.c"
    "stdio/setbuf.c"
    "stdio/ungetc.c"
    "stdio/fgetc.c"
    "stdio/getc.c"
    "stdio/getchar.c"
    "stdio/fgets.c"
    "stdio/gets.c"
    "stdio/scanf.c"
    "stdio/fscanf.c"
    "stdio/sscanf.c"
    "stdio/vscanf.c"
    "stdio/vfscanf.c"
    "stdio/vsscanf.c"
    
    # Memory management
    "stdlib/malloc.c"
    "stdlib/calloc.c"
    "stdlib/realloc.c"
    "stdlib/free.c"
    "stdlib/exit.c"
    "stdlib/atexit.c"
    "stdlib/abort.c"
    "stdlib/getenv.c"
    "stdlib/system.c"
    "stdlib/atoi.c"
    "stdlib/atol.c"
    "stdlib/atoll.c"
    "stdlib/strtol.c"
    "stdlib/strtoll.c"
    "stdlib/strtoul.c"
    "stdlib/strtoull.c"
    "stdlib/strtod.c"
    "stdlib/strtof.c"
    "stdlib/strtold.c"
    "stdlib/qsort.c"
    "stdlib/bsearch.c"
    "stdlib/abs.c"
    "stdlib/labs.c"
    "stdlib/llabs.c"
    "stdlib/div.c"
    "stdlib/ldiv.c"
    "stdlib/lldiv.c"
    "stdlib/rand.c"
    "stdlib/srand.c"
    
    # String functions
    "string/memcpy.c"
    "string/memmove.c"
    "string/memset.c"
    "string/memcmp.c"
    "string/memchr.c"
    "string/strcpy.c"
    "string/strncpy.c"
    "string/strcat.c"
    "string/strncat.c"
    "string/strcmp.c"
    "string/strncmp.c"
    "string/strchr.c"
    "string/strrchr.c"
    "string/strlen.c"
    "string/strdup.c"
    "string/strndup.c"
    "string/strstr.c"
    "string/strtok.c"
    "string/strerror.c"
    "string/strsep.c"
    "string/strcasecmp.c"
    "string/strncasecmp.c"
    "string/strspn.c"
    "string/strcspn.c"
    "string/strpbrk.c"
    
    # System calls and general functions
    "sys/write.c"
    "sys/read.c"
    "sys/close.c"
    "sys/open.c"
    "sys/stat.c"
    "sys/lstat.c"
    "sys/fork.c"
    "sys/wait.c"
    "sys/waitpid.c"
    
    # General utilities
    "gen/basename.c"
    "gen/dirname.c"
    "gen/getcwd.c"
    "gen/getprogname.c"
    "gen/setprogname.c"
    "gen/time.c"
    "gen/sleep.c"
    "gen/usleep.c"
    "gen/alarm.c"
    "gen/signal.c"
    "gen/raise.c"
    "gen/pause.c"
    "gen/getpid.c"
    "gen/getppid.c"
    "gen/getuid.c"
    "gen/geteuid.c"
    "gen/getgid.c"
    "gen/getegid.c"
    
    # Architecture-specific startup code
    "${ARCH}/crt1.c"
    "${ARCH}/crti.S"
    "${ARCH}/crtn.S"
)

echo "Compiling FreeBSD libc source files..."

# Compile each source file
for src in "${ESSENTIAL_SOURCES[@]}"; do
    if [ -f "$src" ]; then
        obj_file="$BUILD_DIR/$(basename "$src" .c).o"
        echo "Compiling $src -> $obj_file"
        
        if [[ "$src" == *.S ]]; then
            # Assembly file
            gcc -c $INCLUDES "$src" -o "$obj_file"
        else
            # C file
            gcc -c $CFLAGS $INCLUDES "$src" -o "$obj_file"
        fi
    else
        echo "Warning: Source file $src not found, skipping..."
    fi
done

echo "Creating static library..."
ar rcs "$BUILD_DIR/libfreebsd.a" "$BUILD_DIR"/*.o

echo "FreeBSD libc compilation complete!"
echo "Static library created: $BUILD_DIR/libfreebsd.a"
echo ""
echo "To use with your test program:"
echo "gcc -ffreestanding -nostdlib -I./include -I./amd64 test.c -L./build -lfreebsd -o test"
