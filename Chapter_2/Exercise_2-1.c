#include <stdio.h>
#include <limits.h>
#include <locale.h>
#include <bits/wordsize.h>
#include <float.h>
#include <math.h>

signed char SignedChar_MinMax[2];
void SignedChar_Range(signed char SignedChar_MinMax[]);
unsigned char UnsignedChar_MinMax[2];
void UnsignedChar_Range(unsigned char UnsignedChar_MinMax[]);
signed short int SignedShortInt_MinMax[2];
void SignedShortInt_Range(signed short int SignedShortInt_MinMax[]);
unsigned short int UnsignedShortInt_MinMax[2];
void UnsignedShortInt_Range(unsigned short int UnsignedShortInt_MinMax[]);
signed int SignedInt_MinMax[2];
void SignedInt_Range(signed int SignedInt_MinMax[]);
unsigned int UnSignedInt_MinMax[2];
void UnSignedInt_Range(unsigned int UnSignedInt_MinMax[]);
signed long int SignedLongInt_MinMax[2];
void SignedLongInt_Range(signed long int SignedLongInt_MinMax[]);
unsigned long int UnSignedLongInt_MinMax[2];
void UnSignedLongInt_Range(unsigned long int UnSignedLongInt_MinMax[]);
signed long long int SignedLongLongInt_MinMax[2];
void SignedLongLongInt_Range(signed long long int SignedLongLongInt_MinMax[]);
unsigned long long int UnSignedLongLongInt_MinMax[2];
void UnSignedLongLongInt_Range(unsigned long long int UnSignedLongLongInt_MinMax[]);
char Char_MinMax[2];
void Char_Range(char Char_MinMax[]);
short Short_MinMax[2];
void Short_Range(short Short_MinMax[]);
int Int_MinMax[2];
void Int_Range(int Int_MinMax[]);
long Long_MinMax[2];
void Long_Range(long Long_MinMax[]);
unsigned Unsigned_MinMax[2];
void Unsigned_Range(unsigned Unsigned_MinMax[]);


/* floating point values */
float Float_MinMax[2];
void Float_Range(float Float_MinMax[]);
double Double_MinMax[2];
void Double_Range(double Double_MinMax[]);
long double LongDouble_MinMax[2];
void LongDouble_Range(long double LongDouble_MinMax[]);


