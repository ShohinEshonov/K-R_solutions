#include <stdio.h>


static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day);
int month_day(int year, int yearday, int *pmonth, int *pday);


int main()
{
	int year  = 1927;
	int month = 12;
       	int day   = 31;

	
	int yearday = 365;
	int pday;
	int pmonth;



	int _month_day = month_day(year, yearday, &pmonth, &pday); 

	if(_month_day == -1)
	{
		printf("Error: Invalid year %d", year);
		return 1;

	}


	if(_month_day == -2)
	{
		printf("Error: Invalid yearday %d", yearday);
		return 2;
	}	
	
	int day_year = day_of_year(year, month, day);

	if(day_year == -1)
	{
		printf("Error: Invalid month %d\n", month);
		return 3;
	}

	if(day_year == -2)
	{
		printf("Error: Invalid day  %d\n", day);
		return 4;
	}

	printf("Year:%d, Month:%d, Day:%d, Day of year: %d\n",year, month, day, day_year);
	printf("Year:%d, Yearday:%d, month:%d, day:%d\n", year, yearday, pmonth, pday);

}








int day_of_year(int year, int month, int day)
{
	if(month > 12 || month < 1)
		return -1;

	if(day > 31 || day < 1)
		return -2;
	
	int leap;	

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

	char *p = &daytab[leap][1];

	while(month-- > 1)
		day += *p++;

	return day;
}



int month_day(int year, int yearday, int *pmonth, int *pday)
{
	if(year < 1)
		return -1;
	if(yearday > 366 || yearday < 1)
		return -2;
	



	int leap, i;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	
	if(leap == 0 && yearday > 365)
		return -2;
	
	char *p = &daytab[leap][1]; 

	for(i = 1; yearday > *p; i++) 
		yearday -= *p++;
	*pmonth = i;
	*pday   = yearday;

	return 0;
}


