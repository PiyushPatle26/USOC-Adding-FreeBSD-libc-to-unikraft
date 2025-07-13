#ifndef _FREEBSDLIBC_COMPAT_H_
#define _FREEBSDLIBC_COMPAT_H_

/* Prevent FreeBSD signal.h from being included - use minimal compatibility */
#define _SIGNAL_H_
#define _SYS_SIGNAL_H_

/* Prevent FreeBSD sys/wait.h conflicts - use Unikraft's implementation */
#define _SYS_WAIT_H_

/* Signal constants */
#ifndef _NSIG
#define _NSIG 64    /* Number of signals */
#endif

/* Stack type for signal handling */
#ifndef _STACK_T_DECLARED
#define _STACK_T_DECLARED
typedef struct {
    void *ss_sp;      /* signal stack base */
    long ss_size;     /* signal stack length */
    int ss_flags;     /* signal stack flags */
} stack_t;
#endif

/* SEEK constants for lseek() */
#ifndef SEEK_SET
#define SEEK_SET        0       /* set file offset to offset */
#define SEEK_CUR        1       /* set file offset to current plus offset */
#define SEEK_END        2       /* set file offset to EOF plus offset */
#endif

/* UTIME constants for futimens() - Use FreeBSD values */
#ifndef UTIME_NOW
#define UTIME_NOW       -1
#define UTIME_OMIT      -2
#endif

/* File flags - O_NOATIME is Linux-specific, define as 0 for compatibility */
#ifndef O_NOATIME
#define O_NOATIME       0
#endif

/* Epoll constants - Linux-specific, define for compatibility */
#ifndef EPOLL_CLOEXEC
#define EPOLL_CLOEXEC   02000000
#endif

/* Poll types for Unikraft compatibility */
#ifndef __nfds_t_defined
#define __nfds_t_defined
typedef unsigned int nfds_t;
#endif

#ifndef _STRUCT_POLLFD_DECLARED
#define _STRUCT_POLLFD_DECLARED
struct pollfd {
    int fd;         /* file descriptor */
    short events;   /* events to poll for */
    short revents;  /* events that occurred */
};
#endif

/* Poll event constants - Match FreeBSD epoll values exactly */
#ifndef POLLIN
#define POLLIN          0x001
#define POLLPRI         0x002
#define POLLOUT         0x004
#define POLLRDNORM      0x040
#define POLLRDBAND      0x080
#define POLLWRNORM      0x100
#define POLLWRBAND      0x200
#define POLLERR         0x008
#define POLLHUP         0x010
#define POLLNVAL        0x020
#define POLLRDHUP       0x2000
#endif

/* Prevent FreeBSD UIO enum redefinition - use Unikraft's version */
#define _SYS__UIO_H_
#define _UIO_RW_

/* Prevent FreeBSD poll.h from being included - use Unikraft's version */
#define _SYS_POLL_H_

/* Prevent FreeBSD SSP (Stack Smashing Protection) function redefinitions */
#define _SSP_UIO_H_

/* Prevent FreeBSD rlim_t type definition - use Unikraft's version */
#define _RLIM_T_DECLARED

/* Basic signal types for compatibility */
#ifndef __siginfo_t_defined
#define __siginfo_t_defined
#define _SIGINFO_T_DECLARED  /* Prevent FreeBSD redefinition */

/* Process ID types */
#ifndef _ID_T_DECLARED
#define _ID_T_DECLARED
typedef long id_t;
#endif

/* ID type enum for waitid */
#ifndef _IDTYPE_T_DECLARED
#define _IDTYPE_T_DECLARED
typedef enum idtype {
    P_ALL = 0,      /* wait for any child */
    P_PID = 1,      /* wait for specified process */
    P_PGID = 2      /* wait for any process in specified process group */
} idtype_t;
#endif

/* Resource usage structure - forward declaration only */
#ifndef _RUSAGE_DECLARED
#define _RUSAGE_DECLARED
struct rusage;  /* Forward declaration - full definition in sys/resource.h */
#endif

typedef struct {
    int si_signo;       /* Signal number */
    int si_errno;       /* Errno value */
    int si_code;        /* Signal code */
    int si_pid;         /* Sending process ID */
    int si_uid;         /* Real user ID of sending process */
    int si_status;      /* Exit status or signal */
    void *si_addr;      /* Memory location which caused fault */
    union {
        int _pad[16];   /* Pad to maintain size */
        struct {
            int si_band;
            int si_fd;
        } _sigpoll;
    } _sifields;
} siginfo_t;

