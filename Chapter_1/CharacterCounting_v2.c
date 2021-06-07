#include <stdio.h>

/* count characters in input; 2nd version */
int main() 
{
    double nc;

    for (nc = 0; getchar() != EOF; ++nc) 
        ;  // for statement must have a body...so this is a null statement
    printf("%.0f\n", nc);
}
