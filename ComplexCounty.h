#pragma once
#include "County.h"
#include <vector>
namespace votes
{
	class ComplexCounty :public County
	{
	public:
		//ctors:
		ComplexCounty(const string countyName, int numdelegates) : County(countyName, numdelegates) {}
		ComplexCounty() {}

		virtual void GetPartiesElectors(vector<float>& statisticsArray, vector<int>& countyElectors, int partiesSize)const override;
		virtual void sortAndPrintWinners(vector<int>& voteCount, vector<int>& Electors, int partiesSize, PartyList* partylist)const override;
		virtual void printCountyType() const override;
		virtual void saveCounty(ostream& out) const override;
	};
}