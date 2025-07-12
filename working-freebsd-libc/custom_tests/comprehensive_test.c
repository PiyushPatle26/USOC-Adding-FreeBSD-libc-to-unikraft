/* comprehensive_test.c - Test more FreeBSD libc functionality */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    printf("=== FreeBSD libc Test Suite ===\n");
    
    /* Test 1: Basic string output */
    puts("Test 1: Basic puts() function");
    
    /* Test 2: printf with string formatting */
    printf("Test 2: printf with string: %s\n", "Hello World");
    
    /* Test 3: printf with integer formatting */
    printf("Test 3: printf with integers: %d, %d, %d\n", 42, -17, 0);
    
    /* Test 4: printf with character formatting */
    printf("Test 4: printf with chars: %c %c %c\n", 'A', 'B', 'C');
    
    /* Test 5: printf with percent literal */
    printf("Test 5: printf with literal percent: 100%%\n");
    
    /* Test 6: String functions (if available) */
    char str1[] = "Hello";
    char str2[] = "World";
    char str3[20];
    
    printf("Test 6: String operations\n");
    printf("  strlen(\"%s\") = %d\n", str1, (int)strlen(str1));
    
    /* Test strcpy if available */
    strcpy(str3, str1);
    printf("  strcpy result: %s\n", str3);
    
    /* Test strcmp if available */
    int cmp = strcmp(str1, str2);
    printf("  strcmp(\"%s\", \"%s\") = %d\n", str1, str2, cmp);
    
    /* Test 7: Memory operations (if available) */
    char buffer[10];
    memset(buffer, 'X', 5);
    buffer[5] = '\0';
    printf("Test 7: memset result: %s\n", buffer);
    
    printf("=== All tests completed ===\n");
    return 0;
}

/* Entry point for freestanding environment */
void _start() {
    int ret = main();
    exit(ret);
}
