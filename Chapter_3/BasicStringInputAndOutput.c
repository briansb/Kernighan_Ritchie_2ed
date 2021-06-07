#include <stdio.h>

#define MAXCHARS 1000

int main() {
    char s[MAXCHARS];
    
    int i = 0;
    char c;
    while ((c = getchar()) != EOF) {
        s[i++] = c;
    }
    s[i] = '\0';

    i = 0;
    while ((c = s[i++]) != '\0') printf("%c", c);
    printf("\n");

    return 0;
}