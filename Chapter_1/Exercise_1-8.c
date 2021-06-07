#include <stdio.h>

/* count blanks (ASCII 32), tabs (ASCII 9), newlines (ASCII 10) */
int main() 
{
	int c, n1;

    n1 = 0;
    while ((c = getchar()) != EOF) {
        if (c == 32) ++n1;
        if (c == 9) ++n1;
        if (c == 10) ++n1;
    }
    printf("%d\n", n1);

}
