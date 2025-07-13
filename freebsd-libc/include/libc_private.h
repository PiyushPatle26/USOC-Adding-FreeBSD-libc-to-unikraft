#ifndef _LIBC_PRIVATE_H_
#define _LIBC_PRIVATE_H_

/* Internal FreeBSD libc glue for Unikraft */

#include <uk/plat/console.h>
#include <uk/plat/time.h>
#include <uk/plat/memory.h>

/* Platform-specific functions */
extern void uk_plat_init(void);
extern int uk_plat_console_write(const char *buf, size_t len);
extern time_t uk_plat_time(void);
extern void *uk_plat_malloc(size_t size);
extern void uk_plat_free(void *ptr);

/* Syscall mapping functions */
extern int uk_sys_write(int fd, const void *buf, size_t count);
extern int uk_sys_read(int fd, void *buf, size_t count);
extern int uk_sys_open(const char *pathname, int flags, mode_t mode);
extern int uk_sys_close(int fd);
extern int uk_sys_exit(int status);

/* Startup functions */
extern void __libc_init(void);
extern void _start(void);

#endif /* _LIBC_PRIVATE_H_ */ 