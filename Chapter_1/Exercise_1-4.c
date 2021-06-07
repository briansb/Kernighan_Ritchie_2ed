#include <stdio.h>

/* print Celsius-Fahrenheit table */
int main() {

	// floating point version
	float fahr, celsius;
	int lower, upper, step;

	// assignment statements
	lower = -20;  /* lower limit of temperature table */
	upper = 120;  /* upper limit */
	step = 10;    /* step size */

	printf("Celsius to Fahrenheit\n");
	celsius = lower;
	while (celsius <= upper) {
		fahr = (9.0 / 5.0 * celsius) + 32.0;
		printf("%3.0f  %6.1f\n", celsius, fahr);
		celsius = celsius + step;
	}

}
