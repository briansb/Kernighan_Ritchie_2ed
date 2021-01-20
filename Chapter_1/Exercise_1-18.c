#include <stdio.h>
#define MAXLINE 1000    /* maximum input line size */

/* had to change name to get_line...conflicted with some library function */
int get_line_noblanks_notabs(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
/* for exercise, get_line -> get_line_noblanks_notabs */
int main()
{
    int len;        /* current line length */
    int max;        /* maximum length seen so far */
    char line[MAXLINE];     /* current input line */
    char longest[MAXLINE];  /* longest line saved here */

    max = 0;
    while ((len = get_line_noblanks_notabs(line, MAXLINE)) > 0) {
        if (len > max) {
            max = len;
            copy(longest, line);
        } 
        printf("This line was %d characters long:\n", len);
        printf("%s",line); 
    }
    
    return 0;
}

/* get_line:  read a line into s, return length */
int get_line_noblanks_notabs(char s[], int lim)
{
    int c, i;
    int has_newline = 0;  /* 0 is line does not have \n, 1 is it does */

    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    /* here are the revisions */
    if (c == '\n') {
        has_newline = 1;   /* save new line information */
    }
    /* check for trailing blanks and tabs */
    --i;   /* i now points to last char */
    for (i; s[i] == 32 || s[i] == '\t'; --i)
        ;
    /* i is now pointing to the last "real" character */
    if (has_newline ==1) {
        ++i;
        s[i] = '\n';
    }
    s[i+1] = '\0';
    return i+1;
}

/* copy: copy 'from' into 'to'; assume 'to' is big enough */
void copy(char to[], char from [])
{
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}