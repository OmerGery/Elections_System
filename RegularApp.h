#pragma once
#include "App.h"
namespace votes
{
	// RegularApp is using app, used for "regular" round of election
	class RegularApp : public App
	{
	public:
		//ctor:
		RegularApp(Date electionday) :App(electionday) {};

		virtual void AddCounty(string name, int delegatesNum, bool simple) override;
		virtual bool AddCitizen(string name, int id, int year, int countynum) override;
		virtual bool AddCitizenAsDelegate(int id, int partynum, int countynum) override;

		virtual void PrintAllCounties() const override;
		bool printVotes() override;

		virtual void saveApp(ostream& out)const override;
	};

}
