#include <stdio.h>

/* count the 1 bits in x */
int bitcount(unsigned x);

int main() {


    int x = 7;
    printf("%d has %d ones\n", x, bitcount(x));

    return 0;
}

int bitcount(unsigned x) {
    int b;
    for (b = 0; x!= 0; x >>=1) 
        if (x & 01)
            b++;
    return b;
}