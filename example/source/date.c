#include"public.h"
#include"date.h"

//int isrunyear (int year);   //判断是否为闰年
//int month_days (int month, int year);    //给定每个月的天数
int ReturnDate(int days,DATE *pdate)
{
	DATE date1;
	DATE date2;
	date1.year = 2023;
	date1.month = 4;
	date1.day = 22;
	pdate->year = date1.year;
	pdate->month = date1.month;
	pdate->day = date1.day;   //将date1赋值给date2
	while (days)
	{
		days--;
		if (pdate->day != month_days (pdate->month, pdate->year))
		{
			pdate->day++;
		}
		else
		{
			if (pdate->month != 12)
			{
				pdate->month++;
				pdate->day = 1;
			}
			else
			{
				pdate->year++;
				pdate->month = 1;
				pdate->day = 1;
			}
		}
	}
	return 0;
}

int isrunyear (int year)
{
	if (year % 400 == 0 || year % 4 == 0 && year % 100 != 0)
		return 1;
	else
		return 0;
}

int month_days (int month, int year)
{
	switch (month)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			return 31;
		case 4:
		case 6:
		case 9:
		case 11:
			return 30;
		case 2:
			return isrunyear (year) ? 29 : 28;
		default:
			return -1;
	}
}