#include <stdio.h>
#include <string.h>

#define MAXCHAR 100

void reverse_recursive(char s[], int start, int end);

int main() {
    char c;
    char s[MAXCHAR];

    int i = 0;
    while ((c = getchar()) != EOF) s[i++] = c;
    s[i-1] = '\0';   /* overwrite the CR with EOL */

    reverse_recursive(s, 0, strlen(s)-1);

    i = 0;
    while ((c = s[i++]) != '\0') printf("%c", c);
    printf("\n");


    return 0;
}

/* reverse_recursive:  reverse string s in place using recursion */
void reverse_recursive(char s[], int start, int end) {
    int c;
    if (start < end) {
        c = s[start];
        s[start] = s[end];
        s[end] = c;
        reverse_recursive(s, start+1, end -1);
    }
    return;
}