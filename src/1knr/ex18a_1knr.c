/* Exercise 1-18
 *
 * Write a program to remove trailing blanks and tabs from each line of input,
 * and to delete entirely blank lines
 *
 * Author: Alexandros Bantis
 * Date: 2013/05/16
 * Time: 18:29
 */

#include <stdio.h>

#define MAX_LINE 1000
#define TRUE 1

void clear_line(char [], int);
int get_line(char [], int);
void trim_line(char [], int);

int main()
{
    char line[MAX_LINE] = {0};
    int lastChar = 1;
    while (lastChar != EOF) {
        lastChar = get_line(line, MAX_LINE);
        if (lastChar == '\n')
            ;
        else
            printf("%s\n", line);
        clear_line(line, MAX_LINE);
    }
    return 0;
}

/* get_line: gets the next line and returns the char in the first position
 * of the char array s[] */
int get_line(char s[], int ceiling)
{
    int c;
    int i = 0;
    while (i < ceiling) {
        c = getchar();
        if (c == EOF) { /* end of the input */
            break;
        } else if (c == '\n' && i == 0) { /* an empty line */
            break;
        } else if (c == '\n') { /* end of the line */
            c = s[i-1];
            break;
        } else {
            s[i] = c;
        }
        i++;
    }
    s[i] = '\0';
    trim_line(s, ceiling);
    return c;
}

/* clear_line: sets values of char array s[] to null values */
void clear_line(char s[], int len)
{
    int i;
    for (i = 0; i < len; i++) {
        s[i] = '\0';
    }
}

/* trim_line: removes trailing blanks and tabs from a line */
void trim_line(char s[], int len)
{
    int i = len;
    while (i >= 0 && (s[i] == ' ' || s[i] == '\t' || s[i] == '\0' )) {
        s[i--] = '\0';
    }
}
