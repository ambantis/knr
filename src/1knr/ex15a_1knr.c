/* Exercise 1-15
 *
 * Rewrite the temperature conversion program of Section 1.2 to use a function
 * for conversion
 */

#include <stdio.h>


int fahr2Celsius(int f);

int main()
{
    int fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;
    printf("Fahrenheit -> Celsius temperature conversion\n");
    while(fahr <= upper) {
        celsius = fahr2Celsius(fahr);
        printf("%d\t%d\n", fahr, celsius);
        fahr += step;
    }
}

int fahr2Celsius(int temp)
{
    return (5/9.0) * (temp - 32);
}
