/* SPDX-License-Identifier: BSD-3-Clause */
#ifndef _SYS__TYPES_H_
#define _SYS__TYPES_H_

#include <stddef.h>
#include <stdint.h>

/* Basic types for FreeBSD libc compatibility */
typedef signed long    __ssize_t;
typedef unsigned long  __size_t;
typedef long           __off_t;
typedef int            __pid_t;
typedef unsigned int   __uid_t;
typedef unsigned int   __gid_t;
typedef unsigned int   __mode_t;
typedef unsigned int   __nlink_t;
typedef unsigned int   __dev_t;
typedef unsigned long  __ino_t;
typedef long           __time_t;
typedef long           __clock_t;
typedef int            __key_t;
typedef long           __intptr_t;
typedef unsigned long  __uintptr_t;

#endif /* _SYS__TYPES_H_ */ 