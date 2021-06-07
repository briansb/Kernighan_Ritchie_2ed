#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h> 

#define MAX 15

void shellsort(int v[], int n);
void random_array(int array[], int n, int min, int max, int unique);
int in_array(int array[], int bound, int randomnumber);

int main () {
    int v[MAX];

    random_array(v, MAX, 0, 100, 1);
    for (int i = 0; i<MAX; i++) printf("%6d%c", v[i], (i%10==9 || i==MAX-1) ? '\n' : ' ');
    printf("\n");

    shellsort(v, MAX);

    for (int i = 0; i<MAX; i++) printf("%6d%c", v[i], (i%10==9 || i==MAX-1) ? '\n' : ' ');


    return 0;
}
/* shellsort:  sort v[0]...v[n-1] into increasing order */
void shellsort(int v[], int n) {
    int gap, i, j, temp;

    for (gap = n/2; gap > 0; gap /=2) 
        for (i = gap; i < n; i++)
            for (j = i-gap; j >= 0 && v[j] > v[j+gap]; j -= gap) {
                temp = v[j];
                v[j] = v[j+gap];
                v[j+gap] = temp;
            }

    return;
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