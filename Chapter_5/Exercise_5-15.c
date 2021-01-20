#include <stdio.h>
#include <string.h> /* for strcmp */
#include <ctype.h>  /* for tolower */

#define MAXLINES 5000   /* max # lines to be sorted */
char *lineptr[MAXLINES];  /* pointers to text lines */


int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort_bb(void *lineptr[], int left, int right, 
            int (*comp)(void *, void *));
int numcmp(const char *, const char *);  /* same comparison as strcmp, but on numeric grounds 
                                            meaning, the string is turned into a number */

int string_compare(char *str1, char *str2);
int number_compare(char *, char *);
int read_command_line(int argc, char *argv[]);
int numeric = 0;
int reverse = 0;
int fold = 0;
char str1lower[1000];
char str2lower[1000];

/* sort input lines */
int main (int argc, char *argv[]) {
    int nlines;        /* number of input lines read */
    
    if ( read_command_line(argc, argv)) {
        printf("Incorrect command line arguments\n");
        return 1;
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort_bb((void **) lineptr, 0, nlines-1,
            (int (*)(void*,void*))(numeric ? number_compare : string_compare));
        printf("Sorted lines are:\n");
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error:  input too big to sort\n");
        return 1;
    }

}
/* qsort:  sort v[left]...v[right] into increasing order */
void qsort_bb(void *v[], int left, int right, 
            int (*comp)(void *, void *))
{
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right)      /* do nothing if array contains fewer than two elements */
        return;
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort_bb(v, left, last-1, comp);
    qsort_bb(v, last+1, right, comp);    
}

#include <stdlib.h>

/* string_compare:  wrapper for strcmp */
int string_compare(char *str1, char *str2) {
    if (fold) {
        /* convert str1 and str1 to lowercase */
        int i = 0;
        while (str1lower[i++] =  tolower(str1[i]));
        i = 0;
        while (str2lower[i++] =  tolower(str2[i]));
        if (reverse) return strcmp(str2lower, str1lower);
        else return strcmp(str1lower, str2lower);
    } else {
        /* reverse arguments if -r */
        if (reverse) return strcmp(str2, str1);
        else return strcmp(str1, str2);
    }
}
/* number_compare:  wrapper for numcmp */
int number_compare(char *str1, char *str2) {
    /* reverse arguments if -r */
    if (reverse) return numcmp(str2, str1);
    else return numcmp(str1, str2);
}
/* numcmp:  compare s1 and s2 numerically */
int numcmp(const char *s1, const char *s2) {
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

/* swap:  interchange v[i] and v[j] */
void swap(void *v[], int i, int j)
{
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

#define MAXLEN 1000     /* max length of any input line */
int getline_bb(char *, int);
char *alloc(int);

/* readlines:  read input lines */
int readlines(char *lineptr[], int maxlines)
{
        int len, nlines;
        char *p, line[MAXLEN];

        nlines = 0;
        while ((len = getline_bb(line, MAXLEN)) > 0)
            if (nlines >= maxlines || (p = malloc(len)) == NULL)
                return -1;
            else {
                line[len-1] = '\0';     /* delete newline */
                strcpy(p, line);
                lineptr[nlines++] = p;
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
int read_command_line(int argc, char *argv[]) {
    int arg_length = 0;
    char arg_value;
    while (--argc) {
        *++argv;
        if ( *argv[0] != '-') return 1;
        arg_length = strlen(*argv);
        while (--arg_length) {
            arg_value = *(   ++(*argv)     );
            switch(arg_value) {
                case 'n':
                    numeric = 1;
                    break;
                case 'r':
                    reverse = 1;
                    break;
                case 'f':
                    fold = 1;
                    break;
                // case 'd':
                //     d_flag = 1;
                //     break;
                // case 'e':
                //     e_flag = 1;
                //     break;
                default:
                    printf("Unrecognized parameter\n");
                    return 1;
            }
        }
    }

    return 0;
}
