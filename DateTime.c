#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "DateTime.h"
#include "Node.h"
#include "Path.h"

/**
Creates new dateTime
params:
int year - year
int month - month
int day - day
*/
DateTime *createDateTime(int year, int month, int day){
	DateTime *tmp = NULL;
	tmp = malloc(sizeof(DateTime));
	tmp->year = year;
	tmp->month = month;
	tmp->day = day;
	return tmp;
}

//Days in each month
const int monthDays[13] = {0,31, 28, 31, 30, 31, 30,
                           31, 31, 30, 31, 30, 31};

/**
Prints DateTime
params:
DateTie *d - datetime to print
*/
void printDateTime(DateTime *d)
{
    printf("%d-%d-%d; \n", d->year, d->month, d->day);
    return;
}

/**
Counts leap years since 0.0.0000 to date
params:
DateTime *d - date
returns: 
int - number of leap years
*/
int countLeapYears(DateTime *d)
{
    int years = d->year;
    if (d->month <= 2)
        years--;
    return years / 4 - years / 100 + years / 400;
}

/**
Counts days between two dates
params:
DateTime *d1 - first date
DateTime *d2 - second date
returns:
int - number of days
*/
int getDifference(DateTime *dt1, DateTime *dt2)
{
	int i;
	int n1, n2;
	n1 = dt1->year * 365 + dt1->day;
	n1 += countLeapYears(dt1);
	for(i=0; i<dt1->month;i++) n1+=monthDays[i];
	n2 = dt2->year * 365 + dt2->day;
	n2 += countLeapYears(dt2);
	for(i=0; i<dt2->month;i++) n2+=monthDays[i];

    return (n2 - n1);
}



