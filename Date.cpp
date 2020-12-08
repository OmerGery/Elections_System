#define _CRT_SECURE_NO_WARNINGS
#include "Date.h"
#include <string.h>
#include <iostream>

using namespace std;
namespace votes
{
	Date::Date(int day, int month, int year)
	{
		if (day < c_maxDayPerMonthArr[month])
			_day = day;
		if (month > 0 && month <= 12 && c_maxDayPerMonthArr[month] >= _day)
			_month = month;
		_year = year;
	}
}

