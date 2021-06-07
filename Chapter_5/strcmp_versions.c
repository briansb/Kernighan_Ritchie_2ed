#include <stdio.h>

int strcmp_array(char *s, char *t);
int strcmp_pointer(char *s, char *t);

int main() {

    char *s1 = "brian";
    char *t1 = "brian";
    char *u1 = "bryan";
    printf("Strcmp_array = %d\n", strcmp_array(s1, t1));
    printf("Strcmp_array = %d\n", strcmp_array(s1, u1));



    char *s2 = "brian";
    char *t2 = "brian";
    char *u2 = "bryan";
    printf("Strcmp_array = %d\n", strcmp_pointer(s2, t2));
    printf("Strcmp_array = %d\n", strcmp_pointer(s2, u2));

    return 0;
}

/* strcmp:  return <0 if s<t, 0 if s==t, >0 if s>t */
int strcmp_pointer(char *s, char *t) {
    
    // for ( ; *s == *t; s++, t++) 
    //     if (*s == '\0')
    //         return 0;
    // return *s - *t;
    // my version
    for ( ; *s == *t & *s != '\0'; s++, t++) 
            ;
    return *s - *t;
}

/* strcmp:  return <0 if s<t, 0 if s==t, >0 if s>t */
int strcmp_array(char *s, char *t) {
    int i;

    for (i = 0; s[i] == t[i]; i++) 
        if (s[i] == '\0')
            return 0;
    return s[i] - t[i];
}