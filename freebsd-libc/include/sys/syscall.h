#ifndef _SYS_SYSCALL_H_
#define _SYS_SYSCALL_H_

/* System call definitions for FreeBSD libc */

#include <sys/types.h>

/* Basic syscall numbers */
#define SYS_write    4
#define SYS_read     3
#define SYS_open     5
#define SYS_close    6
#define SYS_exit     1
#define SYS_fork     2
#define SYS_getpid   20

/* Generic syscall function */
long syscall(long number, ...);

#endif /* _SYS_SYSCALL_H_ */ 