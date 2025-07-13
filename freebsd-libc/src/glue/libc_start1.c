#include <uk/plat/bootstrap.h>
#include <uk/plat/console.h>
#include <uk/plat/memory.h>
#include <uk/plat/thread.h>

extern int main(int argc, char *argv[]);
extern void uk_plat_init(void);

/* Initialize FreeBSD libc */
void __libc_init(void)
{
    /* Initialize platform-specific components */
    uk_plat_init();
    
}

/* Main entry point for FreeBSD libc applications */
void _start(void)
{
    int argc;
    char **argv;
    
    /* Get command line arguments from Unikraft */
    ukplat_memregion_get_cmdline(&argc, &argv);
    
    /* Initialize FreeBSD libc */
    __libc_init();
    
    /* Call the application's main function */
    int ret = main(argc, argv);
    
    /* Exit with the return value from main */
    uk_syscall_r_exit(ret);
} 