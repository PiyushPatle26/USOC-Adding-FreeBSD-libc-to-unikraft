# FreeBSD libc for Unikraft

This is a port of FreeBSD's C standard library (libc) to Unikraft. It provides a complete implementation of the C standard library functions, including stdio, stdlib, string manipulation, and system calls.

## Structure

```
lib-freebsd-libc/
├── Config.uk          # Unikraft configuration
├── Library.uk         # Library metadata
├── Makefile.uk        # Build configuration
├── README.md          # This file
├── include/           # Header files
│   ├── stdio/         # Standard I/O headers
│   ├── stdlib/        # Standard library headers
│   ├── string/        # String manipulation headers
│   ├── sys/           # System headers
│   └── ...            # Other headers
└── src/               # Source files
    ├── glue/          # Unikraft glue code
    ├── stdio/         # Standard I/O implementation
    ├── stdlib/        # Standard library implementation
    ├── string/        # String manipulation implementation
    └── sys/           # System call implementation
```

## Features

- Complete C standard library implementation
- Standard I/O functions (printf, scanf, file operations)
- String manipulation functions
- Memory management functions
- System call interface
- Wide character support
- Thread-safe operations

## Usage

1. Add this library to your Unikraft application's `Makefile`:
   ```makefile
   LIBS := $(LIBS) $(UK_LIBS)/lib-freebsd-libc
   ```

2. Enable the library in your application's configuration:
   ```
   make menuconfig
   # Navigate to Library Configuration -> libfreebsd-libc
   # Enable "libfreebsd-libc - FreeBSD C standard library"
   ```

3. Build your application:
   ```bash
   make
   ```

## Configuration Options

- `LIBFREEBSDLIBC_WANT_IO_C99_FORMATS`: Enable C99 I/O formats
- `LIBFREEBSDLIBC_LINUX_ERRNO_EXTENSIONS`: Use Linux errno extensions
- `LIBFREEBSDLIBC_CRYPT`: Enable crypt() and crypt_r() functions

## Dependencies

This library depends on the following Unikraft libraries:
- `LIBUKALLOC`: Memory allocation
- `LIBUKTIME`: Time functions
- `LIBVFSCORE`: Virtual file system
- `LIBUKSIGNAL`: Signal handling
- `LIBUKSCHED_TCB_INIT`: Thread control block initialization
- `LIBPOSIX_PROCESS`: POSIX process functions
- `LIBPOSIX_USER`: POSIX user functions

## License

This library is licensed under the BSD-3-Clause license, same as FreeBSD libc.

## Contributing

When contributing to this library:
1. Follow the existing code style
2. Add appropriate tests
3. Update documentation as needed
4. Ensure compatibility with Unikraft's build system 