int main() {
/* Excellent reference article with format specifiers */
/*  https://en.wikipedia.org/wiki/C_data_types */

/* format characters */
/* https://www.cplusplus.com/reference/cstdio/printf/ */

    setlocale(LC_NUMERIC, "");  /* for printing commas.  Also use %'d as format specifier */

/* These assume 8-bit `char's, 16-bit `short int's, and 32-bit `int's and `long int's.  */
    printf("These bit length values are from /usr/include/limits.h and /usr/include/x86_64-linux-gnu/bits/wordsize.h\n");
    printf("They are for this machine only.\n");
    printf("\tMax length of multibyte character = %d bits\n", MB_LEN_MAX);
    printf("\tNumber of bits in 'char' = %d\n", CHAR_BIT);
    printf("\tNumber of bits in a word = %d\n\n", __WORDSIZE);
/*  Min and max */
    printf("These range values come from limits.h\n");
    printf("\tMin and max values of 'signed char' = %d and %d\n", SCHAR_MIN, SCHAR_MAX);
    printf("\tMin and max values of 'unsigned char' = %u and %u\n", 0, UCHAR_MAX);
    printf("\tMin and max values of 'signed short int' = %d and %d\n", SHRT_MIN, SHRT_MAX);
    printf("\tMin and max values of 'unsigned short int' = %u and %u\n", 0, USHRT_MAX);
    printf("\tMin and max values of 'signed int' = %'d and %'d\n", INT_MIN, INT_MAX);
    printf("\tMin and max values of 'unsigned int' = %'u and %'u\n", 0, UINT_MAX);
    printf("\tMin and max values of 'signed long int' = %'ld and %'ld\n", LONG_MIN, LONG_MAX);
    printf("\tMin and max values of 'unsigned long int' = %'u and %'lu\n", 0, ULONG_MAX);
    printf("\tMin and max values of 'signed long long int' = %'lld and %'lld\n", LLONG_MIN, LLONG_MAX);
    printf("\tMin and max values of 'unsigned long long int' = %'u and %'llu\n\n", 0, ULLONG_MAX);

/*  Determine by computation */
    printf("These whole number range values come from computation:\n");
    SignedChar_Range(SignedChar_MinMax);
    printf("\tMin and max values of 'signed char' = %d and %d\n", SignedChar_MinMax[0], SignedChar_MinMax[1]);
    UnsignedChar_Range(UnsignedChar_MinMax);
    printf("\tMin and max values of 'unsigned char' = %u and %u\n", UnsignedChar_MinMax[0], UnsignedChar_MinMax[1]);
    SignedShortInt_Range(SignedShortInt_MinMax);
    printf("\tMin and max values of 'signed short int' = %d and %d\n", SignedShortInt_MinMax[0], SignedShortInt_MinMax[1]);
    UnsignedShortInt_Range(UnsignedShortInt_MinMax);
    printf("\tMin and max values of 'unsigned short int' = %u and %u\n", UnsignedShortInt_MinMax[0], UnsignedShortInt_MinMax[1]);
    SignedInt_Range(SignedInt_MinMax);
    printf("\tMin and max values of 'signed int' = %'d and %'d\n", SignedInt_MinMax[0], SignedInt_MinMax[1]);
    UnSignedInt_Range(UnSignedInt_MinMax);
    printf("\tMin and max values of 'unsigned int' = %'u and %'u\n", UnSignedInt_MinMax[0], UnSignedInt_MinMax[1]);
    SignedLongInt_Range(SignedLongInt_MinMax);
    printf("\tMin and max values of 'signed long int' = %'ld and %'ld\n", SignedLongInt_MinMax[0], SignedLongInt_MinMax[1]);
    UnSignedLongInt_Range(UnSignedLongInt_MinMax);
    printf("\tMin and max values of 'unsigned long int' = %'lu and %'lu\n", UnSignedLongInt_MinMax[0], UnSignedLongInt_MinMax[1]);
    SignedLongLongInt_Range(SignedLongLongInt_MinMax);
    printf("\tMin and max values of 'signed long long int' = %'lld and %'lld\n", LLONG_MIN, LLONG_MAX);
    UnSignedLongLongInt_Range(UnSignedLongLongInt_MinMax);
    printf("\tMin and max values of 'unsigned long long int' = %'llu and %'llu\n", UnSignedLongLongInt_MinMax[0], UnSignedLongLongInt_MinMax[1]);
    Char_Range(Char_MinMax);
    printf("\tMin and max values of 'char' = %d and %d\n", Char_MinMax[0], Char_MinMax[1]);
    Short_Range(Short_MinMax);
    printf("\tMin and max values of 'short' = %'d and %'d\n", Short_MinMax[0], Short_MinMax[1]); 
    Int_Range(Int_MinMax);
    printf("\tMin and max values of 'int' = %'d and %'d\n", Int_MinMax[0], Int_MinMax[1]);
    Long_Range(Long_MinMax);
    printf("\tMin and max values of 'long' = %'ld and %'ld\n", Long_MinMax[0], Long_MinMax[1]);
    Unsigned_Range(Unsigned_MinMax);
    printf("\tMin and max values of 'unsigned' = %'u and %'u\n\n", Unsigned_MinMax[0], Unsigned_MinMax[1]);

    /* Floating point */
    printf("These values are from usr/lib/gcc/x86_64-linux-gnu/7/include/float.h\n");
    printf("\tMaximum representable finite floating-point number, (1 - b**-p) * b**emax\n");
    /* this will print all of the mantissa */
    /* printf("\t\tfloat max = %f, double max = %f, long double max = %Lf\n", FLT_MAX, DBL_MAX, LDBL_MAX); */
    printf("\t\tfloat max = %e, double max = %e, long double max = %Le\n", FLT_MAX, DBL_MAX, LDBL_MAX);
    printf("\tMinimum positive values\n");
    printf("\t\tfloat min = %e, double min = %e, long double = %Le\n", FLT_TRUE_MIN, DBL_TRUE_MIN, LDBL_TRUE_MIN);

    printf("\nThese floating point range values come from computation:\n");
    Float_Range(Float_MinMax);
    printf("\tMin and max values of 'float' = %e and %e\n", Float_MinMax[0], Float_MinMax[1]);
    Double_Range(Double_MinMax);
    printf("\tMin and max values of 'double' = %e and %e\n", Double_MinMax[0], Double_MinMax[1]);
    LongDouble_Range(LongDouble_MinMax);
    printf("\tMin and max values of 'long double' = %Le and %Le\n", LongDouble_MinMax[0], LongDouble_MinMax[1]);

    return 0;
}

