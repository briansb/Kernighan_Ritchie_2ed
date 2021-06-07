/*  Structure of program
    while (next operator or operand is not EOF)
        if (number)
            push it
        else if (operator)
            pop operands
            do operation
            push result
        else if (newline)
            pop and print top of stack
        else
            error
*/

#include <stdio.h>
#include <stdlib.h>     /* for atof() */
#include <ctype.h>      /* for isdigit() */
#include <string.h>     /* for strlen() */

#define MAXOP   100     /* max size of operand or operator */
#define NUMBER  '0'     /* signal that a number was found */
#define MAXVAL  100     /* maximum depth of val stack */

int sp = 0;             /* next free stack position */
double val[MAXVAL];     /* value stack */

void push (double f);   /* push value onto stack */
double pop(void);       /* pop and return value from stack */
int getop(char s[]);    /* getop: get next operator or numeric operand */
int getline_bb(char s[], int lim);

char line[MAXOP];
char *ptr;

/* reverse Polish calculator */
int main() {
    int type;
    float fval;
    double op2;
    char s[MAXOP];

    ptr = line;
    getline_bb(ptr, 100);

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                //push(atof(s));
                sscanf(s, "%f", &fval);
                push(fval);
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':                /* subtraction and division are not commutative */
                op2 = pop();         /*  so the order matters */
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error:  zero divisor\n");
                break;
            case '%':
                op2 = pop();
                if (op2 != 0.0)
                    push((int)pop() % (int)op2);
                else
                    printf("error:  zero modulo\n");
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                getline_bb(ptr, 100);
                if (!*ptr) return 0;
                break;
            default:
                printf("error:  unknown command %s\n", s);
                break;
        }
    }
    return 0;
}
int getop(char s[]) {
/* return operators as int, s = '\0'
   return '\n' as int, s = '\0'
   return NUMBER, s = the number itself as a string
*/   
    int j;
    char c;

    if (!*ptr) return '\n';
    
    j = sscanf(ptr, "%s", s);       /* adds \0 to end, if last item strips \n and adds \0 */
    ptr += strlen(s)+1;
    if (strlen(s) == 1) {
        sscanf(s, "%c", &c);
        if (!isdigit(c)) return c;
        else return NUMBER;
    } else return NUMBER;
    
}

void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error:  stack full, can't push %g\n", f);
}
double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error:  stack empty\n");
        return 0.0;
    }
}

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