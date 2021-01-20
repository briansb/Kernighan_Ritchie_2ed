#include <stdio.h>
#include <string.h>

/* itoa:  convert n to characters in s */
/* width is the minimum field width */
void itoa(int n, char s[], int width);
void reverse(char s[]);

int main() {
    char s[15];
    char c;
    int i;

    int n = -285;
    int width = 10;
    itoa(n, s, width);
    i = 0;
    printf("%d = ", n);
    while ((c = s[i++]) != '\0') printf("%c", c);
    printf("\n");

    return 0;
}
/* itoa:  convert n to characters in s */
void itoa(int n, char s[], int width) {
    int i, sign;

    if ((sign = n) < 0)    /* record sign */
        n = -n;            /* and make n positive */
    i = 0;
    do {                   /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);   /* delete it */
    if (sign < 0) s[i++] = '-';
    /* add padding */
    while (i < width) s[i++] = ' ';
    s[i] = '\0';
    reverse(s);
    return;
}
/* reverse:  reverse string s in place */
void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        // c = s[i];
        // s[i] = s[j];
        // s[j] = c;
        c = s[i], s[i] = s[j], s[j] = c;
    }
    return;
}