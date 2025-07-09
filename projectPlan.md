# Project Plan
##  Timeline & Tasks
###  July 9
####  Pre-requisites

1. Understand what a libc is (C standard library implementation).
2. Explore how `musl` is integrated with Unikraft (structure, files, KConfig).
3. Check implementation of other libcs like `newlib`.
4. Study how printing (`printf`) and I/O works in FreeBSD libc.
5. Understand patching, especially how to adapt upstream codebases to Unikraft's kernel-less environment.
n

## Mentor's Strategy - Why "Locally Run with FreeBSD libc"?

### What Your Mentor Actually Meant

> “Try to locally run application with FreeBSD libc”

* **Don't jump directly into Unikraft**
* **First**, build and run a simple application on **your local Linux system** (e.g. Fedora, Ubuntu)
* But link it against **FreeBSD's libc source**, manually compiled

### 🧠 Why This Helps You

1.  **Identifies minimum required files**

   * `write.c`, `exit.c`, `stdio.h`, etc.
   * You see exactly which parts of libc are used for even the simplest app

2.  **Helps find syscall usage**

   * You’ll learn which syscalls your app makes (`strace` shows this)

3.  **Exposes runtime dependencies**

   * You find if dynamic libraries (like glibc) are being pulled in accidentally

4.  **Reveals platform-dependent parts**

   * If something fails (e.g. wrong `crt0`, missing syscall), you'll know what to patch before porting

###  How to Try It Locally

1. Clone FreeBSD libc from source
2. Write this basic app:

```c
#include <stdio.h>
int main() {
    printf("Hello from FreeBSD libc!\n");
    return 0;
}
```

3. Build it using:

```bash
gcc -nostdlib -I/path/to/freebsd/libc/include -L/path/to/libc/.libs test.c -o test
```

4. Run it using:

```bash
./test
```

---

## `ldd` and `strace`: Analyzing Your Binary

###  Tool 1: `ldd` — Check Linked Libraries

####  What it does:

Shows which shared (dynamic) libraries your binary depends on.

####  Usage:

```bash
$ ldd ./hello
```

####  Output:

```text
linux-vdso.so.1 (0x00007ffc5f5b8000)
libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f8e4f3f0000)
```

#### Use it to:

* Verify if you're using **glibc**, **musl**, or your **own FreeBSD libc**
* Confirm whether the binary is **statically or dynamically linked**

###  Tool 2: `strace` — Trace Syscalls at Runtime

####  What it does:

Shows **every syscall** your program makes to the OS.

####  Usage:

```bash
$ strace ./hello
```

####  Output (simplified):

```text
execve("./hello", ["./hello"], ...) = 0
brk(NULL)                         = 0x55b7c25a6000
write(1, "Hello, World!\n", 14)   = 14
exit_group(0)                    = 0
```

####  Use it to:

* Identify **syscalls** your app makes (e.g., `write`, `exit`)
* Know exactly which syscall wrappers you must port in FreeBSD libc

---

##  Why Use `ldd` and `strace` Before Porting

###  Sample Flow:

You compile `c-hello` and run:

```bash
strace ./c-hello-freebsd-libc
```

And it shows:

```text
write(1, "hello\n", 6)
exit(0)
```

This means:

* You must implement `write()` and `exit()` using Unikraft syscall system
* You do **not** need `fopen()`, `malloc()`, etc. for now

Then:

```bash
ldd ./c-hello-freebsd-libc
```

Shows:

```text
statically linked
```

This means:

*  You're using your own libc (not glibc)
*  No dynamic dependencies

---

##  Summary Table: `strace` vs `ldd`

| Tool      | Use It For                             | Example Command         |
| --------- | -------------------------------------- | ----------------------- |
| `ldd`     | Check dynamic libraries used           | `ldd ./mybinary`        |
| `strace`  | See syscalls made by the binary        | `strace ./mybinary`     |
| `objdump` | See low-level symbols and section info | `objdump -t ./mybinary` |

