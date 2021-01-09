#define _CRT_SECURE_NO_WARNINGS
#include "Date.h"
#include <string.h>
#include <iostream>
using namespace std;
namespace votes
{
	Date::Date()
	{
		_day = 1;
		_month = 1;
		_year = 1900;
	}
	Date::Date(int day ,int month , int year)
	{
		string errorName;
		if (year < 0)
			throw (errorName = "Year can't be a negative number");
		if (month < 1 || day > maxDayPerMonth[month] || day < 1)
			throw (errorName = "Date wasn't valid, out of the calander");
		_day = day;
		_month = month;
		_year = year;
	}

	void Date::saveDate(ostream& out) const
	{
		out.write(rcastcc(&_day), sizeof(_day));
		out.write(rcastcc(&_month), sizeof(_month));
		out.write(rcastcc(&_year), sizeof(_year));
	}
	void Date::loadDate(istream& in)
	{
		in.read(rcastc(&_day), sizeof(_day));
		in.read(rcastc(&_month), sizeof(_month));
		in.read(rcastc(&_year), sizeof(_year));
	}
	ostream& operator<<(ostream& os, const Date& date)
	{
		os << "The Election Date is: " << date.getDay() << "/" << date.getMonth() << "/" << date.getYear() << endl;
		return os;
	}
}

