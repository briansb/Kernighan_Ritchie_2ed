#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINELENGTH 100

int fgetline(char *line, int max, FILE *fin);
char *fgets(char *s, int n, FILE *iop);

int main(int argc, char *argv[]) {
    FILE *fp1, *fp2;
    char line1[MAXLINELENGTH], line2[MAXLINELENGTH];

    if (argc != 3) {
        fprintf(stderr, "Wrong number of parameters\n");
        exit(1);
    }
    if (( fp1 = fopen(*++argv, "r")) == NULL) {
        fprintf(stderr, "Can not open %s\n", *argv);
        exit(1);
    }
    if (( fp2 = fopen(*++argv, "r")) == NULL) {
        fprintf(stderr, "Can not open %s\n", *argv);
        exit(1);
    }

    /* test */
    int count1, count2, condition;
    while ((count1 = fgetline(line1, MAXLINELENGTH, fp1)) != 0 && (count2 = fgetline(line2, MAXLINELENGTH, fp2)) != 0) {
        if ((condition = strcmp(line1, line2)) != 0) {
            printf("%s ... %s\n", line1, line2);
            exit(0);
        }
    }
    if (count1 != 0) {
        printf("%s\n", line1);
    } else if (count2 != 0) {
        printf("%s\n", line2);
    }


    return 0;
}


/* fgetline:  read a line from fin, return length */
int fgetline(char *line, int max, FILE *fin) {
    if (fgets(line, max, fin) == NULL)
        return 0;
    else
        return strlen(line);
}
/* fgets:  get at most n chars from iop */
char *fgets(char *s, int n, FILE *iop) {
    register int c;
    register char *cs;

    cs = s;
    while (--n > 0 && (c = getc(iop)) != EOF)
        if ((*cs++ = c) == '\n')
            break;
    *cs = '\0';
    return (c == EOF && cs == s) ? NULL : s;
}