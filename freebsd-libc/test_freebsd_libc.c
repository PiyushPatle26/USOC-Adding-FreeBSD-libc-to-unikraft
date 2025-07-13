#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    printf("=== FreeBSD libc Test ===\n");
    
    // Test printf
    printf("1. printf() test: Hello from FreeBSD libc!\n");
    
    // Test string functions
    char str1[] = "Hello";
    char str2[] = "World";
    char result[20];
    
    strcpy(result, str1);
    strcat(result, " ");
    strcat(result, str2);
    
    printf("2. String functions test: %s\n", result);
    printf("3. strlen() test: Length of '%s' is %zu\n", result, strlen(result));
    
    // Test memory functions
    char buffer[10];
    memset(buffer, 'A', 9);
    buffer[9] = '\0';
    printf("4. memset() test: %s\n", buffer);
    
    printf("=== Test completed successfully! ===\n");
    return 0;
}
