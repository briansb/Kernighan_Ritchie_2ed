#include <stdio.h>

/* itoa:  convert n to characters in s using recursion */
void itoa_recursive(int n, char s[]);

static int index;

int main() {
    char s[15];
    char c;
    int i;

    index = 0;
    int n = -2073;
    itoa_recursive(n, s);
    i = 0;
    printf("%d = ", n);
    while ((c = s[i++]) != '\0') printf("%c", c);
    printf("\n");

    return 0;
}

void itoa_recursive(int n, char s[]) {
    if (n < 0) {
        s[index++] = '-';
        n = -n;
    }
    if (n / 10) {
        itoa_recursive(n / 10, s);
    }
    s[index++] = n % 10 + '0';  /* the '0' is added to make n an ASCII character */
    s[index] = '\0';
    return;
}