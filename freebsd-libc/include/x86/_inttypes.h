#ifndef _MACHINE_X86_INTTYPES_H_
#define _MACHINE_X86_INTTYPES_H_

/* x86 inttypes compatibility stub for FreeBSD libc */
/* This is a minimal stub for compatibility */

/* Machine-specific format specifiers for x86_64 */
#if defined(__LP64__)
/* 64-bit specific format specifiers */
#define	PRId8		"d"
#define	PRIi8		"i"
#define	PRIo8		"o"
#define	PRIu8		"u"
#define	PRIx8		"x"
#define	PRIX8		"X"

#define	PRId16		"d"
#define	PRIi16		"i"
#define	PRIo16		"o"
#define	PRIu16		"u"
#define	PRIx16		"x"
#define	PRIX16		"X"

#define	PRId32		"d"
#define	PRIi32		"i"
#define	PRIo32		"o"
#define	PRIu32		"u"
#define	PRIx32		"x"
#define	PRIX32		"X"

#define	PRId64		"ld"
#define	PRIi64		"li"
#define	PRIo64		"lo"
#define	PRIu64		"lu"
#define	PRIx64		"lx"
#define	PRIX64		"lX"

#define	PRIdMAX		"ld"
#define	PRIiMAX		"li"
#define	PRIoMAX		"lo"
#define	PRIuMAX		"lu"
#define	PRIxMAX		"lx"
#define	PRIXMAX		"lX"

#define	PRIdPTR		"ld"
#define	PRIiPTR		"li"
#define	PRIoPTR		"lo"
#define	PRIuPTR		"lu"
#define	PRIxPTR		"lx"
#define	PRIXPTR		"lX"

#define	SCNd8		"hhd"
#define	SCNi8		"hhi"
#define	SCNo8		"hho"
#define	SCNu8		"hhu"
#define	SCNx8		"hhx"

#define	SCNd16		"hd"
#define	SCNi16		"hi"
#define	SCNo16		"ho"
#define	SCNu16		"hu"
#define	SCNx16		"hx"

#define	SCNd32		"d"
#define	SCNi32		"i"
#define	SCNo32		"o"
#define	SCNu32		"u"
#define	SCNx32		"x"

#define	SCNd64		"ld"
#define	SCNi64		"li"
#define	SCNo64		"lo"
#define	SCNu64		"lu"
#define	SCNx64		"lx"

#define	SCNdMAX		"ld"
#define	SCNiMAX		"li"
#define	SCNoMAX		"lo"
#define	SCNuMAX		"lu"
#define	SCNxMAX		"lx"

#define	SCNdPTR		"ld"
#define	SCNiPTR		"li"
#define	SCNoPTR		"lo"
#define	SCNuPTR		"lu"
#define	SCNxPTR		"lx"
#else
/* 32-bit mode */
#define	PRId8		"d"
#define	PRIi8		"i"
#define	PRIo8		"o"
#define	PRIu8		"u"
#define	PRIx8		"x"
#define	PRIX8		"X"

#define	PRId16		"d"
#define	PRIi16		"i"
#define	PRIo16		"o"
#define	PRIu16		"u"
#define	PRIx16		"x"
#define	PRIX16		"X"

#define	PRId32		"d"
#define	PRIi32		"i"
#define	PRIo32		"o"
#define	PRIu32		"u"
#define	PRIx32		"x"
#define	PRIX32		"X"

#define	PRId64		"lld"
#define	PRIi64		"lli"
#define	PRIo64		"llo"
#define	PRIu64		"llu"
#define	PRIx64		"llx"
#define	PRIX64		"llX"

#define	PRIdMAX		"lld"
#define	PRIiMAX		"lli"
#define	PRIoMAX		"llo"
#define	PRIuMAX		"llu"
#define	PRIxMAX		"llx"
#define	PRIXMAX		"llX"

#define	PRIdPTR		"d"
#define	PRIiPTR		"i"
#define	PRIoPTR		"o"
#define	PRIuPTR		"u"
#define	PRIxPTR		"x"
#define	PRIXPTR		"X"

#define	SCNd8		"hhd"
#define	SCNi8		"hhi"
#define	SCNo8		"hho"
#define	SCNu8		"hhu"
#define	SCNx8		"hhx"

#define	SCNd16		"hd"
#define	SCNi16		"hi"
#define	SCNo16		"ho"
#define	SCNu16		"hu"
#define	SCNx16		"hx"

#define	SCNd32		"d"
#define	SCNi32		"i"
#define	SCNo32		"o"
#define	SCNu32		"u"
#define	SCNx32		"x"

#define	SCNd64		"lld"
#define	SCNi64		"lli"
#define	SCNo64		"llo"
#define	SCNu64		"llu"
#define	SCNx64		"llx"

#define	SCNdMAX		"lld"
#define	SCNiMAX		"lli"
#define	SCNoMAX		"llo"
#define	SCNuMAX		"llu"
#define	SCNxMAX		"llx"

#define	SCNdPTR		"d"
#define	SCNiPTR		"i"
#define	SCNoPTR		"o"
#define	SCNuPTR		"u"
#define	SCNxPTR		"x"
#endif

#endif /* _MACHINE_X86_INTTYPES_H_ */
