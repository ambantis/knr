/**
 * @file
 * K&R Exercise 1.23
 * Write a program to remove all comments from a C program. Don't forget to
 * handle quoted strings and character constants properly. C comments do
 * not nest.
 * @date 2013/05/24
 * @version 1.0a
 */

#include <stdio.h>

#define MAX 1000 /**< maximum size of a line array */

/**
 * Boolean type
 */
typedef enum {
    false, /**< false */
    true   /**< true */
} bool;

/**
 * Indicates whether given point in the text stream is in a state of 
 */
typedef enum {
    code, /**< default state */
    quote,   /**< inside quote block */
    comment  /**< inside comment block */
} streamState;

/** Current state for the next char to be printed */
streamState state = code;

void noCommentPrint(char []);
int getLine(char [], int);
void clearLine(char [], int);

int main()
{
    int c;
    char line[MAX] = {0};
    while (true) {
        c = getLine(line, MAX);
        if (c == EOF)
            break;
        noCommentPrint(line);
        clearLine(line, MAX);
    }
    return 0;
}

/**
 * @brief Evaluates streamState at @ s[i]
 *
 * The streamState can be @a code, @a quote, or @a comment. The method
 * examines the elements just before and after to determine if state
 * should change, based upon c89 comment syntax.
 * @param[in] s Current line
 * @param[in] i Current point on line
 */
void evalStateAt(char s[], int i)
{
    int len = strLen(s);
    char before = (i > 1) ? s[i-2] : '\0';
    char last = (i > 0) ? s[i-1] : '\0';
    char curr = s[i];
    char next = (i+1 < len) ? s[i+1] : '\0'; 
    switch (state) {
        case code:
            if (curr == '/' && next == '*')
                state = comment;
            else if (curr == '\"')
                state = quote;
            break;
        case quote:
            if (last == '\"')
                state = code;
            break;
        case comment:
            if (before == '*' && last == '/')
                state = code;
            break;
        default:
            break;
    }
}

/**
 * @brief Prints current line without comments
 *
 */
void noCommentPrint(char s[])
{
    int i;
    int len = strLen(s);
    for (i = 0; i < len; i++) {
        evalStateAt(s, i);
        if (state != comment || s[i] == '\n')
            putchar(s[i]);
        else
            putchar(' ');
    }
}

/**
 * @brief Populates @a s with stdin
 *
 * @param[in,out] s The current line.
 * @param[in]   max The maximum size of the current line.
 */
int getLine(char s[], int max)
{
    int c;
    int i = 0;
    while (true) {
        c = getchar();
        if (c == EOF) {
            break;
        } else if (c == '\n') {
            s[i++] = c;
            break;
        } else {
            s[i++] = c;
        }
    }
    s[i] = '\0';
    return c;
}

/**
 * @brief Populates all elements of \a s with '\0'
 *
 * @param[in,out] s The current line.
 * @param[in]   max The maximum size of the current line.
 */
void clearLine(char s[], int max)
{
    int i, len;

    for (i = 0; i < max; i++) {
        s[i] = '\0';
    }
}

/**
 * @brief Calculates length of char array \a s.
 */
int strLen(char s[])
{
    int i = 0;
    while (s[i] != '\0')
        i++;
    return i;
}


