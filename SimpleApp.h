#pragma once
#include "App.h"
namespace votes
{
	// SimpleApp is using app, used for "simple" round of election

	static const char defaultName[] = "default";

	class SimpleApp: public App
	{
	public:
		//ctors:
		SimpleApp(Date electionday, int delegatesNum); 
		SimpleApp(Date electionday) :App(electionday) {}// CTOR to make an "empty simple app"

		virtual void AddCounty(string name, int delegatesNum, int type) override;
		virtual void AddCitizen(string name, int id, int year, int countynum) override;
		virtual void AddCitizenAsDelegate(int id, int partynum, int countynum) override;

		virtual void PrintAllCounties() const override;
		virtual void printVotes() override;

		virtual void saveApp(ostream& out) const override;
		
	};
}
