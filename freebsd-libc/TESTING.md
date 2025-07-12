# Testing FreeBSD libc on Unikraft

## Overview

This document describes how to test the FreeBSD libc port for Unikraft and how to troubleshoot common issues.

## Test Application

A minimal test application has been created in `../test-freebsd-libc-hello/` that tests:

- `printf()` - Formatted output
- `write()` - Direct system calls
- `strlen()` - String operations
- Basic C standard library functionality

## Building and Running

1. **Prerequisites:**
   - Unikraft source in `../unikraft/`
   - FreeBSD libc library in `../lib-freebsd-libc/`
   - QEMU for running the application

2. **Build the test application:**
   ```bash
   cd test-freebsd-libc-hello
   ./test.sh
   ```

3. **Run the application:**
   ```bash
   qemu-system-x86_64 -cpu host -enable-kvm -m 64 -nodefaults -no-acpi -display none -serial stdio -device isa-debug-exit -kernel build/test-freebsd-libc-hello_kvm-x86_64
   ```

## Expected Output

```
Hello from FreeBSD libc on Unikraft!
String length: 28
Direct write test
Testing printf with numbers: 42, success
FreeBSD libc test completed successfully!
```

## Common Issues and Solutions

### 1. Missing Header Files

**Error:** `fatal error: 'sys/cdefs.h' file not found`

**Solution:** Ensure all required headers are present:
- `include/sys/cdefs.h`
- `include/sys/_null.h`
- `include/sys/_types.h`
- `include/sys/types.h`

### 2. Missing Type Definitions

**Error:** `unknown type name 'size_t'` or similar

**Solution:** Check that `sys/_types.h` includes all necessary typedefs:
- `__size_t`
- `__ssize_t`
- `__off_t`
- `__off64_t`
- `__va_list`

### 3. Missing Function Implementations

**Error:** `undefined reference to 'printf'` or similar

**Solution:** 
1. Check that the function is implemented in the appropriate source directory
2. Verify the source file is listed in `Makefile.uk`
3. Ensure the function is properly declared in the header file

### 4. Syscall Glue Issues

**Error:** `undefined reference to 'uk_syscall_write'` or similar

**Solution:** 
1. Check that `src/glue/syscall.c` and `src/glue/plat.c` are properly implemented
2. Verify that the syscall numbers match Unikraft's expectations
3. Ensure the glue code is included in `Makefile.uk`

### 5. Build Configuration Issues

**Error:** Build system can't find the library

**Solution:**
1. Verify `Config.uk` and `Library.uk` are properly configured
2. Check that the library path is correctly specified in the test application's Makefile
3. Ensure all required dependencies are declared

## Adding More Functionality

When adding new functions:

1. **Add the implementation** to the appropriate source directory
2. **Update the header** to declare the function
3. **Add to Makefile.uk** to include the source file
4. **Test incrementally** to catch issues early

## Debugging Tips

1. **Use verbose builds:** Add `V=1` to make commands for detailed output
2. **Check symbol dependencies:** Use `nm` to examine the built library
3. **Test minimal cases:** Start with the simplest possible function calls
4. **Compare with working implementations:** Reference `lib-newlib` for guidance

## Next Steps

After the basic test passes:

1. Add more complex functions (malloc, file I/O, etc.)
2. Test with real applications
3. Add performance benchmarks
4. Document any Unikraft-specific considerations 