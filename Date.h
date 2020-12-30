#pragma once
#include <fstream>
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
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
		Date(int day,int month ,int year);
		Date();
		int getDay() const { return _day; }
		int getMonth() const { return _month; }
		int getYear() const { return _year; }
		void loadDate(istream& in);
		void saveDate(ostream& out) const;
	};
}