void LongDouble_Range(long double LongDouble_MinMax[]) {
    long double total = 0;
    long double max;
    long double first = 1;
    long double second = first * 2.0;
    while (!isinf(second)) {
        first = second;
        second *= 2.0;
    }
    second = first;
    first = second / 2.0;
    total = second + first;
    while (!isinf(total)) {
        max = total;
        first = first / 2.0;
        total = total + first;
    }    
    first = 1;
    second = first / 2.0;
    while (second != 0.0) {
        first = second;
        second /= 2.0;
    }
    LongDouble_MinMax[0] = first;
    LongDouble_MinMax[1] = max;
    return;
}

void Double_Range(double Double_MinMax[]) {
    double total = 0;
    double max;
    double first = 1;
    double second = first * 2.0;
    while (!isinf(second)) {
        first = second;
        second *= 2.0;
    }
    second = first;
    first = second / 2.0;
    total = second + first;
    while (!isinf(total)) {
        max = total;
        first = first / 2.0;
        total = total + first;
    }    
    first = 1;
    second = first / 2.0;
    while (second != 0.0) {
        first = second;
        second /= 2.0;
    }
    Double_MinMax[0] = first;
    Double_MinMax[1] = max;
    return;
}

void Float_Range(float Float_MinMax[]) {
    /* https://cboard.cprogramming.com/c-programming/143938-how-determine-minimum-value-floating-point-types-using-direct-computation.html /
    /* from float.h, find mantissa digits and exponent digits */

    /* get to correct order of magnitude...quickly */
    float total = 0;
    float max;
    float first = 1;
    float second = first * 2.0;
    while (!isinf(second)) {
        first = second;
        second *= 2.0;
    }
    /* these are the biggest and second-biggest non inf floats */
    second = first;
    first = second / 2.0;

    /* now add them up by going backwards */
    total = second + first;
    while (!isinf(total)) {
        max = total;
        first = first / 2.0;
        total = total + first;
    }    
    /* max is the maximum */

    /* now for the minimum...this is not the biggest negative number. */
    /* It is the smallest number > 0 */
    first = 1;
    second = first / 2.0;
    while (second != 0.0) {
        first = second;
        second /= 2.0;
    }
    /* first is the minimum */

    Float_MinMax[0] = first;
    Float_MinMax[1] = max;
    return;
}

void UnSignedLongLongInt_Range(unsigned long long int UnSignedLongLongInt_MinMax[]) {
    /* get to correct order of magnitude...quickly */
    unsigned long long int increment;
    unsigned long long int first = 1;
    unsigned long long int second = first * 10;
    while (second > first) {
        first = second;
        second *= 10;
    }

    /* we are now in the same order of magnitude as the max */
    increment = first;
    while (increment != 0) {     /* at some point, the increment will be 1.  And 1 divided by 10 = 0 */
        second = first + increment;
        while (second > first) {
            first = second;
            second += increment;
        }
        increment = increment / 10;
    }
    UnSignedLongLongInt_MinMax[0] = second;
    UnSignedLongLongInt_MinMax[1] = first;
    return;
}

