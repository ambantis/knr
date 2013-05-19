/* Exercise 1-17
 *
 * Write a program to print all input lines that are longer than
 * 80 characters
 *
 * Author: Alexandros Bantis
 * Date: 2013/05/16
 * Time 18:04
 */

#include <stdio.h>

#define MAXLINE 1000
#define TRUE 1

int get_line(char [], int);
void clear_line(char [], int);

int main()
{
    int len;  /* current line length */
    char line[MAXLINE];

    len = 0;
    while (TRUE) {
        clear_line(line, MAXLINE);
        len = get_line(line, MAXLINE);
        if (len = 0)
            break;
        else if (len > 80)
            printf("%s\n", line);
    }
    return 0;
}

/* get_line: gets the next line */
int get_line(char s[], int ceiling)
{
    int c;
    int i = 0;
    while (TRUE) {
        if (++i == ceiling)
            break;
        c = getchar();
        if (c == EOF || c == '\n')
            break;
        else
            s[i] = c;
    }
    s[i] = '\0';
    return --i;
}

/* clear_line: sets values of char array s[] to null values */
void clear_line(char s[], int len)
{
    int i;
    for (i = 0; i < len; i++) {
        s[i] = '\0';
    }
}
