#include <stdio.h>
#include <time.h>

/* for timing things */
int main()  
{

    clock_t start_t, end_t, clocks;
    int i;
    long sum = 0;
    double delta;
    start_t = clock();
    /* do computations */
    /* example */
    for (i = 0; i < 100000000; ++i) sum += i;

    
    end_t = clock();
    clocks = end_t - start_t;
    delta = (double)clocks / (double) CLOCKS_PER_SEC;
    printf("Elapsed time = %f (s)\n", delta);    

	return 0;
}