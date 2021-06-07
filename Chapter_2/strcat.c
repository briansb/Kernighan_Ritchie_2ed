#include <stdio.h>

void my_strcat(char s[], char t[]);

int main() {
    char a[100] = "brian";
    char b[] = " birmingham";
    
    my_strcat(a, b);
    printf("New string = %s\n", a);

    return 0;
}

/* concatenate t to end of s; s must be big enough */
void my_strcat(char s[], char t[]) {
    int i, j;

    i = j = 0;
    /* find end of s */
    while (s[i] != '\0') i++;

    /* copy t to end of s */
    while ((s[i++] = t[j++]) != '\0') 
        ;
}