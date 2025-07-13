#ifndef _FREEBSD_MOUNT_STRUCTS_H_
#define _FREEBSD_MOUNT_STRUCTS_H_

/* Only include structures and types from FreeBSD mount.h, not function declarations */

#include <sys/types.h>
#include <sys/stat.h>

/* Essential mount structures without function declarations */
#define MFSNAMELEN      16      /* length of type name including null */
#define MNAMELEN        1024    /* size of on/from name bufs */

/* Basic integer types for compatibility */
#ifndef _UINT32_T_DECLARED
#define _UINT32_T_DECLARED
typedef unsigned int uint32_t;
#endif

#ifndef _UINT64_T_DECLARED
#define _UINT64_T_DECLARED
typedef unsigned long long uint64_t;
#endif

#ifndef _INT64_T_DECLARED
#define _INT64_T_DECLARED
typedef long long int64_t;
#endif

#ifndef _INT32_T_DECLARED
#define _INT32_T_DECLARED
typedef int int32_t;
#endif

/* fsid_t type definition */
#ifndef _FSID_T_DECLARED
#define _FSID_T_DECLARED
typedef struct fsid {
    int32_t __val[2];  /* Use __val to match Unikraft VFS expectations */
} fsid_t;
#endif

/* Filesystem statistics structure */
struct statfs {
    uint32_t f_version;         /* structure version number */
    uint32_t f_type;            /* type of filesystem */
    uint64_t f_flags;           /* copy of mount exported flags */
    uint64_t f_bsize;           /* filesystem fragment size */
    uint64_t f_iosize;          /* optimal transfer block size */
    uint64_t f_blocks;          /* total data blocks in filesystem */
    uint64_t f_bfree;           /* free blocks in filesystem */
    int64_t  f_bavail;          /* free blocks avail to non-superuser */
    uint64_t f_files;           /* total file nodes in filesystem */
    int64_t  f_ffree;           /* free nodes avail to non-superuser */
    uint64_t f_syncwrites;      /* count of sync writes since mount */
    uint64_t f_asyncwrites;     /* count of async writes since mount */
    uint64_t f_syncreads;       /* count of sync reads since mount */
    uint64_t f_asyncreads;      /* count of async reads since mount */
    uint64_t f_spare[10];       /* unused spare */
    uint32_t f_namemax;         /* maximum filename length */
    uint32_t f_namelen;         /* alias for f_namemax for compatibility */
    uid_t    f_owner;           /* user that mounted the filesystem */
    fsid_t   f_fsid;            /* filesystem id */
    char     f_charspare[80];   /* spare string space */
    char     f_fstypename[MFSNAMELEN]; /* filesystem type name */
    char     f_mntfromname[MNAMELEN];  /* mounted filesystem */
    char     f_mntonname[MNAMELEN];    /* directory on which mounted */
};

/* Mount flags */
#define MNT_RDONLY      0x00000001  /* read only filesystem */
#define MNT_SYNCHRONOUS 0x00000002  /* filesystem written synchronously */
#define MNT_NOEXEC      0x00000004  /* can't exec from filesystem */
#define MNT_NOSUID      0x00000008  /* don't honor setuid bits on fs */
#define MNT_UNION       0x00000020  /* union with underlying filesystem */

#endif /* _FREEBSD_MOUNT_STRUCTS_H_ */
