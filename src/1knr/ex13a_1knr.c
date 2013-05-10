/* Exercise 1-13
 * 
 * Write a program to print a histogram of the lengths of words in its input.
 * It is easy to draw the histogram with the bars horizontal; a vertical
 * orientation is more challenging.
 *
 * Author: Alexandros Bantis
 * Date: 2013/05/08
 * Time: 23:03
 */ 

#include <stdio.h>

#define MAX_WORD_SIZE    20
#define HISTOGRAM_HEIGHT 30
#define TRUE  1
#define FALSE 0

int wordCount[MAX_WORD_SIZE+1] = {0};
int row[MAX_WORD_SIZE+1] = {0};

int getWordLength();
void updateHistogram(int len);
void printHistogram();

int main()
{
    int length;

    while(TRUE) {
        length = getWordLength();
        if (length == EOF) {
            updateHistogram(-length);
            printHistogram();
            break;
        } else {
            updateHistogram(length);
        }
    }
}

/* getWordLength(): returns */
int getWordLength()
{
    int c, charCount;

    charCount = 0;
    while(TRUE) {
        c = getchar();
        switch (c) {
            case EOF:
                return EOF;
                break;
            case ' ': case '-': case '\t': case '\n':
                return charCount;
                break;
            case '.': case ',': case ';': case ':': case '?': case '!':
            case '(': case ')': case '[': case ']': case '{': case '}':
            case '@': case '#': case '$': case '%': case '^': case '*': case '+':
            case '\"': case '/': case '~': case '`': case '<': case '>':
                break;
            default:
                charCount++;
                break;
        }
    }
}

/* updateHistogram(int len): increments wordCount[] at len  */
void updateHistogram(int len) {
    if (len < 1) {
        ;
    } else if (len < MAX_WORD_SIZE) {
        wordCount[len] += 1;
    } else {
        wordCount[MAX_WORD_SIZE] += 1;
    }
}

/* printHistogram(): prints out the histogram */
void printHistogram() {
    int i, j, count;
    
    /* print header */
    printf("\nHISTOGRAM OF WORD FREQUENCY COUNT FOR INPUT:\n\n");
    
    /* print count if it exceeds histogram height */
    printf("   ");
    for (i = 1; i < MAX_WORD_SIZE; i++) {
        count = wordCount[i];
        (count > HISTOGRAM_HEIGHT) ? printf("%d ", count) : printf("   ");
    }
    putchar('\n');

    /* print body */
    for (i = HISTOGRAM_HEIGHT; i > 0; i--) {
        printf("%2d ", i);
        for (j = 1; j < MAX_WORD_SIZE+1; j++) {
            (i <= wordCount[j]) ? printf(" X ") : printf("   ");
        }
        putchar('\n');
    }

    /* print footer */
    printf("   -----------------------------------------------------------\n");
    printf("   01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20+\n\n");
}
