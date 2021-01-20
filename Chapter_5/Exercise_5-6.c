#include <stdio.h> 
#include <ctype.h>
#include <string.h> /* strlen */

#define MAXLINE 1000  /*maximum input line length */
#define MAXOP   100     /* max size of operand or operator */
#define BUFSIZE 100     /* max size of ungetch buffer */
#define NUMBER  '0'     /* signal that number was found */


int getline_ptr(char *line, int max);
int atoi_ptr(char *s);
void itoa_ptr(int n, char *s);
void reverse_ptr(char s[]);
int strindex_ptr(char *s, char *t);



char buf[BUFSIZE];
int bufp = 0;
char getch_ptr(void);
void ungetch_ptr(int c);
int getop(char s[]);
char *ptr = buf;

int main() {

    // char line[MAXLINE];
    // int length = getline_ptr(line, MAXLINE);
    // printf("Input line = %sLength = %d\n", line, length);

    // char *s = "    -125";
    // printf("%s = %d\n", s, atoi_ptr(s));
    // char *t = "7474747";
    // printf("%s = %d\n", t, atoi_ptr(t));


    // char s[11] = "bbirmingham";
    // printf("%s reversed = ", s);
    // reverse_ptr(s);
    // printf("%s\n", s);

    // int n = -12647;
    // char s[MAXLINE];
    // itoa_ptr(n,s);
    // printf("Numeric %d = %s\n", n, s);

    // char s[11] = "birmingham";
    // char *t = "gha";
    // int index = strindex_ptr(s,t);
    // printf("strindex_ptr returned %d\n", index);

    char s[MAXOP];
    int type;

    while ((type = getop(s)) != EOF) {
        printf("Type = %d\n", type);
    }

    

    return 0;
}
/* getop: get next operator or numeric operand. Pointer version */
int getop(char s[]) {
    int i, c;

    while ((*s = c = getch_ptr()) == ' ' || c == '\t')
        ;
    *++s = '\0';
    if (!isdigit(c) && c != '.')
        return c;       /* not a number */
    i = 0;
    if (isdigit(c))     /* collect integer part */
        while (isdigit(*++s = c = getch_ptr()))
            ;
    if (c == '.')       /* collect fraction part */
        while (isdigit(*++s = c = getch_ptr()))
            ;
    *s = '\0';
    if (c != EOF)
        ungetch_ptr(c);

    return NUMBER;
}
/* get a (possibly pushed back) character. Pointer version*/
char getch_ptr(void) {       
    return (*ptr != '\0') ? *--ptr : getchar();
}
/* push character back on input. Pointer version */
void ungetch_ptr(int c) {   
    // no buffer size check;
    *ptr++ = c;
}

/* strindex:  return index of t in s, -1 if none.  Pointer version */
int strindex_ptr(char *s, char *t) {
    int index;
    char *orig_t = t;
    for (index = 0; *s != '\0'; index++)
        if ( *s == *t ) {
            while (*++s == *++t && *s != '\0') ;
            if (*t == '\0') return index;
            t = orig_t;
        } else *s++; 
    
    return -1;
}

/* itoa:  convert n to characters in s.  Pointer version */
void itoa_ptr(int n, char *s) {
    int sign;
    char *t = s;    /* need to remember starting address */

    if ((sign = n) < 0)    /* record sign */
        n = -n;            /* and make n positive */
    do {                        /* generate digits in reverse order */
        *s++ = n % 10 + '0';    /* get next digit */
    } while ((n /= 10) > 0);    /* delete it */
    if (sign < 0) *s++ = '-';
    *s = '\0';
    s = t;                  /* reset s to starting address */
    reverse_ptr(s);
    return;
}

/* reverse:  reverse string s in place.  Pointer version */
void reverse_ptr(char *s) {
    char c;
    char *t = s;

    /* find end of t */
    while (*++t) ;
    --t;
    while (s < t) {
        c = *s; *s = *t; *t = c;
        s++; t--;
    }
    return;
}

/* atoi_ptr:  convert string to integer.  Pointer version */
int atoi_ptr(char *s) {
    int n, sign;

    for ( ; isspace(*s); s++ )  /* skip white space */
        ;
    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-')  /* skip sign */
        s++;
    for (n = 0; isdigit(*s); s++)
        n = 10 * n + (*s - '0');
    return sign * n;
}

/* getline_ptr: get line into s, return length.  Pointer version */
int getline_ptr(char *s, int lim) {
    char *ptr;
    ptr = s;
    int c;
    while (--lim > 0 && (c=getchar()) != EOF && c != '\n') 
        *s++ = c;
    if (c == '\n') 
        *s++ = c;
    *s = '\0';

    return s - ptr;
}