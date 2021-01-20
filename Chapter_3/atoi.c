#include <stdio.h>
#include <ctype.h>

int atoi(char s[]);

int main() {
    char c;
    int i = 0;
    char s[10];
    while ((c = getchar()) != EOF) s[i++] = c;
    s[i] = '\0';

    int n = atoi(s);

    printf("%s = %d\n", s, n);
    
    return 0;
}
int atoi(char s[]) {
    int i, n, sign;

    for (i = 0; isspace(s[i]); i++)  /* skip white space */
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')  /* skip sign */
        i++;
    for (n = 0; isdigit(s[i]); i++)
        n = 10 * n + (s[i] - '0');
    return sign * n;
}