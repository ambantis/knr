/* Exercise 1.22
 *
 * Write a program to "fold" long input lines into two or more shorter
 * lines after the last non-blank character that occurs before the
 * n-th column of input.  Make sure your program does something
 * intelligent with very long lines, and if there are no blanks or
 * tabs before the specified column.
 *
 * Author: Alexandros Bantis
 * Date: 2013/05/22
 * Time: 17:05
 */

#include <stdio.h>
#include <assert.h>

#define TRUE        1     /**< boolean \a true */
#define FALSE       0     /**< boolean \a false */
#define SIZE       70     /**< maximum size of folded line output */
#define HOT        15     /**< size of hot zone from right of line size */
#define MAX      1000     /**< maximum size of a line array */

void fold(char [], int, int);
void getLine(char [], int);
void clearLine(char [], int);
int strLen(char []);
int hasMore(void);

int main()
{
    char line[MAX] = {0}; /**<  */

    while (hasMore()) {
        getLine(line, MAX);
        if (strLen(line) > SIZE)
            fold(line, SIZE, HOT);
        printf("%s\n", line);
    }
    return 0;
}

int firstSpaceBeforeHotZone(char [], int, int);
int firstSpaceInHotZone(char [], int, int);
int canFoldLine(char []);
int hasSpaceInHotZone(char [], int, int);
int isBlank(char [], int);
int isAlpha(char);
int isNumeric(char);
int inHotZone(int, int, int);
void moveToCache(char [], int);
int cacheFreeSpace(void);

char cache[MAX] = {0}; /**< storage for characters removed from folded line */

/**
 * \brief There exists \a more characters to be processed by application.
 *
 * A value of \a TRUE, the default state, indicates that \a stdin has not
 * encountered an \a EOF. A value of FALSE, which can be set by \a getLine(),
 * indicates that there is no more text to be processed and the \a main()
 * loop can exit.
 */

int more = TRUE;

/**
 * \brief Takes a long line and separates it into smaller lines.
 *
 * If \a s[] length is greater than <em>size - hot</em>, then the array is
 * split into two parts, with the chars to the right removed and placed in
 * the cache.
 * \param[in,out] s    Current line of input
 * \param[in]     size Intended line length
 * \param[in]     hot  hotzone area on the right margin where the program
 *                     searches for a space break
 */
void fold(char s[], int size, int hot)
{
    int len = strLen(s); /**< The length of \a s */
    int splitAt; /**< The point where the char array will be folded */
    if (len < size-hot || !canFoldLine(s)) {
        moveToCache(s, 0);
    } else {
        if (hasSpaceInHotZone(s, size, hot))
            splitAt = firstSpaceInHotZone(s, size, hot);
        else
            splitAt = firstSpaceBeforeHotZone(s, size, hot);
        moveToCache(s, splitAt);
    }
}

/**
 * \brief Returns first point in hotzone of \a s that has a space.
 * \param[in,out]    s Current line
 * \param[in]     size Margin size desired for current line.
 * \param[in]      hot Distance from right margin that hotzone extends
 * \return             First point in hotzone that has a space.
*/
int firstSpaceBeforeHotZone(char s[], int size, int hot)
{
    int i;
    for (i = size-hot; i > 0; i--)
        if (isBlank(s, i))
            break;
    return i;
}

/**
 * \brief Returns first point in before hotzone of \a s that has a space.
 * \param[in,out]    s Current line
 * \param[in]     size Margin size desired for current line.
 * \param[in]      hot Distance from right margin that hotzone extends
 * \return             First point in hotzone that has a space.
*/
int firstSpaceInHotZone(char s[], int len, int hot)
{
    assert(hasSpaceInHotZone(s, len, hot));
    
    int i;
    for (i = len-hot; i < len; i++)
        if (isBlank(s, i))
            break;
    return i;
}

