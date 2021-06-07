#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h> 

#define MAX 20

/* fills an array with n random integers */
void random_array(int array[], int n, int min, int max, int unique);
int in_array(int array[], int bound, int randomnumber);

int main() {

    int n = 11;
    int a[MAX];
    random_array(a, n, 10, 20, 1);

    for (int i = 0; i<n; i++) {
        printf("%6d%c", a[i], (i%10==9 || i==n-1) ? '\n' : ' ');
    }




    return 0;
}
/* fills an array with n random integers, min to max (inclusive) */
/* the numbers are not repeated if unique == 1 */
void random_array(int array[], int n, int min, int max, int unique) {
    /* initialize random seed: */
    srand(time(NULL));
    if (((max-min+1) < n) & unique == 1) {
        printf("Can not produce unique random numbers.  Range is too small.\n");
        return;
    }

    int randomnumber;
    int i = 0;
    while (i < n) {
        /* generate random number between min and max */
        randomnumber = rand() % (max - min + 1) + min;
        if (unique != 1 | !in_array(array, i, randomnumber)) {
            array[i] = randomnumber;
            ++i;
        }
    }

    return;
}
int in_array(int array[], int bound, int randomnumber) {
    for (int j = 0; j<=bound; ++j) {
        if (array[j] == randomnumber) return 1;
    }
    return 0;
}