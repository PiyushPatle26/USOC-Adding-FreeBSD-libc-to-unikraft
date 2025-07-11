#include <stdio.h>
void _start() {
    printf("Hello from stub-patched FreeBSD libc!\n");
    while (1); // prevent return
}
