/**
 * @file
 * K&R Exercise 5.2
 * Write getfloat, the floating-point analog of getint. What type
 * does getfloat return as its function value
 * @date 2013/06/02
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


int getFloat(float *);

int main()
{
    float next;
    float n = 0;
    float *pn = &n;
    while (true) {
        next = getFloat(pn);
        if (next == 0)
            break;
        printf("%f\n", *pn);
    }
    return 0;
}

int getFloat(float *pn)
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
    if (c == '.') {
        c = getc(stdin);
        int decimal = 0;
        int i;
        for (i = 10 ; isdigit(c) && c != EOF; c = getc(stdin), i *= 10) {
            decimal = (decimal * 10) + (c - '0'); 
        }
        if (decimal > 0)
            *pn = *pn + (decimal / i);
    }
    *pn *= sign;
    if (c != EOF) {
        ungetc(c, stdin);
        return c;
    } else {
        return 0;
    }
    
}
