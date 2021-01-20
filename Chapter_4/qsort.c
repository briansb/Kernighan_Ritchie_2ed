#include <stdio.h>
#include <time.h>         /* for random number seed */ 
#define qsort qsort_orig  /* define stdlib qsort to qsort_orig */
#include <stdlib.h>       /* for random number generation */

#undef qsort     /* lose the original qsort */

void qsort(int v[], int lef, int right);
void swap(int v[], int i, int j);
void print_array(char arr[], int v[]);

int elements;

int main() {
    int i, r;
    int v[100];

    elements = 30;

    srand(time(NULL));   /* Call once */
    for (i = 0; i < elements; ++i) {
        r = rand() % 100;      // Returns a pseudo-random integer between 0 and 100
        v[i] = r;
    }

    print_array("Before qsort", v);
    printf("\nCalling qsort\n");  

    qsort(v,0,elements-1);

    print_array("\nAfter qsort", v);

    return 0;
}

/* qsort:  sort v[left]...v[right] into increasing order */
void qsort(int v[], int left, int right) {
    int i, last;
    
    if (left >= right)       /* do nothing if array contains fewer than two elements */
        return;
    
    swap(v, left, (left + right)/2);   /* use middle element for pivot element...see Roughgarden pg 118 */
                                       /* move partition element to v[0] */

    last = left;
    for (i = left + 1; i <= right; i++)    /* partition */
        if (v[i] < v[left])
            swap(v, ++last, i);

    swap(v, left, last);

    qsort(v, left, last-1);
    qsort(v, last+1, right);
    return;
}

/* swap:  interchange v[i] and v[j] */
void swap(int v[], int i, int j) {
    int temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
    return;
}

void print_array(char arr[], int v[]) {
    int i;
    printf("%s...", arr);
    for (i = 0; i < elements; ++i) 
        printf(" %d", v[i]);
    printf("\n");
    return;
}