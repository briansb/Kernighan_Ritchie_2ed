#include <stdio.h>

void strcpy_array(char s[], char t[]);
void strcpy_pointer(char *s, char *t);
void strcpy_pointer_improved(char *s, char *t);
void strcpy_pointer_final(char *s, char *t);

int main() {

    char t[] = "birmingham";
    char s[11];
    strcpy_array(s, t);
    printf("%s\n", s);

    char t1[] = "brian";
    char s1[6];
    strcpy_pointer(s1, t1);
    printf("%s\n", s1);

    char t2[] = "stephen";
    char s2[8];
    strcpy_pointer_improved(s2, t2);
    printf("%s\n", s2);

    char t3[] = "this is a test";
    char s3[15];
    strcpy_pointer_final(s3, t3);
    printf("%s\n", s3);

    return 0;
}

/* strcpy:  copy t to s; pointer version 3 */
void strcpy_pointer_final(char *s, char *t) {
    while (*s++ = *t++) /* we only need to check for zero */
        ;
}

/* strcpy:  copy t to s; pointer version 2 */
void strcpy_pointer_improved(char *s, char *t) 
{
    while ((*s++ = *t++) != '\0')
        ;
}

/* strcpy:  copy t to s; pointer version 1 */
void strcpy_pointer(char *s, char *t)
{
    while ((*s = *t) != '\0') {
        s++;
        t++;
    }
}

/* strcpy:  copy t to s; array subscript version */
void strcpy_array(char s[], char t[]) 
{
    int i = 0;
    while ((s[i] = t[i]) != '\0') 
        i++;
}