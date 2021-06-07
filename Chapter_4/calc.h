#define NUMBER  '0'     /* signal that a number was found */
void push (double f);   /* push value onto stack */
double pop(void);       /* pop and return value from stack */
int getop(char s[]);    /* getop: get next operator or numeric operand */
int getch(void);        /* get a (possibly pushed back) character */
void ungetch(int);      /* push character back on input */