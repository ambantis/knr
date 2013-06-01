/**
 * @file
 * K&R Exercise 5.1
 * As written, getint treats a + or - not followed by a digit as a
 * valid representation of zero. Fix it to push such a character
 * back on the input.
 * @date 2013/05/31
 * @version 1.0a
 */

#include <stdio.h>
#include <ctype.h>

/**
 * Boolean type
 */
typedef enum {
    false, /**< false */
    true   /**< true */
} bool;


int getInt(int *);

int main()
{
    int next;
    int n = 0;
    int *pn = &n;
    while (true) {
        next = getInt(pn);
        if (next == 0)
            break;
        printf("%d\n", *pn);
    }
    return 0;
}

int getInt(int *pn)
{
    int c, sign;

    c = getc(stdin);
    while (isspace(c) && c != EOF)
        c = getc(stdin);
    if (c == EOF)
        return 0;
    else if (!isdigit(c) && c != '-' && c != '+') {
        ungetc(c, stdin);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '-' || c == '+')
        c = getc(stdin);
    if (!isdigit(c) && c != EOF) {
        ungetc(c, stdin);
        return 0;
    } else if (c == EOF) {
        return 0;
    }
    for (*pn = 0; isdigit(c) && c != EOF; c = getc(stdin)) {
        *pn = (*pn * 10) + (c - '0');
    }
    *pn *= sign;
    if (c != EOF) {
        ungetc(c, stdin);
        return c;
    } else {
        return 0;
    }
    
}
