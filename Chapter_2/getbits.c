#include <stdio.h>

unsigned getbits(unsigned x, int p, int n);

int main() {
    int x = 91;
    int p = 4;
    int n = 2;

    printf("With %d, the %d bits starting at %d = %d\n", x, n, p, getbits(x, p, n));


    return 0;
}

/* returns the right-adjusted n-bit field of x that starts at p */
/* assumes p >= n  */
unsigned getbits(unsigned x, int p, int n){
    /* overview - a mask operation */
    /* first - the mask is ~(~0 << n).  Take a bunch of ones, shift them left (zeros fill the blanks).
               You are left with a word that has all ones except the right n bits.  Then, ones complement again
               and you have a mask for just the right n bits.  Ex.  n = 5 would give mask of 0000000000011111   */
    /* second - move n bits to the right p - n + 1 places.  Or, take the rightmost bit in question and put it
               in the rightmost word position */
    return (x >> (p+1-n)) & ~(~0 << n);
}