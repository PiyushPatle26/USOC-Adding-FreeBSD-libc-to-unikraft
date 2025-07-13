#ifndef _LIBSYS_H_
#define _LIBSYS_H_

/* Syscall interface for FreeBSD libc */

#include <sys/types.h>

/* Basic syscall numbers */
#define SYS_write    4
#define SYS_read     3
#define SYS_open     5
#define SYS_close    6
#define SYS_exit     1
#define SYS_fork     2
#define SYS_getpid   20

/* Syscall function declarations */
int sys_write(int fd, const void *buf, size_t count);
int sys_read(int fd, void *buf, size_t count);
int sys_open(const char *pathname, int flags, mode_t mode);
int sys_close(int fd);
void sys_exit(int status);
int sys_fork(void);
int sys_getpid(void);

/* Generic syscall function */
long syscall(long number, ...);

#endif /* _LIBSYS_H_ */ 