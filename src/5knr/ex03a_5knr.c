/**
 * @file
 * K&R Exercise 5.3
 * Write a pointer version of the function strcat that we showed in
 * Chapter 2: strcat(s,t) copies the string t to the end of s
 * @date 2013/06/03
 * @version 1.0a
 */

#include <stdio.h>

void strCat(char *s, char *t);

int main()
{
    char hello[15] = "Hello ";
    char world[] = "World!";
    printf("source: %s\n", hello);
    printf("extra: %s\n", world);
    strCat(hello, world);
    printf("new source: %s\n", hello);
    return 0;
}

void strCat(char *s, char *t)
{
    while (*s != '\0')
        s++;
    while (*t != '\0') {
        *s = *t;
        s++;
        t++;
    }
}
