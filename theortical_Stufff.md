# Comprehensive Documentation: Porting FreeBSD libc to Unikraft

> **Objective**: Learn the fundamental concepts behind libc implementations, syscall pathways, Unikraft's custom syscall handling, and how to port FreeBSD libc to Unikraft. This includes everything from basic theory to advanced integration, complete with flow diagrams and system-level insights.

---

##  What is libc?

**libc** (C Standard Library) is the backbone of any C application. It provides standard interfaces to:

* Memory management (`malloc`, `free`)
* String manipulation (`strcpy`, `strlen`, etc.)
* File I/O (`open`, `write`, `read`, etc.)
* Process management (`fork`, `exit`, etc.)
* System call wrappers (`syscall`, `ioctl`, etc.)

Libc connects user-space programs to the operating system through syscall wrappers.

---

##  Implementations of libc

| Libc Variant     | Description                                                                 |
| ---------------- | --------------------------------------------------------------------------- |
| **glibc**        | GNU C Library - full-featured, widely used in GNU/Linux systems             |
| **musl**         | Lightweight, designed for static linking and embedded systems               |
| **newlib**       | Lightweight libc used in RTOS and bare-metal systems, no OS dependency      |
| **FreeBSD libc** | BSD-specific implementation with tight integration to FreeBSD's syscall ABI |

Each implementation differs in:

* Size
* Portability
* Threading model
* Syscall abstraction

---

##  Linking and Syscalls: Core Concepts

###  What is Linking?

**Linking** connects your program to external code and libraries.

* **Static Linking**: Copies library code into your binary.
* **Dynamic Linking**: Uses `.so` (shared object) files at runtime.

Static linking is preferred in unikernels (like Unikraft) to ensure everything is embedded inside a single binary.

###  What is a Syscall?

A **System Call (Syscall)** is the interface by which a user program requests a service from the OS kernel.

For example:

```c
write(fd, buf, len); // libc wrapper
```

Under the hood:

```
write()  -->  syscall(SYS_write, fd, buf, len)  -->  Kernel handles
```

The syscall typically involves a **trap to kernel** (like `int 0x80` or `syscall` instruction on x86\_64).

---

##  POSIX Compliance

**POSIX (Portable Operating System Interface)** defines standard APIs that Unix-like systems must expose.

POSIX compliance in libc means:

* `open()`, `read()`, `fork()`, etc. behave the same on all compliant systems
* Helps in writing portable user-space code

Most libc implementations (musl, glibc, FreeBSD libc) aim for partial or full POSIX compliance.

---

##  Syscall Pathway: Full Flow Diagram

```
Application
   ↓
Standard C Function (e.g., write)
   ↓
libc wrapper (e.g., write.c)
   ↓
Syscall Stub or Inline Assembly (e.g., write.S or syscall(SYS_write,...))
   ↓
Syscall Interface (int 0x80, syscall instruction)
   ↓
Kernel syscall handler
   ↓
VFS layer (if file syscall)
   ↓
Device driver or FS
```

---

##  How Syscalls Work in FreeBSD

FreeBSD uses a highly structured syscall system based on the following files:

### 🔸 `syscalls.master`

* Master table of syscall numbers, names, arguments

### 🔸 `SYSCALLS.def`

* Specifies which libc stubs/wrappers to generate for each syscall

### 🔸 `write.S`, `exit.S`, etc.

* Inline assembly syscall stubs:

```asm
SYSCALL(write) // expands to mov $SYS_write, %eax; int 0x80
```

### 🔸 `syscall.S`

* Contains the macro definitions used by above `.S` files

###  What Are Stubs and Wrappers?

| Term    | Meaning                                                    |
| ------- | ---------------------------------------------------------- |
| Stub    | Thin layer of code that triggers the syscall (in asm or C) |
| Wrapper | C function that handles user API and invokes stub          |

---

##  Why This Doesn't Work in Unikraft

Unikraft is a unikernel — no user/kernel boundary, no `int 0x80`, no syscall instructions.
Instead:

* Syscalls are handled via C function dispatching
* No traps or privilege switches

