/* Exercise 1.22
 *
 * Write a program to "fold" long input lines into two or more shorter lines after
 * the last non-blank character that occures before the n-th column of input.
 * Make sure your program does something intelligent with very long lines, and if
 * there are no blanks or tabs before the specified column.
 *
 * Author: Alexandros Bantis
 * Date: 2013/05/22
 * Time: 17:05
 */

#include <stdio.h>
#include <assert.h>

#define TRUE        1
#define FALSE       0
#define SIZE       70
#define HOT        15
#define MAX      1000

int fold(char [], int, int);
int getLine(char [], int);
void clearLine(char [], int);
int strLen(char []);
int hasMore(void);

int main()
{
    int ch;
    int splitAt;
    char line[MAX] = {0};

    while (hasMore()) {
        ch = getLine(line, MAX);
        fold(line, SIZE, HOT);
        printf("%s\n", line);
    }
    return 0;
}

int firstSpaceBeforeHotZone(char s[], int len, int hot);
int firstSpaceInHotZone(char s[], int length, int hot);
int canFoldLine(char s[]);
int hasSpaceInHotZone(char s[], int len, int hot);
int isBlank(char s[], int at);
int isAlpha(char s);
int isNumeric(char s);
int inHotZone(int at, int len, int hot);
void moveToCache(char from[], int at);
int cacheFreeSpace(void);

char cache[MAX] = {0};
int more = TRUE;

int fold(char s[], int size, int hot)
{
    int len, splitAt;
    // is the length of the line less than len-hot?
    // if so, then do nothing and return current len
    len = strLen(s);
    if (len < size-hot || !canFoldLine(s))
        return len;
    
    // identify point to split the line
    if (hasSpaceInHotZone(s, size, hot))
        splitAt = firstSpaceInHotZone(s, size, hot);
    else
        splitAt = firstSpaceBeforeHotZone(s, size, hot);
    
    // copy the line to the right of the split to the cache
    // and return the new line length
    moveToCache(s, splitAt);
    return --splitAt;
}

int firstSpaceBeforeHotZone(char s[], int size, int hot)
{
    int i;
    for (i = size-hot; i > 0; i--)
        if (isBlank(s, i))
            break;
    return i;
}

int firstSpaceInHotZone(char s[], int len, int hot)
{
    assert(hasSpaceInHotZone(s, len, hot));
    
    int i;
    for (i = len-hot; i < len; i++)
        if (isBlank(s, i))
            break;
    return i;
}

int canFoldLine(char s[])
{
    int i, len;
    len = strLen(s);
    for (i = 0; i < len && !isAlpha(s[i]) && !isNumeric(s[i]); i++)
        ;
    for ( ; i < len; i++)
        if (isBlank(s, i))
            return TRUE;
    return FALSE;
}

int hasSpaceInHotZone(char s[], int size, int hot)
{
    int i;
    for (i = size-hot; i < size; i++) {
        if (isBlank(s, i))
            return TRUE;
    }
    return FALSE;
}

int isBlank(char s[], int at)
{
    int state;
    switch (s[at]) {
        case ' ': case '\t':
            state = TRUE;;
            break;
        case '-':
            if (isAlpha(s[at-1]) && isAlpha(s[at+1]))
                state = TRUE;
            else
                state = FALSE;
            break;
        default:
            state = FALSE;
            break;
    }
    return state;
}

int isAlpha(char s)
{
    int state;
    switch (s) {
        case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
        case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
        case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u':
        case 'v': case 'w': case 'x': case 'y': case 'z':
        case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
        case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
        case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U':
        case 'V': case 'W': case 'X': case 'Y': case 'Z':
            state = TRUE;
            break;
        default:
            state = FALSE;
            break;
    }
    return state;
}

int isNumeric(char s)
{
    int state;
    switch (s) {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            state = TRUE;
        default:
            state = FALSE;
    }
    return state;
}

int inHotZone(int at, int len, int hot)
{
    if (at < len && at > len - hot)
        return TRUE;
    else
        return FALSE;
}

void moveToCache(char from[], int at)
{
    int i, j, len;

    len = strLen(from);
    for (i = at+1, j = strLen(cache); i < len && cacheFreeSpace > 0; i++, j++) {
        cache[j] = from[i];
        from[i] = '\0';
        if (cache[j] == '\n')
            j--;
    }
}

int cacheFreeSpace(void)
{
    return MAX - strLen(cache);
}

int hasMore(void)
{
    if (more == FALSE && strLen(cache) == 0)
        return FALSE;
    else
        return TRUE;
}


/* getLine: gets the next line and returns the char in the first position
 * of the char array s[] */
int getLine(char s[], int size)
{
    int c;
    int i = 0;
    int len;
    if ((len = strLen(cache)) > 0) {
        for ( ; i < len; i++) {
            s[i] = cache[i];
            cache[i] = '\0';
        }
    }

    while (i < size && hasMore()) {
        c = getchar();
        if (c == EOF) { /* end of the input */
            more = FALSE;
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
    return s[0];
}

/* clearLine: sets values of char array s[] to null values */
void clearLine(char s[], int max)
{
    int i, len;

    for (i = 0; i < max; i++) {
        s[i] = '\0';
    }
}

/* strLen: returns the length of string s*/
int strLen(char s[])
{
    int i = 0;
    while (s[i] != '\0')
        i++;
    return i;
}
