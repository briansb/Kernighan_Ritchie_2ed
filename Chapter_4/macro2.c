#include <stdio.h>

#define dprint(expr) printf(#expr " = %g\n", expr)

int main() {

    double x, y;

    x = 11;
    y = 5;

    dprint(x/y);  /* expands to printf("x/y = %g\n", x/y);  */
    
    return 0;
    
}