void SignedLongLongInt_Range(signed long long int SignedLongLongInt_MinMax[]) {
    /* get to correct order of magnitude...quickly */
    signed long long int increment;
    signed long long int first = 1;
    signed long long int second = first * 10;
    while (second > first) {
        first = second;
        second *= 10;
    }

    /* we are now in the same order of magnitude as the max */
    increment = first;
    while (increment != 0) {     /* at some point, the increment will be 1.  And 1 divided by 10 = 0 */
        second = first + increment;
        while (second > first) {
            first = second;
            second += increment;
        }
        increment = increment / 10;
    }
    SignedLongLongInt_MinMax[0] = second;
    SignedLongLongInt_MinMax[1] = first;
    return;
}

void UnSignedLongInt_Range(unsigned long int UnSignedLongInt_MinMax[]) {
    /* get to correct order of magnitude...quickly */
    unsigned long int increment;
    unsigned long int first = 1;
    unsigned long int second = first * 10;
    while (second > first) {
        first = second;
        second *= 10;
    }

    /* we are now in the same order of magnitude as the max */
    increment = first;
    while (increment != 0) {     /* at some point, the increment will be 1.  And 1 divided by 10 = 0 */
        second = first + increment;
        while (second > first) {
            first = second;
            second += increment;
        }
        increment = increment / 10;
    }
    UnSignedLongInt_MinMax[0] = second;
    UnSignedLongInt_MinMax[1] = first;
    return;
}
void Unsigned_Range(unsigned Unsigned_MinMax[]) {
    /* get to correct order of magnitude...quickly */
    unsigned increment;
    unsigned first = 1;
    unsigned second = first * 10;
    while (second > first) {
        first = second;
        second *= 10;
    }

    /* we are now in the same order of magnitude as the max */
    increment = first;
    while (increment != 0) {     /* at some point, the increment will be 1.  And 1 divided by 10 = 0 */
        second = first + increment;
        while (second > first) {
            first = second;
            second += increment;
        }
        increment = increment / 10;
    }
    Unsigned_MinMax[0] = second;
    Unsigned_MinMax[1] = first;
    return;
}

void Long_Range(long Long_MinMax[]) {
    /* get to correct order of magnitude...quickly */
    long increment;
    long first = 1;
    long second = first * 10;
    while (second > first) {
        first = second;
        second *= 10;
    }

    /* we are now in the same order of magnitude as the max */
    increment = first;
    while (increment != 0) {     /* at some point, the increment will be 1.  And 1 divided by 10 = 0 */
        second = first + increment;
        while (second > first) {
            first = second;
            second += increment;
        }
        increment = increment / 10;
    }
    Long_MinMax[0] = second;
    Long_MinMax[1] = first;
    return;
}

void SignedLongInt_Range(signed long int SignedLongInt_MinMax[]) {
    /* get to correct order of magnitude...quickly */
    signed long int increment;
    signed long int first = 1;
    signed long int second = first * 10;
    while (second > first) {
        first = second;
        second *= 10;
    }

    /* we are now in the same order of magnitude as the max */
    increment = first;
    while (increment != 0) {     /* at some point, the increment will be 1.  And 1 divided by 10 = 0 */
        second = first + increment;
        while (second > first) {
            first = second;
            second += increment;
        }
        increment = increment / 10;
    }
    SignedLongInt_MinMax[0] = second;
    SignedLongInt_MinMax[1] = first;
    return;
}

