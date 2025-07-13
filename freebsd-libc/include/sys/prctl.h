#ifndef _SYS_PRCTL_H_
#define _SYS_PRCTL_H_

/* Linux prctl.h compatibility stub for FreeBSD libc */

/* Process control operations - minimal set for compatibility */
#define PR_SET_NAME         15      /* Set process name */
#define PR_GET_NAME         16      /* Get process name */
#define PR_SET_DUMPABLE     4       /* Set dumpable flag */
#define PR_GET_DUMPABLE     3       /* Get dumpable flag */

/* Function declaration */
int prctl(int option, unsigned long arg2, unsigned long arg3, 
          unsigned long arg4, unsigned long arg5);

#endif /* _SYS_PRCTL_H_ */
