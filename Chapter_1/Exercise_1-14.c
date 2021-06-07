#include <stdio.h>

#define ASCII_CHARACTERS 127

/* horizontal histogram of character frequency */
/* use an array of dimensions 126...for the ASCII codes 0 through 126 */
/*  ....then, increment the "ASCII index" when that character occurs */
int main() 
{
    int i, c;
    int numchars[ASCII_CHARACTERS];   /* numchars[i] - the number of occurrences of i character */

    for (i =0; i < ASCII_CHARACTERS; ++i) numchars[i] = 0;

    while ((c = getchar()) != EOF) {
        ++numchars[c];
    }
    
    printf("Histogram: \n");
    for (i = 32; i < ASCII_CHARACTERS; ++i) {
        /* only print the printable characters, ie, ASCII 32 through 126 */
        /* only print the frequencies for the characters that actually appeared */
        if (numchars[i] != 0 ) {
            printf("%c occurs %d times\n", i, numchars[i]);
        }
    }

    return 0;
}
