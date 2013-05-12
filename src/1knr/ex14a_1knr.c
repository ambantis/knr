/* Exercise 1-14
 *
 * Write a program to print a histogram of the frequencies of different
 * characters in its input.
 *
 * Author: Alexandros Bantis
 * Date: 2013/05/11
 * Time: 23:23
 */

#include <stdio.h>

#define NUM_CHARS 127
#define TRUE  1
#define FALSE 0

int chars[NUM_CHARS+1] = {0};

void populateChars();
void printHistogram();

int main()
{
    populateChars();
    printHistogram();
}

void populateChars()
{
    int c;
    while(TRUE) {
        c = getchar();
        if (c == EOF)
            return;
        chars[c] += 1;
    }
}

void printHistogram()
{
    int i, j;
    /* print header */
    printf("\nHISTOGRAM OF CHARACTER FREQUENCY COUNT FOR INPUT\n\n");

    /* print body */
    for (i = 0; i < NUM_CHARS; i++) {
        if (chars[i] > 0) {
            printf(" %c - ", i);
            for (j = 0; j < chars[i]; j++) {
                putchar('x');
            }
            printf(" %d\n", chars[i]);
        }
    }
}
