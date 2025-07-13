#include <uk/syscall.h>
#include <uk/plat/syscall.h>
#include <errno.h>
#include <uk/config.h>
#if CONFIG_LIBSYSCALL_SHIM
#include <stdarg.h>

int uk_sys_write(int fd, const void *buf, size_t count)
{
    return uk_syscall_r_write(fd, buf, count);
}

int uk_sys_read(int fd, void *buf, size_t count)
{
    return uk_syscall_r_read(fd, buf, count);
}

int uk_sys_open(const char *pathname, int flags, mode_t mode)
{
    return uk_syscall_r_open(pathname, flags, mode);
}

int uk_sys_close(int fd)
{
    return uk_syscall_r_close(fd);
}

int uk_sys_exit(int status)
{
    uk_syscall_r_exit(status);
    return 0; /* Should never reach here */
}

/* Additional syscalls as needed */
int uk_sys_fork(void)
{
    /* Unikraft doesn't support fork, return error */
    errno = ENOSYS;
    return -1;
}

int uk_sys_getpid(void)
{
    /* Return a dummy PID for now */
    return 1;
} 


long syscall(long num, ...)
{
	va_list va;
	long arg[6];

	va_start(va, num);
	arg[0] = va_arg(va, long);
	arg[1] = va_arg(va, long);
	arg[2] = va_arg(va, long);
	arg[3] = va_arg(va, long);
	arg[4] = va_arg(va, long);
	arg[5] = va_arg(va, long);
	va_end(va);

	return uk_syscall(num,
			  arg[0],
			  arg[1],
			  arg[2],
			  arg[3],
			  arg[4],
			  arg[5]);
}

#else
#include <errno.h>
#include <uk/print.h>
#include <uk/essentials.h>

long syscall(long num __maybe_unused, ...)
{
	uk_pr_err("No such system call %lu\n", num);
	return -ENOSYS;
}
#endif /* CONFIG_LIBSYSCALL_SHIM */
