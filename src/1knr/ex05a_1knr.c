#include <stdio.h>

/*
 * Exercise 1-5
 *
 * Modify the temperature conversion program to print the table in
 * reverse order, that is, from 300 degrees to 0.
 */

int main()
{
    float celsius;
    int fahr, floor, ceiling, step;

    floor = 0;
    ceiling = 300;
    step = 20;

    printf("Fahrenheit -> celsius temperature conversion\n");
    for (fahr = ceiling; fahr >= floor; fahr = fahr - step) {
	celsius = (5.0/9) * (fahr-32);
	printf("%3d %6.1f\n", fahr, celsius);
    }
    return 0;
}
