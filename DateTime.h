typedef struct dat DateTime;

struct dat{
	int year;
	int month;
	int day;
};

DateTime *createDateTime(int year, int month, int day);
void printDateTime(DateTime *d);
int getDifference(DateTime *dt1, DateTime *dt2);
int countLeapYears(DateTime *d);
