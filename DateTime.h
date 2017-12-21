typedef struct{
	int year;
	int month;
	int day;
}DateTime;

DateTime *createDateTime(int year, int month, int day);
void printDateTime(DateTime *d);
int getDifference(DateTime *dt1, DateTime *dt2);
int countLeapYears(DateTime *d);
