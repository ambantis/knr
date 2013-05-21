/* Exercise 1-20
 *
 * Write a program detab that replaces tabs in the input with the proper number
 * of blanks to space to the next tab stop. Assume a fixed set of tab stops, say
 * every n columns. Should n be a variable or a symbolic parameter?
 *
 * Author: Alexandros Bantis
 * Date: 2013/05/20
 * Time: 17:07
 */

#include <stdio.h>

#define TAB         8
#define LINE       80
#define MAX_LINE 1000
#define TRUE 1

int detab(char [], int, int);
int replace_tab(char [], int, int, int);
int get_line(char [], int);
void clear_line(char []);
int str_len(char []);

int main()
{
    int lastChar;  /* line length */
    char line[MAX_LINE] = {0};
    
    while (TRUE) {
        lastChar = get_line(line, MAX_LINE);
        if (lastChar == EOF)
            break;
        detab(line, TAB, MAX_LINE);
        printf("%s\n", line);
        clear_line(line);
    }
    return 0;
}

/* detab: takes as input a string s[] and tab width, and returns new size */
/*        of the char array */
int detab(char s[], int tab, int max)
{
    int i, j, count, point, len;

    len = str_len(s);
    i = 0;
    while (i < len) {
        if (s[i] == '\t') {
            point = i+1;
            count = tab - (point % tab);
            i = replace_tab(s, i, count, max);
        } else {
            i++;
        }
    }
    return i;
}

/* replace_tab: inserts space characters within a char array  */
/*              returns adjusted point of insertion           */
int replace_tab(char s[], int at, int count, int max)
{
    int i, len;

    len = str_len(s);
    
    /* test for valid arguments                                         */
    if (len + count-1 > max)  /* check if s[] has enough space for      */
        return 0;             /* insertion                              */
    if (s[at] != '\t')        /* check for valid insertion point that   */
        return 0;             /* contains a tab character               */
    if (count < 0)            /* check that we are inserting a valid    */
        return 0;             /* number of spaces, greater than 1       */

    s[at] = ' ';              /* replace tab with a space increment at  */
    --count;
    for (i = len; i > at; i--) { /* expand s[] by count to point */
        s[i+count] = s[i];
    }
    for (i = at; i <= at+count; i++) {
        s[i] = ' ';
    }
    return i;
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

/* str_len: returns the length of string s*/
int str_len(char s[])
{
    int i;
    for (i = 0; s[i] != '\0'; i++)
        ;
    return --i;
}
