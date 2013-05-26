/**
 * @file
 * K&R Exercise 1.24
 * Write a program to check a C program for rudimentary syntax errors like
 * unbalanced parentheses, brackets and braces. Don't forget about quotes,
 * both single and double, escape sequences, and comments. (This program
 * is hard if you do it in full generality.)
 * @date 2013/05/25
 * @version 1.0a
 * */

#include <stdio.h>
#include <assert.h>

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
    code,     /**< default state */
    include,  /**< an include statement */
    quote1,   /**< inside single-quote block */
    quote2,   /**< inside double-quote block */
    comment  /**< inside comment block */
} streamState;

/** Current state for the next char to be printed */
streamState state = code;

void read(char p[], int max);
bool isParen(char ch);
void extract(char s[], char p[], int max);
void add(char p[], char c, int max);
bool eval(char p[]);
bool empty(char p[]);
int dec(char p[], int i);
int inc(char p[], int i);
bool isPair(char left, char right);
void evalStateAt(char s[], int i);
bool isInclude(char s[]);
int getLine(char s[], int max);
void clearLine(char s[], int max);
int strLen(char s[]);

int main()
{
    char par[MAX] = {0};
    read(par, MAX);
    bool balanced = eval(par);
    if (balanced)
        printf("code is balanced\n");
    else
        printf("code IS NOT balanced.!\n");
    return 0;
}

/**
 * @brief Reads stdin one line at a time and then extracts
 * the paren characters: (){}[] to the @a p char array.
 * @param[out] p The char array of paren characters
 * @param[in] max The maximum size of @ p char array
 */
void read(char p[], int max)
{
    int c;
    char line[MAX] = {0};
    while (true) {
        c = getLine(line, MAX);
        if (c == EOF)
            break;
        extract(line, p, MAX);
        clearLine(line, MAX);
    }
}

/**
 * @brief Evaluates whether @a ch is a paren: (){}[].
 * @param[in] ch The character to be evaluated.
 * @return Boolean true if the character is a paren: (){}[]
 */
bool isParen(char ch)
{
    switch (ch) {
        case '(': case ')': case '[': case ']': case '{': case '}':
            return true;
            break;
        case '<': case '>':
            if (state == include)
                return true;
            break;
        default:
            break;
    }
    return false;
}

/**
 * @brief Extracts paren characters from current line of input.
 * @param[in] s The line of input to be read.
 * @param[out] p The location for extracted parens to be placed.
 * @param[in] max The maximum size of the @a p char array.
 *  */
void extract(char s[], char p[], int max)
{
    int c, i;
    int len = strLen(s);
    for (i = 0; i < len; i++) {
        c = s[i];
        evalStateAt(s, i);
        if ((state == code || state == include) && isParen(c))
            add(p, c, max);
    }
}

/**
 * @brief Adds a char to array @a p
 * @param[out] p Char array of parens
 * @param[in] c The char to be added
 * @param[in] max The maximum size of array @a p
 */
void add(char p[], char c, int max)
{
    int len = strLen(p);
    assert(len < max);
    p[len] = c;
}

/**
 * @brief Evaluates the char array of parens.
 *
 * The function searches for paren pairs; each pair it finds is removed.
 * The function uses an algorithm of dividing up the the char array into
 * left and right.
 * @param[in,out] p The char array of parens: ()[]{}
 */
bool eval(char p[])
{
    int left = 0;
    int right = 1;
    int len = strLen(p);
    int split = 1;
    while (true) {
        left = dec(p, split);
        right = inc(p, split);
        if (empty(p))
            return true;
        else if (split == len)
            return false;
        else if (isPair(p[left], p[right])) {
            p[left] = p[right] = ' ';
            split++;
        } else
            split++;
    }
    return false;
}

/**
 * @brief Evalutes whether the char array @a p contains any parens (non-spaces)
 * @return True if char array @a p contains only the space character.
 */
bool empty(char p[])
{
    int i;
    int len = strLen(p);
    for (i = 0; i < len; i++)
        if (p[i] != ' ')
            return false;
    return true;
}

/**
 * @brief Used by the eval function to find the next character to evaluate in the
 * left side of the paren char array.
 * @param [in] p The paren char array.
 * @param [in] i The split point.
 * @return next point of left side of paren char array to evaluate
 */
int dec(char p[], int i)
{
        i--;
    while(p[i] == ' ' && i > 0)
        i--;
    return i;
}

/**
 * @brief Used by the eval function to find the next character to evaluate in the
 * right side of the paren char array.
 * @param [in] p The paren char array.
 * @param [in] i The split point.
 * @return next point of the right side of paren char array to evaluate
 */
int inc(char p[], int i)
{
    while(p[i] == ' ')
        i++;
    return i;
}

/**
 * @brief Evalutes whether two chars are matching parens.
 * @param[in] left
 * @param[in] right
 * @return
 */
bool isPair(char left, char right)
{
    if (left == '(' && right == ')')
        return true;
    else if (left == '{' && right == '}')
        return true;
    else if (left == '[' && right == ']')
        return true;
    else
        return false;
}

/**
 * @brief Evaluates streamState at @ s[i]
 *
 * The streamState can be @a code, @2 quote1, @a quote2, or @a
 * comment. The method examines the elements just before and after to
 * determine if state should change, based upon c89 comment syntax.
 * @param[in] s Current line
 * @param[in] i Current point on line
 */
void evalStateAt(char s[], int i)
{
    int len = strLen(s);
    char iMinus4 = (i > 3) ? s[i-4] : '\0';
    char iMinus3 = (i > 2) ? s[i-3] : '\0';
    char iMinus2 = (i > 1) ? s[i-2] : '\0';
    char iMinus1 = (i > 0) ? s[i-1] : '\0';
    char iZed = s[i];
    char iPlus1 = (i+1 < len) ? s[i+1] : '\0';
    char iPlus2 = (i+2 < len) ? s[i+2] : '\0';
    char iPlus3 = (i+3 < len) ? s[i+3] : '\0';
    switch (state) {
        case code:
            if (iZed == '/' && iPlus1 == '*')
                state = comment;
            else if ((iZed == '\'' && iPlus1 == '\\' && iPlus3 == '\'') ||
                     (iZed == '\'' && iPlus2 == '\''))
                state = quote1;
            else if (iZed == '\"')
                state = quote2;
            else if (i == 0 && iZed == '#' && isInclude(s))
                state = include;
            break;
        case include:
            if (iZed == '\n')
                state = code;
            break;
        case quote1:
            if ((iMinus4 == '\'' && iMinus3 == '\\' && iMinus1 == '\'') ||
                (iMinus3 == '\'' && iMinus1 == '\''))
                state = code;
            break;
        case quote2:
            if (iMinus1 == '\"')
                state = code;
            break;
        case comment:
            if (iMinus2 == '*' && iMinus1 == '/')
                state = code;
            break;
        default:
            break;
    }
}

/**
 * @brief Evalutes whether beginning of line is a valid include statement.
 *
 * @param s[in] Line of code
 * @param boolean true if beginning of line matches the string "#include"
 */
bool isInclude(char s[])
{
    int i;
    const char includeStmt[] = "#include";
    int inclLen = 8;
    int len = strLen(s);
    if (len < inclLen)
        return false;
    for (i = 0; i < inclLen; i++)
        if (s[i] != includeStmt[i])
            return false;
    return true;
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
