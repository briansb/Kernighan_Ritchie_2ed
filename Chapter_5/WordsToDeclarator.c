#include <stdio.h>
#include <string.h> /* for strcpy, strcat, isalpha, isalnum */
#include <ctype.h>  /* for strcpy, strcat, isalpha, isalnum */

#define MAXTOKEN 100
#define BUFSIZE 100     /* max size of ungetch buffer */

enum {NAME, PARENS, BRACKETS };

int gettoken(void);
int tokentype;              /* type of last token */
char token[MAXTOKEN];       /* last token string */
char out[1000];             /* output string */

int getch(void);
void ungetch(int c);
char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;           /* next free position in buf */

/* undcl:  convert word descriptions to declarations */
int main() {
    int type;
    char temp[MAXTOKEN];

    while (gettoken() != EOF) {
        strcpy(out, token);
        while ((type = gettoken()) != '\n')
            if (type == PARENS || type == BRACKETS)
                strcat(out, token);
            else if (type == '*') {
                sprintf(temp, "(*%s)", out);
                strcpy(out, temp);
            } else if (type == NAME) {
                sprintf(temp, "%s %s", token, out);
                strcpy(out,temp);
            } else
                printf("invalid input at %s\n", token);
        printf("%s\n", out);
    }
    return 0;
}

int gettoken(void) {        /* return next token */
    int c;
    char *p = token;

    while ((c = getch()) == ' ' || c == '\t')
        ;
    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']'; )
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch()); )
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else
        return tokentype = c;
}

int getch(void) {       /* get a (possibly pushed back) character */
    return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c) {   /* push character back on input */
    if (bufp >= BUFSIZE)
        printf("ungetch:  too many characters\n");
    else
        buf[bufp++] = c;
}