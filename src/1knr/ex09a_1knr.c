#include <stdio.h>

/* Exercise 1-9
 * Write a program to copy its input to its output, replacing each string of
 * one or more blanks by a single blank.
 *
 * User: Alexandros Bantis
 * Date: 5/6/13
 * Time: 7:10 PM
 */

int main(void)
{
    int c;

    while((c = getchar()) != EOF) {
        if (c == ' ') {
            putchar(c);
            while((c = getchar()) == ' ') {
                ;
            }
        }
        putchar(c);
    }
    return 0;
}
