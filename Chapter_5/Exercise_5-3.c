#include <stdio.h>

void strcat_pointer(char *s, char *t);

int main() {

    char a[100] = "brian";
    char b[] = " birmingham";
    
    strcat_pointer(a, b);
    printf("New string = %s\n", a);

    return 0;
}

/* concatenate t to end of s; s must be big enough */
void strcat_pointer(char *s, char *t) {

    /* find end of s */
    while (*++s)
        ;

    /* copy t to end of s */
    while (*s++ = *t++) 
        ;
}