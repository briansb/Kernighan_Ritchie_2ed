#include <stdio.h>
#define MAXLINE 1000    /* maximum input line size */

/* had to change name to get_line...conflicted with some library function */
int get_line(char line[], int maxline);
void copy(char to[], char from[]);
void reverse(char s[]);

int main()
{
    int len;        /* current line length */
    int max;        /* maximum length seen so far */
    char line[MAXLINE];     /* current input line */
    char longest[MAXLINE];  /* longest line saved here */

    max = 0;
    while ((len = get_line(line, MAXLINE)) > 0) {
        reverse(line);
        printf("%s", line);
    }

    return 0;
}

void reverse(char s[]) {
    char temp[MAXLINE];
    int length = 0;
    int i;
    copy(temp, s);
    while (temp[length] != '\n')
        ++length;

    for (i = 0; i<length; ++i) {
        s[i] = temp[length-1-i];
    }
}

/* get_line:  read a line into s, return length */
int get_line(char s[], int lim)
{
    int c, i;

    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/* copy: copy 'from' into 'to'; assume 'to' is big enough */
void copy(char to[], char from [])
{
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}
