# Project Plan
##  Timeline & Tasks
###  July 9
####  Pre-requisites

1. Understand what a libc is (C standard library implementation).
2. Explore how `musl` is integrated with Unikraft (structure, files, KConfig).
3. Check implementation of other libcs like `newlib`.
4. Study how printing (`printf`) and I/O works in FreeBSD libc.
5. Understand patching, especially how to adapt upstream codebases to Unikraft's kernel-less environment.

#### 🔨 Implementation Plan

* Create a new external library `lib-freebsd`

* Mirror structure of `musl` and `newlib`:

  ```
  lib/
   └── libfreebsd/
       ├── include/
       ├── src/
       ├── Makefile.uk
       ├── Config.uk
       └── patches/
  ```

* Download FreeBSD libc sources

* Identify minimal required source files:

  * `stdlib` (e.g., malloc/free)
  * `string` (e.g., memcpy/strcpy)
  * `unistd` (e.g., syscall wrappers)
  * Basic syscall interface

* Adapt libc to Unikraft's build and syscall system
* Add KConfig entries to enable/disable FreeBSD libc
* Plan initial test with `c-hello` and maybe one or two more `catalog-core` apps

###  July 10
####  Continue Porting
* Finish porting selected libc components
* Flag and document all compatibility issues
* Add stubs or syscall mappings for unsupported system calls
* Begin patching with `#ifdef __UNIKRAFT__` guards where needed

####  On Hackathon Day
* Finalize build and integration
* Run test suite:

  * `c-hello`
  * One or two apps from `catalog-core`
* Benchmark runtime correctness

---

##  Research Summary
### 🔹 libc Fundamentals

* libc provides the standard functions for memory, I/O, and system interaction.
* FreeBSD libc is POSIX-compliant and used as default in FreeBSD systems.
* musl and newlib are examples of other libc variants already integrated with Unikraft.

### 🔹 musl in Unikraft

* Highly modular and tightly coupled with Unikraft syscalls.
* Uses `Makefile.uk`, `Config.uk`, and patches for integration.
* Contains clean header/implementation separation.

### 🔹 Compatibility Challenges

* Unikraft does not implement all Linux/FreeBSD syscalls.
* Need to map `read()`, `write()`, `open()`, etc., to Unikraft equivalents (`uk_sys_*`).
* `stdio` and I/O functions are complex — postpone detailed implementation.
* Use Unikraft's internal logging (`uk_pr_info`, etc.) for I/O debugging.

### 🔹 Testing Strategy

* Start with `c-hello`
* Later, run applications from `apps/posix-tests`, `catalog-core/redis`, etc.
* Evaluate correctness and binary size

---

##  Technical Potential Implementation
###  Stub syscall layer

```c
int freebsd_read(int fd, void *buf, size_t count) {
    return uk_sys_read(fd, buf, count);  // or similar UK syscall
}
```

###  Example KConfig (`Config.uk`)

```kconfig
config LIBFREEBSD
    bool "FreeBSD libc support"
    default n
    help
      Enable the FreeBSD libc port as an external libc alternative.
```

###  Example Makefile.uk

```make
$(eval $(call addlib_s,$(CONFIG_LIBFREEBSD)))
```

