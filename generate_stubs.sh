#!/bin/bash

# Extract symbols
nm build/libc_minimal.a | grep ' U ' | awk '{print $2}' | sort -u > undefined_symbols.txt
nm build/libc_minimal.a | grep ' T ' | awk '{print $3}' | sort -u > defined_symbols.txt

# Find undefined symbols
comm -23 undefined_symbols.txt defined_symbols.txt > to_stub_symbols.txt

# Filter symbols we care to stub
grep -E '_pthread_|_spin|__cxa_|__isthreaded|__stdio_cancel|_once|_exit|_thread_autoinit|___pthread_cleanup|__error|__d2b|__freedtoa|malloc|reallocf|memchr|memmove|raise|sigaction|__rv_alloc|__nrv_alloc|__tens_|__multadd|__cmp|__lshift|__quorem|__Bfree|__flt_rounds|__fpclassifyd|__get_|__set_|__xlocale_|strncpy|ffs|getdtablesize|_read|_write|_close|lseek' \
  to_stub_symbols.txt > final_stubs.txt

# Create stub source with required headers
{
  echo "// Auto-generated stubs"
  echo "#include <stddef.h>"  # for size_t
  echo "#include <stdint.h>"  # for uintptr_t etc. if needed
  echo ""
} > stubs.c

# Check if __isthreaded is already defined
has_isthreaded=$(nm build/libc_minimal.a | grep ' T ' | awk '{print $3}' | grep -w __isthreaded)

while read sym; do
  case $sym in
    __isthreaded)
      if [ -z "$has_isthreaded" ]; then
        echo "int __isthreaded = 0;" >> stubs.c
      fi
      ;;
    _exit)
      echo "void _exit(int x) { while(1); }" >> stubs.c
      ;;
    malloc|calloc|realloc|reallocf)
      echo "void* $sym(size_t x) { return 0; }" >> stubs.c
      ;;
    memchr|memmove|strncpy)
      echo "void* $sym(void* a, const void* b, size_t c) { return 0; }" >> stubs.c
      ;;
    raise|getdtablesize|ffs|lseek|_read|_write|_close)
      echo "int $sym(...) { return -1; }" >> stubs.c
      ;;
    *)
      echo "void $sym() {}" >> stubs.c
      ;;
  esac
done < final_stubs.txt
