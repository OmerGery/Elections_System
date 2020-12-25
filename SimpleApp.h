#pragma once
#include "App.h"
#include "Citizen.h"
#include "Party.h"
#include "Date.h"
#include "CitizenList.h"
#include "County.h"
#include "CountyArr.h"
#include "CountyDelegate.h"
#include "PartyList.h"

namespace votes
{
	class SimpleApp: public App
	{
	public:
		SimpleApp(Date& electionday, int delegatesNum);
		virtual void AddCounty(char* name, int delegatesNum, bool simple) override;
		virtual bool AddCitizen(char* name, int id, int year, int countynum) override;
		virtual void PrintAllCounties() const override;
		virtual bool AddCitizenAsDelegate(int id, int partynum, int countynum) override;
		virtual void printVotes() override;
	};
}
