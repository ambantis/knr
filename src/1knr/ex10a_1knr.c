#include <stdio.h>

/* Exercise 1-10
 *
 * Write a program to copy its input to its output, replacing each tab by \t,
 * each backspace by \b, and each backslash by \\. This makes tabs and backspaces
 * visible in an unambiguous way.
 *
 * Author: Alexandros Bantis
 * Date: 5/6/13
 * Time: 7:50 PM
 */

int main()
{
    int c;

    while((c = getchar() != EOF)) {
        switch (c) {
        case '\b':
            printf("\b");
            break;
        case '\t':
            printf("\t");
            break;
        case '\\':
            printf("\\");
            break;
        default:
            putchar(c);
            break;
        }
    }
    return 0;
}
