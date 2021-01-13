
#pragma once
#include <fstream>
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
using namespace std;
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
static const int maxDayPerMonth[13] = { -1,31,28,31,30, 31, 30, 31, 31, 30, 31, 30, 31 };
using namespace std;
namespace votes
{
	class Date
	{
	private:
		int _day;
		int _month;
		int _year;
	public:
		//ctors:
		Date(int day,int month ,int year);
		Date();
		// no memory allocation - default copy ctor and operator= are used.
		//getters
		int getDay() const { return _day; }
		int getMonth() const { return _month; }
		int getYear() const { return _year; }
		friend ostream& operator<<(ostream& os, const Date& date);
		//save/load
		void loadDate(istream& in);
		void saveDate(ostream& out) const;
	};
}
