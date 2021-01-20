#include <stdio.h>

int atoi(char s[]);

int main() {

    char number[5] = "93201";
    printf("%s is the integer %d\n", number, atoi(number));

   return 0;
}

/* converts char arry to integer equivalent */
int atoi(char s[]) {
    int i, n;
    n = 0;
    for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
        n = 10 * n + (s[i] - '0');
    return n;
}