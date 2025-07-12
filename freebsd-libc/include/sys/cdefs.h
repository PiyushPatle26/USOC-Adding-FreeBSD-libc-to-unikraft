/* SPDX-License-Identifier: BSD-3-Clause */
#ifndef _SYS_CDEFS_H_
#define _SYS_CDEFS_H_

/* Basic macros for FreeBSD libc compatibility */
#define __BEGIN_DECLS
#define __END_DECLS

#define __restrict restrict
#define __pure2 __attribute__((__pure__))
#define __malloc_like __attribute__((__malloc__))
#define __result_use_check __attribute__((__warn_unused_result__))
#define __alloc_size(x) __attribute__((__alloc_size__(x)))
#define __alloc_size2(x,y) __attribute__((__alloc_size__(x,y)))
#define __alloc_align(x) __attribute__((__alloc_align__(x)))
#define __noexcept __attribute__((__nothrow__))
#define __nonnull(x) __attribute__((__nonnull__(x)))
#define __nullable
#define _Nonnull
#define _Nullable

#define __NULLABILITY_PRAGMA_PUSH
#define __NULLABILITY_PRAGMA_POP

#define __maybe_unused __attribute__((__unused__))
#define __unused __attribute__((__unused__))

#define _Noreturn __attribute__((__noreturn__))

/* Feature test macros */
#define __POSIX_VISIBLE 200809
#define __XSI_VISIBLE 700
#define __BSD_VISIBLE 1
#define __ISO_C_VISIBLE 2011
#define __EXT1_VISIBLE 1

/* Long long support */
#define __LONG_LONG_SUPPORTED 1

/* Null pointer */
#ifndef NULL
#define NULL ((void *)0)
#endif

#endif /* _SYS_CDEFS_H_ */ 