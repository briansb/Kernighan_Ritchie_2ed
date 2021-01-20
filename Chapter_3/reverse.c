#include <stdio.h>
#include <string.h>

#define MAXCHAR 100

void reverse(char s[]);

int main() {
    char c;
    char s[MAXCHAR];

    int i = 0;
    while ((c = getchar()) != EOF) s[i++] = c;
    s[i] = '\0';

    reverse(s);

    i = 0;
    while ((c = s[i++]) != '\0') printf("%c", c);
    printf("\n");


    return 0;
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