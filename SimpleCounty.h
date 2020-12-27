#pragma once
#include "County.h"
namespace votes
{
	class SimpleCounty :public County
	{
	public:
		SimpleCounty(const char* countyName, int numdelegates) : County(countyName, numdelegates) {}
		virtual void GetPartiesElectors(float* statisticsArray, int* countyElectors, int partiesSize)const override;
		virtual void sortAndPrintWinners(int* voteCount, int* Electors, int partiesSize, PartyList* partylist)const override;
		virtual void printCountyType() const override;
	};
}