#include <stdio.h>
#include <time.h>

#define MAXELEMENTS 1000000   /* maximum size of sorted array */

/* binsearch:  find x in v[0] <= v[1] <= ...<= v[n-1] */
int binsearch(int x, int v[], int n);
int binsearch_v2(int x, int v[], int n);
int main()  
{
	int array[MAXELEMENTS];
    int n = MAXELEMENTS;
    for (int i = 0; i < n; ++i) array[i] = i + 3;
    int x = 7803;
    
    int index;
    clock_t start_t, end_t, clocks;
    double delta;
    start_t = clock();
    index = binsearch(x,array,n);
    end_t = clock();
    clocks = end_t - start_t;
    delta = (double)clocks / (double) CLOCKS_PER_SEC;
    printf("%d is at index = %d\n", x, index);
    printf("Delta time = %f\n\n", delta);    
    /*                      */
    start_t = clock();
    index = binsearch_v2(x,array,n);
    end_t = clock();
    clocks = end_t - start_t;
    delta = (double)clocks / (double) CLOCKS_PER_SEC;
    printf("%d is at index = %d\n", x, index);
    printf("Delta time = %f\n\n", delta);

	return 0;
}
int binsearch(int x, int v[], int n) {
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low+high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else   /* found match */
            return mid;
    }
    return -1;   /* no match */
}
int binsearch_v2(int x, int v[], int n) {
    int low, high, mid;

    low = 0;
    high = n - 1;
    mid = (low+high) / 2;
    while (low <= high & x != v[mid]) {
        mid = (low+high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else 
            low = mid + 1;
    }
    if (x == v[mid]) return mid;
    else return -1; 
}
