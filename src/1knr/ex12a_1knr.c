#include <stdio.h>

#define IN        1  /* inside a word */
#define OUT       0  /* outside a word */
#define NEWLINE '\n'
#define SPACE   ' '

/* Exercise 1-12
 *
 * Write a program that prints ints input one word per line
 *
 * Author: Alexandros Bantis
 * Date: 5/7/13
 * Time: 22:50
 */

int main()
{
    int c;
    while ((c = getchar()) != EOF) 
    {
        if (c == SPACE) 
        {
            putchar(NEWLINE);
            while ((c = getchar() != EOF && c == SPACE)) 
            {
                ;
            }
        } else {
            putchar(c);
        }
    }
    return 0;
}

