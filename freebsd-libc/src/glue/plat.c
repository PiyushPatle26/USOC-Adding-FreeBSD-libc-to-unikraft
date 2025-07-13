#include <uk/plat/console.h>
#include <uk/plat/time.h>
#include <uk/plat/memory.h>
// #include <uk/plat/thread.h>  // Thread support not needed for basic hello world
#include <uk/plat/syscall.h>
#include <uk/plat/bootstrap.h>
#include <errno.h>
#include <sys/types.h>


/* Platform-specific glue for FreeBSD libc */

void uk_plat_init(void)
{
    /* Initialize platform-specific components */
}

/* Console output for FreeBSD libc */
int uk_plat_console_write(const char *buf, size_t len)
{
    return ukplat_coutk(buf, len);
}

/* Time functions for FreeBSD libc */
time_t uk_plat_time(void)
{
    return ukplat_monotonic_clock() / 1000000; /* Convert to seconds */
}

/* Memory allocation for FreeBSD libc */
void *uk_plat_malloc(size_t size)
{
    return uk_malloc(uk_alloc_get_default(), size);
}

void uk_plat_free(void *ptr)
{
    uk_free(uk_alloc_get_default(), ptr);
} 

int getentropy(void *buf __unused, size_t buflen __unused)
{
	/* We don't have a source for high-quality random data,
	 * at least not yet. So we return ENOSYS, as the spec suggests.
	 */
	errno = ENOSYS;
	return -1;
}

#include <uk/plat/bootstrap.h>

void abort(void)
{
	ukplat_terminate(UKPLAT_CRASH);
}

void _exit(int status)
{
	/* To do: convert status to UKPLAT codes */
	ukplat_terminate(status);
}
