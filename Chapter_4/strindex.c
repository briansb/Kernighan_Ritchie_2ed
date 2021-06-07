#include <stdio.h>
#define MAXLINE 1000  /*maximum input line length */

/* must call this getline_bb, because system already has a getline() */
int getline_bb(char line[], int max);
/* strindex:  return index of t in s, -1 if none */
int strindex(char source[], char searchfor[]);

char pattern[] = "ould";      /* pattern to search for */

/* find all lines maching pattern */
int main() {
    char line[MAXLINE];
    int found = 0;

    while (getline_bb(line, MAXLINE) > 0)
        if (strindex(line, pattern) >= 0) {
            printf("%s", line);
            found++;
        }
    return found;
}

/* strindex:  return index of t in s, -1 if none */
int strindex(char s[], char t[]) {
    int i, j, k;

    for (i = 0; s[i] != '\0'; i++) {
        /* if this for loop runs to completion, 
           then a match was found, and t[k] will
           be equal to the null terminator */
        for (j=i, k=0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            return i;
    }
    return -1;
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