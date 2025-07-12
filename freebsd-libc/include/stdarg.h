/* SPDX-License-Identifier: BSD-3-Clause */
#ifndef _STDARG_H_
#define _STDARG_H_

#include <sys/cdefs.h>
#include <sys/_types.h>

#if defined(__GNUC__)

typedef __builtin_va_list va_list;
#define va_start(ap, last) __builtin_va_start((ap), (last))
#define va_end(ap)         __builtin_va_end((ap))
#define va_arg(ap, type)   __builtin_va_arg((ap), type)
#define va_copy(dest, src) __builtin_va_copy((dest), (src))

#else
#error "Compiler does not support built-in varargs."
#endif

#endif /* _STDARG_H_ */
