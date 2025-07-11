#include <stdio.h>
int main() {
    printf("Hello from FreeBSD libc!\n");
    return 0;
}


void _start() {
    main();
    while(1); // trap if main returns
}



