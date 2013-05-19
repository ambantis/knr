/* Exercise 1-19
 *
 * Write a function reverse(s) that reverses the character string s.
 * Use it to write a program that reverses its input a line at a time.
 *
 * Author: Alexandros Bantis
 * Date: 2013/05/19
 * Time: 00:04
 */

#include <stdio.h>

#define MAX_LINE 1000
#define TRUE 1

void reverse(char []);
int str_len(char []);
void clear_line(char []);
int get_line(char [], int);

int main()
{
    char line[MAX_LINE] = {0};
    int lastChar;
    while (TRUE) {
        lastChar = get_line(line, MAX_LINE);
        if (lastChar == EOF)
            break;
        printf("\noriginal line:\n%s", line);
        reverse(line);
        reverse(line);
        printf("\ndouble reversed line:\n%s\n", line);
        clear_line(line);
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
    return c;
}

/* clear_line: sets values of char array s[] to null values */
void clear_line(char s[])
{
    int i, len;

    len = str_len(s);
    for (i = 0; i < len; i++) {
        s[i] = '\0';
    }
}


void reverse(char s[])
{
    int i, j, tmp, len;

    len = str_len(s);
    for(i = 0, j = len-1; i < j; i++, j--) {
        tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
}

int str_len(char s[])
{
    int i;
    for (i = 0; s[i] != '\0'; i++)
        ;
    return --i;
}
