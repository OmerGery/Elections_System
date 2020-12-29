#pragma once
#include "App.h"
namespace votes
{
	class SimpleApp: public App
	{
	public:
		SimpleApp(Date* electionday, int delegatesNum);
		virtual void AddCounty(char* name, int delegatesNum, bool simple) override;
		virtual bool AddCitizen(char* name, int id, int year, int countynum) override;
		virtual void PrintAllCounties() const override;
		virtual bool AddCitizenAsDelegate(int id, int partynum, int countynum) override;
		virtual void printVotes() override;
		virtual void saveApp(ostream& out) const override;
	};
}
