#include <stdio.h>
#include <string.h> /* for strcmp */
#include <ctype.h>  /* for tolower */
#include <stdlib.h>

#define MAXLEN 1000     /* max length of any input line */
#define MAXLINES 5000   /* max # lines to be sorted */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort_bb(void *lineptr[], int left, int right, 
            int (*comp)(void *, void *));
int numcmp(const char *, const char *);  /* same comparison as strcmp, but on numeric grounds 
                                            meaning, the string is turned into a number */
int getline_bb(char *, int);
char *alloc(int);
char *lineptr[MAXLINES];  /* pointers to text lines */

int string_compare(char *str1, char *str2);
int number_compare(char *, char *);
int read_command_line(int argc, char *argv[]);
int numeric = 0;
int reverse = 0;
int fold = 0;
int directory = 0;
void copytwostrings(char *str1, char *str2, char *str1_result, char * str2_result);
void remove_special(char *str, char *strd);

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

/* string_compare:  wrapper for strcmp */
int string_compare(char *str1, char *str2) {
    char str1_directory[MAXLEN], str2_directory[MAXLEN];
    char str1_fold[MAXLEN], str2_fold[MAXLEN];
    int i;
    
    if (directory) {
        /* remove weird characters */
        remove_special(str1, str1_directory);
        remove_special(str2, str2_directory);
    } else {
        copytwostrings(str1, str2, str1_directory, str2_directory);
    }
    
    if (fold) {
        i = 0;
        while (str1_fold[i++] =  tolower(str1_directory[i]));
        i = 0;
        while (str2_fold[i++] =  tolower(str2_directory[i]));
    } else {
        copytwostrings(str1_directory, str2_directory, str1_fold, str2_fold);
    }
    
    if (reverse) {
        return strcmp(str2_fold, str1_fold);
    } else {
        return strcmp(str1_fold, str2_fold);
    }
}
/* removes special characters */
void remove_special(char *str, char *strd) {
    int i = 0;
    int j = 0;
    char c;
    while (str[i]) {
        c = str[i];
        if ((c == 32) || 
            (c >= 48 && c <= 57) || 
            (c >= 65 & c <= 90) || 
            (c >= 97 & c <= 122)) {
            strd[j] = str[i];
            j++;
        }
        i++;
    }
    strd[j] = '\0';

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
                case 'd':
                    directory = 1;
                    break;
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
void copytwostrings(char *str1, char *str2, char *str1_result, char * str2_result) {
    int i = 0;
    while (str1_result[i++] =  str1[i]);

    i = 0;
    while (str2_result[i++] =  str2[i]);   
}