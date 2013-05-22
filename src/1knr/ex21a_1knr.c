/* Exercise 1.21
 *
 * Write a program entab that replaces strings of blanks by the minimum number
 * of tabs and blanks to achieve the same spacing. Use the same tab stops as
 * for detab. When either a tab or a single blank would suffice for a tab
 * stop, which should be given preference?
 *
 * Author: Alexandros Bantis
 * Date: 2013/05/21
 * Time: 11:35
 */

#include <stdio.h>
#include <assert.h>

#define TRUE        1
#define FALSE       0
#define TAB         4
#define LINE       80
#define MAX_LINE 1000

int entab(char [], int, int);
void replaceTab(char [], int, int, int);
int reachesNextTab(int, int, int);
int nextTab(int, int);
int getLine(char [], int);
void clearLine(char [], int);
int strLen(char []);

int main()
{
int lastChar;  /* line length */
    char line[MAX_LINE];
    clearLine(line, MAX_LINE);
    
    while (TRUE) {
        lastChar = getLine(line, MAX_LINE);
        if (lastChar == EOF)
            break;
        entab(line, TAB, MAX_LINE);
        printf("%s\n", line);
        clearLine(line, MAX_LINE);
    }
    return 0;
}

/* entab: takes as input a string s[] and tab width, and returns new size */
/*        of the char array */
int entab(char s[], int tab, int max)
{
    int i, j, count, point, len, spaces, nextTabStop;

    len = strLen(s);
    i = spaces = 0;
    point = i+1;
    while (i < len) {
        switch (s[i]) {
            case '\t':
                i++;
                point = nextTab(point, tab);
                break;
            case ' ':
                while (s[i] == ' ') {
                    i++;
                    point++;
                    spaces++;
                }
                if (reachesNextTab(point-spaces, spaces, tab)) {
                    i -= spaces;
                    point -= spaces;
                    count = nextTab(point, tab) - point;
                    replaceTab(s, i, count, max);
                    i++;
                    point += count;
                    len -= count+1;
                }
                spaces = 0;
                break;
            default:
                i++;
                point++;
                break;
        }
    }
    return i;
}

/* replaceTab: inserts space characters within a char array  */
void replaceTab(char s[], int at, int count, int max)
{
    int i, len, validArgs;

    len = strLen(s);
    validArgs = TRUE;

    
    /* test for valid arguments                                         */
    for (i = at; i < at+count+1; i++)
        if (s[at] != ' ') {
            validArgs = FALSE;
            printf("error: replace_tab args `at` & count\n.");
        }
    assert(validArgs == TRUE);
    
    s[at++] = '\t';
    for (i = at; i < len+count; i++) { /* expand s[] by count to point */
        s[i] = s[i+count];
    }
    return;
}

int reachesNextTab(int point, int spaces, int tab)
{
    if (spaces > 1 && point+spaces >= nextTab(point, tab))
        return TRUE;
    else
        return FALSE;
}

/*  */
int nextTab(int point, int tab)
{
    return ((point / tab) + 1) * tab; 
}


/* getLine: gets the next line and returns the char in the first position
 * of the char array s[] */
int getLine(char s[], int ceiling)
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
void clearLine(char s[], int max)
{
    int i, len;

    for (i = 0; i < max; i++) {
        s[i] = '\0';
    }
}

/* str_len: returns the length of string s*/
int strLen(char s[])
{
    int i;
    for (i = 0; s[i] != '\0'; i++)
        ;
    return --i;
}
