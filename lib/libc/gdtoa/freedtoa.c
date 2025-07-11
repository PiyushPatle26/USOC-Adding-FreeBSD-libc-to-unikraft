// freedtoa.c
#include <stdlib.h>

void __freedtoa(void *p) {
    free(p);
}

