#pragma once
#include "App.h"
namespace votes
{
	class RegularApp : public App
	{
	public:
		RegularApp(Date electionday) :App(electionday) {};
		virtual void AddCounty(char* name, int delegatesNum, bool simple) override;
		virtual bool AddCitizen(char* name, int id, int year, int countynum) override;
		virtual void PrintAllCounties() const override;
		virtual bool AddCitizenAsDelegate(int id, int partynum, int countynum) override;
		bool printVotes() override;
		virtual void saveApp(ostream& out)const override;
	};

}
