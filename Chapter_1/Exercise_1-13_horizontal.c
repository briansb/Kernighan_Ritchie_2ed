#include <stdio.h>

#define MAXLETTERS 10

/* horizontal histogram of word lengths */
int main() 
{
    int i, j, c, nc;
    int nletters[MAXLETTERS];   /* nletters[i] - the number of words with i characters */

    for (i =0; i < MAXLETTERS; ++i)
        nletters[i] = 0;
    nc = 0;
    
    while ((c = getchar()) != EOF) {
        ++nc;

        if (c == ' ' || c == '\n' || c == '\t') {
            //printf("Word has %d characters\n", nc-1);
            ++nletters[nc-1];
            nc = 0;
        }

    }
    
    printf("Histogram: \n");
    for (i =1; i < MAXLETTERS; ++i) {
        printf("%d-character words:  ", i);
        while (nletters[i] > 0) {
            printf("*");
            --nletters[i];
        }
        printf("\n");
    }
}
