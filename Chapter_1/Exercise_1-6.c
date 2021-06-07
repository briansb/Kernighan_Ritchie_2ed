#include <stdio.h>

/* get value of 'getchar() != EOF' */
int main() 
{
	// type in any character, which will yield 1
    // or ctrl-d, which will yield 0
    printf("%3d\n", (getchar() != EOF));
}
