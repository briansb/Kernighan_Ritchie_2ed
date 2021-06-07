#include <stdio.h>

int main() {

    union test {
        int a;
        float b;
    } hope;
    
    hope.b = 4.5;

    printf("b = %f\n", hope.b  );
}