#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAXLINES 5000   /* max # lines to be sorted */
#define MAXLEN 1000 /* max length of any input line */

int readlines(char *lineptr[], int nlines, char buffer[][MAXLEN]);
void writelines(char *lineptr[], int nlines);
int getline_bb(char *, int);
void qsort_bb(char *lineptr[], int left, int right);
void swap(char *linptr[], int left, int right);

char *lineptr[MAXLINES];    /* array of pointers to text lines */
char *alloc(int);
char buffer[MAXLINES][MAXLEN];  /* 2d array to store input */

/* sort input lines */
int main () {
    int nlines;        /* number of input lines read */
    

    /* start the timer */
    clock_t start_t, end_t, clocks;
    int i;
    long sum = 0;
    double delta;
    start_t = clock();

    /* used InputText instead of keyboard */
    if ((nlines = readlines(lineptr, MAXLINES, buffer)) >= 0) {
        qsort_bb(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);

        
        /* stop the timer */
        end_t = clock();
        clocks = end_t - start_t;
        delta = (double)clocks / (double) CLOCKS_PER_SEC;
        printf("Elapsed time = %f(s)\n", delta);   
        return 0;
    } else {
        printf("error:  input too big to sort\n");
        return 1;
    }

}
/* qsort:  sort v[left]...v[right] into increasing order */
void qsort_bb(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);

    if (left >= right)      /* do nothing if array contains fewer than two elements */
        return;
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if(strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort_bb(v, left, last-1);
    qsort_bb(v, last+1, right);    
}
/* swap:  interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
/* readlines:  read input lines */
int readlines(char *lineptr[], int maxlines, char buffer[][MAXLEN])
{
    int len, nlines, index;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = getline_bb(line, MAXLEN)) > 0) {
        for (index = 0; index<len-1; index++) {
            buffer[nlines][index] = line[index]; }

        lineptr[nlines] = buffer[nlines];
        nlines++;
    }

    return nlines;
}
/* writelines:  write output lines */
void writelines(char *lineptr[], int nlines)
{
    int i;
    
    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}
/* get_line:  read a line into s, return length */
int getline_bb(char s[], int lim)
{
    int c, i;

    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}