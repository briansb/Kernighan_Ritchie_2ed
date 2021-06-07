#include <stdio.h>

static char daytab[2][13] = {
    {0,31,28,31,30,31,30,31,31,30,31,30,31},
    {0,31,29,31,30,31,30,31,31,30,31,30,31}
};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main() {

    char option;
    printf("Compute day of year (1) or month/day (2)\n");
    option = getchar();
    if (option == '1') {
        printf("Computing day of year from year/month/day\n");
        printf("%d\n", day_of_year(2020, 03, 15));
    } else {
        printf("Computing month/day from day of year\n");
        int month, day;
        month_day(2020, 75, &month, &day);
        printf("Month %d, Day %d\n", month, day);
    }

    return 0;
}
/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day) {
    int i, leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    for (i = 1; i < month; i++)
        day += daytab[leap][i];
    return day;
}
/* month_day:  set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
}