#pragma once
#include <fstream>
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
using namespace std;
namespace votes
{
	static const int c_maxDayPerMonthArr[13] = { -1,31,28,31,30, 31, 30, 31, 31, 30, 31, 30, 31 };
	class Date
	{
	private:
		int _day;
		int _month;
		int _year;
	public:
		Date(int day=1, int month=1, int year=1900);
		int getDay() const { return _day; }
		int getMonth() const { return _month; }
		int getYear() const { return _year; }
		void loadDate(istream& in);
		void saveDate(ostream& out) const;
	};
}
