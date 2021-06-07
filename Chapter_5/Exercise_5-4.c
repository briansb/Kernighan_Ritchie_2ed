#include <stdio.h>

int strend(char *s, char *t);

int main() {

    char a[] = "brian birmingham";
    char b[] = "mingham";
    
    if (strend(a, b) )
        printf("%s found at the end of %s\n", b, a);
    else
        printf("%s not found at end of %s\n", b, a);

    return 0;
}

/* strend:  returns 1 if t occurs at end of s, 0 otherwise */
int strend(char *s, char *t) {

    /* find end of s */
    while (*++s)
        ;
    /* find end of t */
    while (*++t)
        ;

    /* step backward through both strings */
    while (*--s == *--t) 
        ;
    
    /* *t = '\0' means above stepped all the way through t */
    if (*t) { 
        return 0;
    } else {
        return 1;
    }
    
}