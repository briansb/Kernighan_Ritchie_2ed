#include <stdio.h>

float FahrToCelsius(float fahrenheit);

/* print Fahrenheit-Celsius table 
    for fahr = 0, 20, ..., 300; floating-point version */
int main() 
{
	float fahr, celsius;
    int lower, upper, step;

    lower = 0;          /* lower limit of temperature table */
    upper = 300;        /* upper limit */
    step = 20;          /* step size */

    fahr = lower;
    while (fahr <= upper) {
        celsius = FahrToCelsius(fahr);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
}

float FahrToCelsius(float fahrenheit)
{
    return (5.0/9.0) * (fahrenheit-32.0);
}