/* FreeBSD compatibility - make __siginfo an alias for siginfo_t */
struct __siginfo {
    int si_signo;       /* Signal number */
    int si_errno;       /* Errno value */
    int si_code;        /* Signal code */
    int si_pid;         /* Sending process ID */
    int si_uid;         /* Real user ID of sending process */
    int si_status;      /* Exit status or signal */
    void *si_addr;      /* Memory location which caused fault */
    union {
        int _pad[16];   /* Pad to maintain size */
        struct {
            int si_band;
            int si_fd;
        } _sigpoll;
    } _sifields;
};
#endif

/* Prevent poll SSP functions that conflict with Unikraft posix-poll */
#define _SSP_POLL_H_
#define _FORTIFY_SOURCE 0
#define __ssp_redirect_raw_impl(rtype, fun, args) /* disabled */

/* Linux-specific fcntl constants - define for compatibility */
#ifndef F_SETSIG
#define F_SETSIG        10      /* set signal sent when I/O possible */
#define F_SETLEASE      1024    /* set lease */
#define F_NOTIFY        1026    /* notify on directory changes */
#define F_SETPIPE_SZ    1031    /* set pipe page size */
#define F_OFD_SETLK     37      /* open file description locks */
#define F_OFD_SETLKW    38
#define F_OFD_GETLK     39
#define F_GETOWN_EX     16      /* get owner with extended info */
#define F_SETOWN_EX     15      /* set owner with extended info */
#define F_GET_RW_HINT   1035    /* get per-file read/write hint */
#define F_SET_RW_HINT   1036    /* set per-file read/write hint */
#define F_GET_FILE_RW_HINT 1037 /* get per-file read/write hint */
#define F_SET_FILE_RW_HINT 1038 /* set per-file read/write hint */
#endif

/* Clock constants for time functions */
#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME          0
#endif
#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC         1
#endif
#ifndef CLOCK_PROCESS_CPUTIME_ID
#define CLOCK_PROCESS_CPUTIME_ID 2
#endif
#ifndef CLOCK_THREAD_CPUTIME_ID
#define CLOCK_THREAD_CPUTIME_ID 3
#endif

/* Additional clock constants for extended compatibility */
#ifndef CLOCK_MONOTONIC_RAW
#define CLOCK_MONOTONIC_RAW 4
#endif
#ifndef CLOCK_MONOTONIC_COARSE
#define CLOCK_MONOTONIC_COARSE 5
#endif
#ifndef CLOCK_REALTIME_COARSE
#define CLOCK_REALTIME_COARSE 6
#endif
#ifndef CLOCK_BOOTTIME
#define CLOCK_BOOTTIME 7
#endif

/* Timer constants */
#ifndef TIMER_ABSTIME
#define TIMER_ABSTIME 1
#endif

/* Prevent FreeBSD time headers from being included - use Unikraft's implementation */
#define _SYS_TIME_H_
#define _TIME_H_
#define _SYS__TIMESPEC_H_
#define _SYS__TIMEVAL_H_

/* Prevent FreeBSD timespec header */
#ifndef _SYS_TIMESPEC_H_
#define _SYS_TIMESPEC_H_
#endif

/* Memory mapping constants */
#ifndef MAP_NORESERVE
#define MAP_NORESERVE   0x0040  /* don't reserve swap space */
#endif

/* Prevent FreeBSD unistd.h from being included - use Unikraft's implementation */
#define _UNISTD_H_

/* Prevent FreeBSD setgroups declaration that conflicts with Unikraft */
#define setgroups setgroups_freebsd_disabled

/* Prevent FreeBSD mount.h entirely to avoid function conflicts */
#define _SYS_MOUNT_H_ 1
#define _FREEBSD_SYS_MOUNT_H_ 1

/* Ensure errno is available */
#ifndef errno
extern int errno;
#endif

/* Add missing directory entry structure */
#ifndef _DIRENT_H_
struct dirent64 {
    unsigned long long d_ino;     /* file number of entry */
    unsigned short d_reclen;      /* length of this record */
    unsigned char  d_type;        /* file type, see below */
    unsigned char  d_namlen;      /* length of string in d_name */
    char     d_name[256];         /* name must be no longer than this */
};

