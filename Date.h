#pragma once
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
		Date(int day, int month, int year);
		Date() {};
		int getDay() const { return _day; }
		int getMonth() const { return _month; }
		int getYear() const { return _year; }
	};
}
