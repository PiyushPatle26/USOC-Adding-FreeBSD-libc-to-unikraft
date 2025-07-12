/* FreeBSD compatibility definitions */
#ifndef _FREEBSD_COMPAT_H_
#define _FREEBSD_COMPAT_H_

#include <sys/types.h>
#include <stdint.h>
#include <stddef.h>

/* Basic type definitions */
#ifndef __BEGIN_DECLS
#ifdef __cplusplus
#define __BEGIN_DECLS extern "C" {
#define __END_DECLS }
#else
#define __BEGIN_DECLS
#define __END_DECLS
#endif
#endif

#ifndef __FBSDID
#define __FBSDID(s)
#endif

/* System call numbers for x86_64 */
#define SYS_write 1
#define SYS_exit 60

#endif /* _FREEBSD_COMPAT_H_ */
