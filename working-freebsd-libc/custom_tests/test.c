#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Hello from FREEBSD libc!\n");
    return 0;
}

void _start() {
    int ret = main();
    exit(ret);
} 

