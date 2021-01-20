#include <stdio.h>

/* print input one word at a time */
int main() 
{	
    int c ;
    
    c = getchar();
    while (c != EOF) {
        if (c == ' ' || c == '\n' || c == '\t')
            putchar('\n');
        else 
            putchar(c);
        c = getchar();       
    }
}
