/* test_better.c - Better test program for FreeBSD libc */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    /* Test basic string output */
    puts("Hello from FreeBSD libc!");
    
    /* Test printf with string */
    printf("This is a test: %s\n", "SUCCESS");
    
    /* Test some basic string functions if available */
    char test_str[] = "Hello World";
    printf("String length: %d\n", (int)strlen(test_str));
    
    return 0;
}

/* Entry point for freestanding environment */
void _start() {
    int ret = main();
    exit(ret);
}
