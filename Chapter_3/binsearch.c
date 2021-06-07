#include <stdio.h>
#define MAXELEMENTS 1000000   /* maximum size of sorted array */

/* binsearch:  find x in v[0] <= v[1] <= ...<= v[n-1] */
int binsearch(int x, int v[], int n);

int main()  
{
	int array[MAXELEMENTS];
    int n = MAXELEMENTS;
    for (int i = 0; i < n; ++i) array[i] = i + 3;
    int x = 7803;
    
    printf("%d is at index = %d\n", x, binsearch(x, array, n));
    
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