void UnSignedInt_Range(unsigned int UnSignedInt_MinMax[]) {
    /* get to correct order of magnitude...quickly */
    unsigned int increment;
    unsigned int first = 1;
    unsigned int second = first * 10;
    while (second > first) {
        first = second;
        second *= 10;
    }

    /* we are now in the same order of magnitude as the max */
    increment = first;
    while (increment != 0) {     /* at some point, the increment will be 1.  And 1 divided by 10 = 0 */
        second = first + increment;
        while (second > first) {
            first = second;
            second += increment;
        }
        increment = increment / 10;
    }

    UnSignedInt_MinMax[0] = second;
    UnSignedInt_MinMax[1] = first;
    return;
}

void Short_Range(short Short_MinMax[]) {
    /* get to correct order of magnitude...quickly */
    short increment;
    short first = 1;
    short second = first * 10;
    while (second > first) {
        first = second;
        second *= 10;
    }

    /* we are now in the same order of magnitude as the max */
    increment = first;
    while (increment != 0) {     /* at some point, the increment will be 1.  And 1 divided by 10 = 0 */
        second = first + increment;
        while (second > first) {
            first = second;
            second += increment;
        }
        increment = increment / 10;
    }

    Short_MinMax[0] = second;
    Short_MinMax[1] = first;
    return;
}

void Int_Range(int Int_MinMax[]) {
    /* get to correct order of magnitude...quickly */
    int increment;
    int first = 1;
    int second = first * 10;
    while (second > first) {
        first = second;
        second *= 10;
    }

    /* we are now in the same order of magnitude as the max */
    increment = first;
    while (increment != 0) {     /* at some point, the increment will be 1.  And 1 divided by 10 = 0 */
        second = first + increment;
        while (second > first) {
            first = second;
            second += increment;
        }
        increment = increment / 10;
    }

    Int_MinMax[0] = second;
    Int_MinMax[1] = first;
    return;
}

void SignedInt_Range(signed int SignedInt_MinMax[]) {
    /* get to correct order of magnitude...quickly */
    signed int increment;
    signed int first = 1;
    signed int second = first * 10;
    while (second > first) {
        first = second;
        second *= 10;
    }

    /* we are now in the same order of magnitude as the max */
    increment = first;
    while (increment != 0) {     /* at some point, the increment will be 1.  And 1 divided by 10 = 0 */
        second = first + increment;
        while (second > first) {
            first = second;
            second += increment;
        }
        increment = increment / 10;
    }

    SignedInt_MinMax[0] = second;
    SignedInt_MinMax[1] = first;
    return;
}

void UnsignedShortInt_Range(unsigned short int UnsignedShortInt_MinMax[]) {
    unsigned short int first = 0;
    unsigned short int second = first + 1;
    while (second > first) {
        first = second;
        second += 1;
    }
    UnsignedShortInt_MinMax[0] = second;
    UnsignedShortInt_MinMax[1] = first;
    return;
}

void SignedShortInt_Range(signed short int SignedShortInt_MinMax[]) {
    signed short int first = 0;
    signed short int second = first + 1;
    while (second > first) {
        first = second;
        second += 1;
    }
    SignedShortInt_MinMax[0] = second;
    SignedShortInt_MinMax[1] = first;
    return;
}

void Char_Range(char Char_MinMax[]) {
    char first = 0;
    char second = first + 1;
    while (second > first) {
        first = second;
        second += 1;
    }
    Char_MinMax[0] = second;
    Char_MinMax[1] = first;
    return;
}

void UnsignedChar_Range(unsigned char UnsignedChar_MinMax[]) {
    unsigned char first = 0;
    unsigned char second = first + 1;
    while (second > first) {
        first = second;
        second += 1;
    }
    UnsignedChar_MinMax[0] = second;
    UnsignedChar_MinMax[1] = first;
    return;
}

void SignedChar_Range(signed char SignedChar_MinMax[]) {
    signed char first = 0;
    signed char second = first + 1;
    while (second > first) {
        first = second;
        second += 1;
    }
    SignedChar_MinMax[0] = second;
    SignedChar_MinMax[1] = first;
    return;
}



