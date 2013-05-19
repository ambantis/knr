/* Exercise 1-16
 *
 * Revise the main routine of the longest-line program so it will correctly
 * print the length of arbitrary long input lines, as much as possible
 * of the text
 *
 * Author: Alexandros Bantis
 * Date: 2013/05/16
 * Time: 14:58
 */

#include <stdio.h>

#define MAXLINE 1000 /* maximum input line length */
#define TRUE 1

int get_line(char line[], int maxline);
void copy(char to[], char from[]);

int main()
{
    int len;  /* current line length */
    int max;  /* max length seen so far */
    char line[MAXLINE];    /* current input line */
    char longest[MAXLINE]; /* longest saved here */

    max = 0;
    while (TRUE) {
        len = get_line(line, MAXLINE);
        if (len == 0)
            break;
        else if (len > max) {
            max = len;
            copy(longest, line);
        }
    }
    if (max > 0) /* there was a line */
        printf("%s", longest);
    return 0;
}

/* get_line: read a line into s, return length */
int get_line(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim && (c = getchar())!= EOF && c!='\n'; i++)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/* copy: copy 'from' into 'to'; assume 'to' is big enough */
void copy(char to[], char from[])
{
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}
