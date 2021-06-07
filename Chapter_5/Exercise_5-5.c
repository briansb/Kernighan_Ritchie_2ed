#include <stdio.h> 
#include <string.h>

char *strncpy_bb(char *s, const char *ct, int n);
char *strncat_bb(char *s, const char *ct, int n);
int strncmp_bb(const char *cs, const char *ct, int n);

int main() {
    // strncpy
    // char s[10];
    // const char ct[] = "brian";
    // int n = 6;

    // char *result = strncpy_bb(s, ct, n);
    // printf("strncpy = %s\n", result);
    // printf("strncpy = %s\n", s);

    // strncat
    // char s[20] = "brian";
    // const char ct[11] = "birmingham";
    // int n = 3;

    // char *result = strncat_bb(s, ct, n);
    // printf("strncat = %s\n", result);
    // printf("strncat = %s\n", s);

    // strncmp
    char cs[11] = "birmingham";
    const char ct[11] = "birmx";
    int n = 5;

    int result = strncmp_bb(cs, ct, n);
    if (result < 0) 
        printf("%s < %s\n", cs, ct);
    else if (result == 0)
        printf("%s = %s\n", cs, ct);
    else
        printf("%s > %s\n", cs, ct);
    
    return 0;
}
/* strncmp:  compare at most n characters of string cs to string ct;
             return <0 if cs<ct, 0 if cs==ct, or >0 if cs>ct */
int strncmp_bb(const char *cs, const char *ct, int n) {

    while ((--n > 0) && ( *cs++ == *ct++ ))
        ;
    return *cs - *ct;
}

/* strncat:  concatenate at most n characters of string ct to string s, 
             terminate s with '\0'; return s. */
char *strncat_bb(char *s, const char *ct, int n) {
    int index = 0;
    /* find end of s */
    while ((*++s) && (++index))
        ;

    /* copy ct to end of s */
    while ( ++index && (*s++ = *ct++) && (--n != 0))
        ;

    /* terminate with '\0' */
    *s = '\0';

    return s - (char)(index+1);
}

/* strncpy:  copy at most n characters of string ct to s; return s.  
             Pad with '\0's if ct has fewer than n characters */
char *strncpy_bb(char *s, const char *ct, int n) {
    int index = 0;
    /* copy ct to s while ct has characters and while n is not 0 */
    while ( ++index && (*s++ = *ct++) && (--n != 0))
        ;
    /* may need padding */
    while ( index++ && (n-- > 0))
        *s++ = '\0';
        
    return s - (char)(index-1); /* index is a counter of how many steps have occurred
                                    BUT...it's an integer, and pointer arithmetic must
                                    happen with the same type of pointer */
}


