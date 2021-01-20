#include <stdio.h>
#include <string.h>

//int strlen_bb(char *s);
/*   NOTE:  declaration parameter is different than defintion parameter */
int strlen_bb(char s[]);

int main() {

    char x[14] = "this is a test";
    printf("%s is %d characters long.\n", x, strlen_bb(x));

    printf("%s is %d characters long.\n", x, strlen_bb(&x[0]));

    printf("%s is %d characters long.\n", x, strlen_bb(x+3));


    return 0;
}


/* strlen:  return length of string */
int strlen_bb(char *s) {
    int n;
    for (n = 0; *s != '\0'; s++)
        n++;
    return n;
}