###  Unikraft uses `uk_syscall()`

```c
long uk_syscall(long n, long a0, long a1, ...);
```

It dispatches syscall numbers to appropriate functions like `sys_write()`.

###  Weak Definitions

If no implementation exists:

```c
__weak long sys_write(...) { return -ENOSYS; }
```

You override this via your own libc implementation.

---

##  How musl is Integrated in Unikraft

###  Directory: `lib/musl`

```
├── Makefile.uk
├── Config.uk
├── patches/ (adapt musl to unikraft)
├── src/
├── include/
```

###  Changes Applied:

* Replace `syscall(SYS_...)` with `uk_syscall()`
* Use `uk_syscall()` for I/O, process calls, etc.
* Patch musl source to remove Linux-specific parts

###  Example:

```diff
- return syscall(SYS_write, fd, buf, len);
+ return uk_syscall(SYS_write, fd, buf, len);
```

---

## 🛠️ How to Port FreeBSD libc to Unikraft (Step-by-Step)

###  Folder Structure

```
lib/freebsd-libc/
├── Makefile.uk
├── Config.uk
├── src/          # minimal syscall wrappers
├── include/      # headers from FreeBSD
├── patches/
```

###  Import Needed Components

* `write.c`, `exit.c`, `read.c`, etc. (from `lib/libc/sys/`)
* `unistd.h`, `sys/types.h`, `errno.h`, etc.

###  Remove Assembly

* FreeBSD's `.S` files like `write.S` use `SYSCALL()` macro → remove
* Replace with:

```c
ssize_t write(int fd, const void *buf, size_t len) {
    return uk_syscall(SYS_write, fd, buf, len);
}
```

###  Hardcode syscall numbers

Create `include/freebsd-syscall-nrs.h`:

```c
#define SYS_write 4
#define SYS_exit 1
#define SYS_read 3
```

###  Provide Makefile.uk

```make
LIBFREELIBC_SRCDIR := $(LIBFREELIBC_BASE)/src
$(eval $(call addlib_sourcetree,$(LIBFREELIBC_SRCDIR)))
```

###  Provide Config.uk

```kconfig
config LIBFREELIBC
    bool "FreeBSD libc (minimal)"
    default n
```

###  Add Custom Syscall (for testing)

In `include/uk/syscall_nrs.h`:

```c
#define SYS_shreya_speaks 9001
```

In `lib/uk/syscall/syscall.c`:

```c
long sys_shreya_speaks(void) {
    printf("Custom syscall hit!\n");
    return 0;
}
```

In the dispatcher:

```c
case SYS_shreya_speaks:
    return sys_shreya_speaks();
```

---

##  Test with a Minimal App

```c
#include <stdio.h>
int main() {
    printf("Hello from FreeBSD libc!\n");
    return 0;
}
```

Confirm:

* `printf()` uses `write()`
* `write()` calls `uk_syscall(SYS_write, ...)`
* `sys_write()` prints to stdout

---

##  Summary Table

| Component           | FreeBSD libc                        | What You Must Do in Unikraft          |
| ------------------- | ----------------------------------- | ------------------------------------- |
| `write.S`, `exit.S` | Assembly syscall stubs              | Delete and rewrite as C wrappers      |
| `SYSCALLS.def`      | Tells what syscall wrappers to make | Manually reimplement needed ones      |
| `syscalls.master`   | Source of syscall #s                | Extract and hardcode `SYS_*` values   |
| `syscall.S`         | Defines macros for syscall asm      | Not needed                            |
| Syscall interface   | `int 0x80`, `syscall` instr         | Use `uk_syscall()`                    |
| Kernel-trap based   | Yes                                 | No (Unikraft is single address space) |

---

##  Next Steps

* [ ] Create `lib/freebsd-libc/` skeleton
* [ ] Add `write()`, `exit()` wrappers using `uk_syscall`
* [ ] Provide headers (`unistd.h`, etc.)
* [ ] Add simple application: `c-hello`
* [ ] Add and test custom syscall (`shreya_speaks`)