/**
 * \brief Returns TRUE/FALSE whether line is foldable.
 *
 * In cases where line has not spaces that separate alphanumeric text, then
 * line cannot be split.
 * \param[in] s Current line
 * \return      Returns TRUE if line is foldable, otherwise FALSE.
 */
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
/**
 * \brief Evalutes whether hotzone has a space.
 *
 * If the hotzone contains no points where line can be folded, then it is
 * necessary to explore area before hotzone for such a break point.
 * \param[in]     s Current line
 * \param[in]     size Margin size desired for current line.
 * \param[in]      hot Distance from right margin that hotzone extends
 * \return             First point in hotzone that has a space.
 */
int hasSpaceInHotZone(char s[], int size, int hot)
{
    int i;
    for (i = size-hot; i < size; i++) {
        if (isBlank(s, i))
            return TRUE;
    }
    return FALSE;
}

/** \brief Evalutes \a s[at] is a blank character
 *
 *  If \a s[at] is a ' ' or '\t' or a '-' with alphanumeric on either
 *  side, then it will evalute to true.
 *  \param[in]  s Current line
 *  \param     at Point on current line to be evaluated.
 *  \return       TRUE if is a blank character, otherwise FALSE
 * */
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

/**
 * \brief tests whether \a s is [a-zA-Z]
 *
 * @param[in]    s A char
 * \return         TRUE if \a s is [a-zA-Z]
 */
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

/**
 * \brief tests whether \a s is [0-9]
 *
 * @param[in]    s A char
 * \return         TRUE if \a s is [0-9]
 */
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

/**
 * \brief Evaluates whether point is in the hotzone.
 *
 * \param[in]   at   Point in \a s to be evaluted.
 * \param[in]   size Margin size desired for current line.
 * \param[in]   hot  Distance from right margin that hotzone extends
 * \return           True if \a s[at] lies within the hotzone.
 */
int inHotZone(int at, int size, int hot)
{
    if (at < size && at > size - hot)
        return TRUE;
    else
        return FALSE;
}

/**
 * \brief Moves chars to the right of \a at to the cache.
 *
 * \param[in,out]  from Char array containing the chars to be moved.
 * \param[in] in Point along \a from[] that marks the split point
 */
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

/**
 * \brief Returns amount of space \a cache has availble for write.
 */
int cacheFreeSpace(void)
{
    return MAX - strLen(cache);
}

/**
 * \brief Evaluates whether there are more chars to evalute.
 *
 *  \return FALSE if EOF is found in stdin and chace isEmpty
 */
int hasMore(void)
{
    if (more == FALSE && strLen(cache) == 0)
        return FALSE;
    else
        return TRUE;
}

/**
 * \brief Populates \a s with chars from \a cache or stdin.
 *
 * First, if there are characters in the \a cache, they are moved to
 * \a s. Then gets chars from stdin until a \a newline or EOF is
 * encountered.
 * \param[in,out] s The current line.
 * \param[in]   max The maximum size of the current line.
 */
void getLine(char s[], int max)
{
    int c;
    int i = 0;
    int len = strLen(cache);
    if (len > 0) {
        for ( ; i < len; i++) {
            s[i] = cache[i];
            cache[i] = '\0';
        }
    }

    while (i < max && hasMore()) {
        c = getchar();
        if (c == EOF) {
            more = FALSE;
            break;
        } else if (c == '\n' && i == 0) {
            break;
        } else if (c == '\n') {
            c = s[i-1];
            break;
        } else {
            s[i] = c;
        }
        i++;
    }
    s[i] = '\0';
}

/**
 * \brief Populates all elements of \a s with '\0'
 *
 * \param[in,out] s The current line.
 * \param[in]   max The maximum size of the current line.
 */
void clearLine(char s[], int max)
{
    int i, len;

    for (i = 0; i < max; i++) {
        s[i] = '\0';
    }
}

/**
 * \brief Calculates length of char array \a s.
 */
int strLen(char s[])
{
    int i = 0;
    while (s[i] != '\0')
        i++;
    return i;
}