/* DIR structure definition */
struct _dirdesc {
    int fd;                       /* file descriptor */
    long tell;                    /* directory position */
    long size;                    /* buffer size */
    char *buf;                    /* buffer */
    int dd_len;                   /* size of data in buffer */
    long dd_seek;                 /* current seek offset */
};
typedef struct _dirdesc DIR;
#endif

/* Add missing access mode constants */
#ifndef R_OK
#define R_OK 4    /* Test for read permission */
#define W_OK 2    /* Test for write permission */
#define X_OK 1    /* Test for execute permission */
#define F_OK 0    /* Test for existence */
#endif

/* Add missing fallocate constants */
#ifndef FALLOC_FL_PUNCH_HOLE
#define FALLOC_FL_PUNCH_HOLE    0x02
#define FALLOC_FL_KEEP_SIZE     0x01
#endif

/* timespec structure for time handling compatibility */
#ifndef _STRUCT_TIMESPEC
#define _STRUCT_TIMESPEC

/* time_t type for timespec */
#ifndef _TIME_T_DECLARED
#define _TIME_T_DECLARED
typedef long time_t;
#endif

/* clockid_t type for clock operations */
#ifndef _CLOCKID_T_DECLARED
#define _CLOCKID_T_DECLARED
typedef int clockid_t;
#endif

/* useconds_t type for microsecond counts */
#ifndef _USECONDS_T_DECLARED
#define _USECONDS_T_DECLARED
typedef unsigned int useconds_t;
#endif

struct timespec {
    time_t tv_sec;    /* seconds */
    long   tv_nsec;   /* nanoseconds */
};

/* timeval structure for compatibility */
#ifndef _STRUCT_TIMEVAL
#define _STRUCT_TIMEVAL
struct timeval {
    time_t tv_sec;    /* seconds */
    long   tv_usec;   /* microseconds */
};
#endif

/* struct tm for time representation */
struct tm {
    int tm_sec;     /* seconds after the minute [0-60] */
    int tm_min;     /* minutes after the hour [0-59] */
    int tm_hour;    /* hours since midnight [0-23] */
    int tm_mday;    /* day of the month [1-31] */
    int tm_mon;     /* months since January [0-11] */
    int tm_year;    /* years since 1900 */
    int tm_wday;    /* days since Sunday [0-6] */
    int tm_yday;    /* days since January 1 [0-365] */
    int tm_isdst;   /* Daylight Saving Time flag */
};

/* struct itimerval for interval timers */
struct itimerval {
    struct timeval it_interval; /* timer interval */
    struct timeval it_value;    /* current value */
};
#endif

/* Signal event structure */
#ifndef _SIGEVENT_DECLARED
#define _SIGEVENT_DECLARED
#ifndef __SYS__SIGVAL_H
#define __SYS__SIGVAL_H
union sigval {
    int     sival_int;
    void   *sival_ptr;
};
#endif

struct sigevent {
    int              sigev_notify;     /* Notification method */
    int              sigev_signo;      /* Signal number */
    union sigval     sigev_value;      /* Signal value */
    void           (*sigev_notify_function)(union sigval);
    void            *sigev_notify_attributes;
};
#endif

/* Timer structure definition */
#ifndef _STRUCT_ITIMERSPEC_DECLARED
#define _STRUCT_ITIMERSPEC_DECLARED
struct itimerspec {
    struct timespec it_interval;  /* Timer interval */
    struct timespec it_value;     /* Timer expiration */
};
#endif

struct __timer {
    int timer_id;
    clockid_t clock_id;
    void *data;
};

/* Timer types and constants */
#ifndef _TIMER_T_DECLARED
#define _TIMER_T_DECLARED
typedef struct __timer *timer_t;
#endif

/* ITIMER constants */
#ifndef ITIMER_REAL
#define ITIMER_REAL    0
#define ITIMER_VIRTUAL 1
#define ITIMER_PROF    2
#endif

/* Function declarations for filesystem operations (after all struct definitions) */
#ifndef __FREEBSD_FUNCTION_DECLS
#define __FREEBSD_FUNCTION_DECLS
int close(int fd);
struct dirent64 *readdir64(DIR *dir);
int readdir64_r(DIR *dir, struct dirent64 *entry, struct dirent64 **result);
int futimesat(int fd, const char *pathname, const struct timeval times[2]);
int utimes(const char *pathname, const struct timeval times[2]);
#endif

#endif /* _FREEBSDLIBC_COMPAT_H_ */