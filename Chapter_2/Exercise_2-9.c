#include <stdio.h>

/* count the 1 bits in x */
int bitcount_v2(unsigned x);

/* Exercise 2-9.  Faster version of bitcount */
int main() {
        /* x &= (x-1)  */
        /*  With two's complement, it somehow masks off the all the zeros
            until it hits a one.  */

    if (7) printf("true\n"); else printf("false\n");
    if (6) printf("true\n"); else printf("false\n");
    if (5) printf("true\n"); else printf("false\n");
    if (4) printf("true\n"); else printf("false\n");
    if (3) printf("true\n"); else printf("false\n");
    if (2) printf("true\n"); else printf("false\n");
    if (1) printf("true\n"); else printf("false\n");
    if (0) printf("true\n"); else printf("false\n");

    unsigned x = 3486;
    printf("%d has %d ones\n", x, bitcount_v2(x));

    return 0;
}

int bitcount_v2(unsigned x) {
    int b = 1;
    while (x &= (x-1)) b++;
    return b;
}