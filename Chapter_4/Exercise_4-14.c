#include <stdio.h>

#define SWAP(T, X, Y) T t; t = X; X = Y; Y = t;

int main() {

    float x, y;
    x = 4.8;
    y = 1.5;

    printf("x = %f\n", x);
    printf("y = %f\n", y);

    SWAP(float, x, y);

    printf("x = %f\n", x);
    printf("y = %f\n", y);

    return 0;
}