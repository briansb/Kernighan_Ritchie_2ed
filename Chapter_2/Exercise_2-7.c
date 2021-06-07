#include <stdio.h>

unsigned ones(int n);
unsigned ones_mask(int p, int n);
unsigned getbits(unsigned x, int p, int n);
unsigned setbits(unsigned x, int p, int n, unsigned y);
unsigned invert(unsigned x, int p, int n);


int main() {
    int x = 2667;
    int p = 7;
    int n = 4;

    printf("In %d, invert %d bits starting at %d = %d\n", x, n, p, invert(x,p,n));

    return 0;
}

/* inverts n bits of x, beginning at p */
unsigned invert(unsigned x, int p, int n) {
    return setbits(x,p,n,getbits(~x,p,n));
}


/* sets the n-bits of x, beginning at p, to the rightmost n bits of y */
/* the rest of x is unchanged */
/* assumes p >= n-1 */
unsigned setbits(unsigned x, int p, int n, unsigned y) {
    /* the middle bits (starting at p, and n bits long) of x are zeroed */
    /* unsigned middle = x & (~ones_mask(p,n)); */
    /* or expanded... */
    /* unsigned middle = x & (~(~(~0 << n) << (p - n + 1))); */

    /* target is the rightmost n bits of y, shifted left the correct amount */
    /* unsigned target = getbits(y,n-1,n) << (p-n+1); */
    /* or expanded... */
    /* unsigned target = (y & ~(~0 << n)) << (p-n+1); */

    /* return middle | target; */
    /* or expanded... */
    return (x & (~(~(~0 << n) << (p - n + 1)))) | ((y & ~(~0 << n)) << (p-n+1));
}

/* returns the right-adjusted n-bit field of x that starts at p */
/* assumes p >= n-1  */
unsigned getbits(unsigned x, int p, int n){
    /* overview - a mask operation */
    /* first - the mask is ~(~0 << n).  Take a bunch of ones, shift them left (zeros fill the blanks).
               You are left with a word that has all ones except the right n bits.  Then, ones complement again
               and you have a mask for just the right n bits.  Ex.  n = 5 would give mask of 0000000000011111   */
    /* second - move n bits to the right p - n + 1 places.  Or, take the rightmost bit in question and put it
               in the rightmost word position */
    return (x >> (p+1-n)) & ~(~0 << n);
}
/* returns a mask of n 1's starting at p */
unsigned ones_mask(int p, int n) {
    /* return ones(n) << (p - n + 1); */
    /* or expanded... */
    return ~(~0 << n) << (p - n + 1);
}
/* returns a rightmost field of n 1's */
/* obviously, n > 0 */
unsigned ones(int n) {
    return ~(~0 << n);
}