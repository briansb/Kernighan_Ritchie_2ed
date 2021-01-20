#include <stdio.h>
#include <ctype.h>

#define MAXLINE 100

/* raises 10 to the n power...n can be negative */
double raise_ten(int n);
/* extends atof() to handle numbers of form 123.456e78 */
double atof_extended(char s[]);
int getline_bb(char s[], int lim);
int atoi(char s[]);

/* rudimentary calculator */
int main() {
    double product, atof_extended(char[]);
    char line[MAXLINE];
    int getline_bb(char line[], int max);

    product = 1;
    while (getline_bb(line, MAXLINE) > 0)
        printf("\t%g\n", product *= atof_extended(line));
    
    return 0;
}   
/* atof:  convert string s to double */
double atof_extended(char s[])
{
    double val, power, result;
    int i, sign, atoi(char s[]), exp;
    char exponent[10];

    for (i = 0; isspace(s[i]); i++)   /* skip white space */
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    result = sign * val / power;
    /* check for scientific notation */
    int j = 0;
    if (s[i] == '\n' ) { ; } /* regular number */
    else if (s[i] == 'E' || s[i] == 'e') {
        /* load exponent */
        while (s[i++] != '\n') exponent[j++] = s[i];
        exp = atoi(exponent);
        result = result * raise_ten(exp);
    }
    else { printf("Unrecognized character\n");}

    return result;

}
/* implements 10^n */
double raise_ten(int n) {
    if (n == 0) return 1.0;
    if (n == 1) return 10;
    double power = 1.0;
    if (n > 0) {
        for ( int i = 1; i <=n; ++i) {
            power *= 10.0;
        }
    } else {
        n = n * (-1);
        for ( int i = 1; i <=n; ++i) {
            power /= 10.0;
        }
    }
    return power;
}

/* getline: get line into s, return length */
int getline_bb(char s[], int lim) {
    int c, i;
    i = 0;
    while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

int atoi(char s[]) {
    int i, n, sign;

    for (i = 0; isspace(s[i]); i++)  /* skip white space */
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')  /* skip sign */
        i++;
    for (n = 0; isdigit(s[i]); i++)
        n = 10 * n + (s[i] - '0');
    return sign * n;
}