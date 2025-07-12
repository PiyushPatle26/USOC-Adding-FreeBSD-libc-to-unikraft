/* SPDX-License-Identifier: BSD-3-Clause */
#ifndef _UNISTD_H_
#define _UNISTD_H_

#include <sys/cdefs.h>
#include <sys/_types.h>

__BEGIN_DECLS

/* File descriptors */
#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

/* Basic I/O functions */
ssize_t write(int fd, const void *buf, size_t count);
ssize_t read(int fd, void *buf, size_t count);

/* Process control */
_Noreturn void _exit(int status);
int close(int fd);

/* File positioning */
off_t lseek(int fd, off_t offset, int whence);

/* File status */
int ftruncate(int fd, off_t length);

__END_DECLS

#endif /* _UNISTD_H_ */
