/*-
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)types.h	8.3 (Berkeley) 1/5/94
 * $FreeBSD$
 */

#ifndef _SYS_TYPES_H_
#define	_SYS_TYPES_H_

#include <sys/cdefs.h>
#include <sys/_types.h>

/* Machine type dependent parameters. */
#include <machine/endian.h>
#include <machine/types.h>

typedef	__uint32_t	__dev_t;	/* device number */
typedef	__uint64_t	__ino_t;	/* file serial number */
typedef	__uint32_t	__mode_t;	/* file type and permissions */
typedef	__uint32_t	__nlink_t;	/* link count */
typedef	__uint64_t	__off_t;	/* file offset */
typedef	__int64_t	__loff_t;	/* file offset */
typedef	__uint32_t	__uid_t;	/* user ID */
typedef	__uint32_t	__gid_t;	/* group ID */
typedef	__uint64_t	__blkcnt_t;	/* blocks allocated for file */
typedef	__uint64_t	__blksize_t;	/* optimal blocksize for I/O */
typedef	__uint64_t	__fsblkcnt_t;	/* file system block count */
typedef	__uint64_t	__fsfilcnt_t;	/* file system file count */
typedef	__uint64_t	__id_t;		/* can hold a uid_t or pid_t */
typedef	__uint32_t	__clock_t;	/* ticks in CLOCKS_PER_SEC */
typedef	__uint32_t	__time_t;	/* seconds since 1 Jan 1970 00:00:00 UTC */
typedef	__uint32_t	__clockid_t;	/* clock_t type */
typedef	__uint32_t	__timer_t;	/* timer_t type */
typedef	__uint32_t	__sa_family_t;	/* sockaddr address family type */
typedef	__uint32_t	__socklen_t;	/* length type for network syscalls */
typedef	__uint32_t	__rlim_t;	/* resource limit */
typedef	__uint8_t	__uint8_t;
typedef	__uint16_t	__uint16_t;
typedef	__uint32_t	__uint32_t;
typedef	__uint64_t	__uint64_t;

#ifndef _SIZE_T_DECLARED
typedef	__size_t	size_t;
#define	_SIZE_T_DECLARED
#endif

#ifndef _SSIZE_T_DECLARED
typedef	__ssize_t	ssize_t;
#define	_SSIZE_T_DECLARED
#endif

#ifndef _OFF_T_DECLARED
typedef	__off_t		off_t;
#define	_OFF_T_DECLARED
#endif

#ifndef _MODE_T_DECLARED
typedef	__mode_t	mode_t;
#define	_MODE_T_DECLARED
#endif

#ifndef _UID_T_DECLARED
typedef	__uid_t		uid_t;
#define	_UID_T_DECLARED
#endif

#ifndef _GID_T_DECLARED
typedef	__gid_t		gid_t;
#define	_GID_T_DECLARED
#endif

#ifndef _PID_T_DECLARED
typedef	__pid_t		pid_t;
#define	_PID_T_DECLARED
#endif

#ifndef _CLOCK_T_DECLARED
typedef	__clock_t	clock_t;
#define	_CLOCK_T_DECLARED
#endif

#ifndef _TIME_T_DECLARED
typedef	__time_t	time_t;
#define	_TIME_T_DECLARED
#endif

#ifndef _CLOCKID_T_DECLARED
typedef	__clockid_t	clockid_t;
#define	_CLOCKID_T_DECLARED
#endif

#ifndef _TIMER_T_DECLARED
typedef	__timer_t	timer_t;
#define	_TIMER_T_DECLARED
#endif

#ifndef _SA_FAMILY_T_DECLARED
typedef	__sa_family_t	sa_family_t;
#define	_SA_FAMILY_T_DECLARED
#endif

#ifndef _SOCKLEN_T_DECLARED
typedef	__socklen_t	socklen_t;
#define	_SOCKLEN_T_DECLARED
#endif

#ifndef _RLIM_T_DECLARED
typedef	__rlim_t	rlim_t;
#define	_RLIM_T_DECLARED
#endif

#ifndef _BLKCNT_T_DECLARED
typedef	__blkcnt_t	blkcnt_t;
#define	_BLKCNT_T_DECLARED
#endif

#ifndef _BLKSIZE_T_DECLARED
typedef	__blksize_t	blksize_t;
#define	_BLKSIZE_T_DECLARED
#endif

#ifndef _FSBLKCNT_T_DECLARED
typedef	__fsblkcnt_t	fsblkcnt_t;
#define	_FSBLKCNT_T_DECLARED
#endif

#ifndef _FSFILCNT_T_DECLARED
typedef	__fsfilcnt_t	fsfilcnt_t;
#define	_FSFILCNT_T_DECLARED
#endif

#ifndef _ID_T_DECLARED
typedef	__id_t		id_t;
#define	_ID_T_DECLARED
#endif

#ifndef _KEY_T_DECLARED
typedef	__int32_t	key_t;
#define	_KEY_T_DECLARED
#endif

#ifndef _INTPTR_T_DECLARED
typedef	__intptr_t	intptr_t;
#define	_INTPTR_T_DECLARED
#endif

#ifndef _UINTPTR_T_DECLARED
typedef	__uintptr_t	uintptr_t;
#define	_UINTPTR_T_DECLARED
#endif

#ifndef _DEV_T_DECLARED
typedef	__dev_t		dev_t;
#define	_DEV_T_DECLARED
#endif

#ifndef _INO_T_DECLARED
typedef	__ino_t		ino_t;
#define	_INO_T_DECLARED
#endif

#ifndef _NLINK_T_DECLARED
typedef	__nlink_t	nlink_t;
#define	_NLINK_T_DECLARED
#endif

/* Major, minor numbers, dev_t's. */
#define	major(x)	((int)(((u_int)(x) >> 8) & 0xff))
#define	minor(x)	((int)((x) & 0xff))
#define	makedev(x,y)	((dev_t)(((x) << 8) | (y)))

#endif /* !_SYS_TYPES_H_ */ 