#include <stdio.h>

/* Exercise 1-8
 * Write a program to count blanks, tabs, and new lines
 * 
 */

int main()
{
    int c, spaces, tabs, newlines;

    spaces = tabs = newlines = 0;
    while((c = getchar()) != EOF) {
        if (c == ' ')
            ++spaces;
        else if (c == '\t')
            ++tabs;
        else if (c == '\n')
            ++newlines;
    }
    printf("num spaces = %d\n", spaces);
    printf("num tabs = %d\n", tabs);
    printf("num newlines = %d\n", newlines);
    return 0;
}
