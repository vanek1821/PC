#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "DateTime.h"
#include "Node.h"
#include "Path.h"

DateTime *createDateTime(int year, int month, int day){
	DateTime *tmp = NULL;
	tmp = malloc(sizeof(DateTime));
	tmp->year = year;
	tmp->month = month;
	tmp->day = day;
	return tmp;
}
