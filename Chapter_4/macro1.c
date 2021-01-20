#include <stdio.h>

#define max(A,B)  ((A) > (B) ? (A) : (B))

int main() {

    int p, q, r, s;

    p = 4;
    q = 5;
    r = 101;
    s = 102;

    printf("max = %d\n", max(p+q, r+s));

    return 0;
    
}