#include <stdio.h>

#define MAXLETTERS 10  /* maximum word length - 1 */

/* vertical histogram of word lengths */
int main() 
{
    int i, j, c, nc;
    int nletters[MAXLETTERS];   /* nletters[i] - the number of words with i characters */
    int max;

    for (i =0; i < MAXLETTERS; ++i)
        nletters[i] = 0;
    nc = 0;
    
    while ((c = getchar()) != EOF) {
        ++nc;

        if (c == ' ' || c == '\n' || c == '\t') {
            ++nletters[nc-1];
            nc = 0;
        }

    }
    
    printf("Histogram: \n");
    // First:  find biggest number in nletters
    max = 0;
    for (i = 0; i < MAXLETTERS-1; ++i) {
        if (nletters[i] > max) { max = nletters[i]; }
    }

    for (i = max; i > 0; --i) {   /* loop through all max lines */
        printf("\t");
        for (j = 1; j < MAXLETTERS; ++j) {
            if ( nletters[j] >= i) {
                printf("    *");
            } else {
                printf("     ");
            }
        }
        printf("\n");
    }
    printf("Characters: 1    2    3    4    5    6    7    8    9\n");
}
