#ifndef DATE_UTILS_H_
#define DATE_UTILS_H_

#define DAYS_IN_WEEK		7
#define MONTHS_IN_YEAR		12
#define YEARS_IN_CENTURY	100

static const int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

enum days {MONDAY = 0, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY};
enum months {JANUARY = 0, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER};

int is_leap_year (int);

#endif
