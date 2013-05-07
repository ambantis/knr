#include <stdio.h>

/* Exercise 1-4
   Modify the temperature conversion program to print a heading
   above the table.
*/

int main()
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;   /* lower limit of temperature table */
    upper = 300; /* upper limit */
    step = 20;

    celsius = lower;
    printf("Celsius -> Fahrenheit temperature conversion\n");
    while (celsius <= upper) {
        fahr = (9.0/5) * celsius + 32;
        printf("%3.0f %6.1f\n", celsius, fahr);
        celsius += step;
        return 0;
    }
}



















