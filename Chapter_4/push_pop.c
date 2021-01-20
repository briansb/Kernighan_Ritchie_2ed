#include <stdio.h>

#define MAXVAL  100     /* maximum depth of val stack */

int sp = 0;             /* next free stack position */
double val[MAXVAL];     /* value stack */

/* push:  push value onto stack */
void push (double f);
/* pop:  pop and return value from stack */
double pop(void);

int main () {
    push(3.0);
    push(5.0);
    push(7.0);
    printf("value = %g\n", pop());
    printf("value = %g\n", pop());

    push(10.0);
    printf("value = %g\n", pop());

    return 0;
}
/* push:  push f onto value stack */
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error:  stack full, can't push %g\n", f);
}
double pop(void) {
    if (sp >0)
        return val[--sp];
    else {
        printf("error:  stack empty\n");
        return 0.0;
    }
}