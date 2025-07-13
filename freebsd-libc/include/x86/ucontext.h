#ifndef _MACHINE_X86_UCONTEXT_H_
#define _MACHINE_X86_UCONTEXT_H_

/* x86 ucontext compatibility stub for FreeBSD libc */
/* This is a minimal stub for compatibility */

/* Basic register context structures for x86_64 */
struct __mcontext {
    long mc_onstack;        /* XXX - sigcontext compat. */
    long mc_rdi;            /* machine state (struct trapframe) */
    long mc_rsi;
    long mc_rdx;
    long mc_rcx;
    long mc_r8;
    long mc_r9;
    long mc_rax;
    long mc_rbx;
    long mc_rbp;
    long mc_r10;
    long mc_r11;
    long mc_r12;
    long mc_r13;
    long mc_r14;
    long mc_r15;
    long mc_trapno;
    long mc_addr;
    long mc_flags;
    long mc_err;
    long mc_rip;
    long mc_cs;
    long mc_rflags;
    long mc_rsp;
    long mc_ss;
    long mc_len;            /* sizeof(mcontext_t) */
    long mc_fpformat;
    long mc_ownedfp;
    long mc_fpstate[64];    /* FPU state (aligned) */
    long mc_spare[8];
};

typedef struct __mcontext mcontext_t;

#endif /* _MACHINE_X86_UCONTEXT_H_ */
