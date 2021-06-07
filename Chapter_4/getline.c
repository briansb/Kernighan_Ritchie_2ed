#include <stdio.h>
#define MAXLINE 1000  /*maximum input line length */

/* must call this getline_bb, because system already has a getline() */
int getline_bb(char line[], int max);

int main() {
    char line[MAXLINE];
    while (getline_bb(line, MAXLINE) > 0)
        printf("Input line = %s\n", line);

    return 0;

}

/* getline: get line into s, return length */
int getline_bb(char s[], int lim) {
    int c, i;
    i = 0;
    while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}