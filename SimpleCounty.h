#pragma once
#include "County.h"
#include <vector>
namespace votes
{
	class SimpleCounty :public County
	{
	public:
		//ctors:
		SimpleCounty(const string countyName, int numdelegates) : County(countyName, numdelegates) {}
		SimpleCounty() {}

		virtual void GetPartiesElectors(vector<float>& statisticsArray, vector<int>& countyElectors, int partiesSize)const override;
		virtual void sortAndPrintWinners(vector<int>& voteCount, vector<int>& Electors, int partiesSize, list <Party*> partylist)const override;
		virtual void printCountyType() const override;

		virtual void saveCounty(ostream& out) const override;
	};
}