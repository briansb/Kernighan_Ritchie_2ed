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
int field = 0;
int field_number = 0;

void copytwostrings(char *str1, char *str2, char *str1_result, char * str2_result);
void remove_special(char *str, char *strd);
int atoi_ptr(char *s);
void ExtractField(char *str1, int field_number, char *str2);

/* sort input lines */
/* commmand line arguments are -r -n -f -d -k# */
/* can combine all args except k# */
int main (int argc, char *argv[]) {
    int nlines;        /* number of input lines read */
    
    if ( read_command_line(argc, argv)) {
        printf("Incorrect command line arguments\n");
        return 1;
    }

    // printf("numeric = %d\n", numeric);
    // printf("reverse = %d\n", reverse);
    // printf("fold = %d\n", fold);
    // printf("directory = %d\n", directory);
    // printf("field = %d\n", field);
    // printf("field number = %d\n", field_number);

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
    char str1_field[MAXLEN], str2_field[MAXLEN];
    char str1_directory[MAXLEN], str2_directory[MAXLEN];
    char str1_fold[MAXLEN], str2_fold[MAXLEN];
    int i;
    
    if (field) {
        /* extract field */
        ExtractField(str1, field_number, str1_field);
        ExtractField(str2, field_number, str2_field);
    } else {
        copytwostrings(str1, str2, str1_field, str2_field);
    } 

    if (directory) {
        /* remove weird characters */
        remove_special(str1_field, str1_directory);
        remove_special(str2_field, str2_directory);
    } else {
        copytwostrings(str1_field, str2_field, str1_directory, str2_directory);
    }
    
    if (fold) {
        i = 0;
        while (str1_fold[i++] =  tolower(str1_directory[i]));
        i = 0;
        while (str2_fold[i++] =  tolower(str2_directory[i]));
    } else {
        copytwostrings(str1_directory, str2_directory, str1_fold, str2_fold);
    }
    
    //printf("Sending %s and %s to strcmp\n", str1_fold, str2_fold);
    if (reverse) {
        return strcmp(str2_fold, str1_fold);
    } else {
        return strcmp(str1_fold, str2_fold);
    }
}

/* number_compare:  wrapper for numcmp */
int number_compare(char *str1, char *str2) {
    char str1_field[MAXLEN], str2_field[MAXLEN];

    if (field) {
        /* extract field */
        ExtractField(str1, field_number, str1_field);
        ExtractField(str2, field_number, str2_field);
    } else {
        copytwostrings(str1, str2, str1_field, str2_field);
    } 

    //printf("Sending %s and %s to numcmp\n", str1_field, str2_field);
    if (reverse) return numcmp(str2_field, str1_field);
    else return numcmp(str1_field, str2_field);
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
                    break;    char str1_field[MAXLEN], str2_field[MAXLEN];
                case 'k':
                    field = 1;
                    field_number = atoi(*argv+1);  /* set the pointer to the stuff after the k */
                    arg_length = 1;  /* so loop won't read any more of this parameter */
                    break;
                default:
                    printf("Unrecognized parameter\n");
                    return 1;
            }
        }
    }

    return 0;
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
void ExtractField(char *str1, int field_number, char *str2) {
    /* assumes space is field delimiter */
    int i = 0;
    int j = 0;
    while (str1[i] == ' ') {   /* ignore leading spaces */
        i++;
    }
    while ( --field_number) {
        while (str1[i++] != ' ' && str1[i] != '\0') {
            ;
        }
    }

    if (str1[i] == '\0') { str2[0] = '\0'; return; }

    while (str1[i] != ' ' && str1[i] != '\0') {
        str2[j++] = str1[i++];
    }
    str2[j] = '\0';
    return;
}
void copytwostrings(char *str1, char *str2, char *str1_result, char * str2_result) {
    int i = 0;
    while (str1_result[i++] =  str1[i]);

    i = 0;
    while (str2_result[i++] =  str2[i]);   
}
/* atoi_ptr:  convert string to integer.  Pointer version */
int atoi_ptr(char *s) {
    int n, sign;

    for ( ; isspace(*s); s++ )  /* skip white space */
        ;
    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-')  /* skip sign */
        s++;
    for (n = 0; isdigit(*s); s++)
        n = 10 * n + (*s - '0');
    return sign * n;
}