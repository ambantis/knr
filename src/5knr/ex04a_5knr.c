/**
 * @file
 * K&R Exercise 5.4
 * Write the function strend(s,t), which returns 1 if the string t occurs
 * at the end of the string s, and zero otherwise.
 * @date 2013/06/05
 * @version 1.0a
 */

#include <stdio.h>

int strEnd(const char *s, const char *t);
int strLen(const char* s);

int main()
{
    char hello_world[] = "Hello, World!";
    char world[] = "World!";
    char jim[] = "Jim!";
    if (strEnd(hello_world, world))
        printf("string: \"%s\" is at the end of string: \"%s\"\n",
               world, hello_world);
    else
        printf("string: \"%s\" is not at the end of string \"%s\"\n",
               world, hello_world);
    

    if (strEnd(hello_world, jim))
        printf("string: \"%s\" is at the end of string: \"%s\"\n",
               jim, hello_world);
    else
        printf("string: \"%s\" is not at the end of string \"%s\"\n",
               jim, hello_world);
    
    return 0;
}

int strEnd(const char *s, const char *t)
{
    int lenS = strLen(s);
    int lenT = strLen(t);
    if (lenT > lenS)
        return 0;
    
    while (*s != '\0')
        s++;
    s--;
    int i;
    for (i = lenT-1; i >= 0; i--, s--)
        if (*s != *(t+i))
            return 0;
    
    return 1;
}

int strLen(const char* s)
{
    int len = 0;
    while (*s != '\0') {
        s++;
        len++;
    }
    return len;
}
