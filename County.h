#pragma once

#include "Party.h"
#include "CitizenList.h"
#include "PartyList.h"
#include "Citizen.h"
#include "CountyDelegateArr.h"
#include "CountyDelegate.h"
#include "Sort.h"
#include <iostream>
using namespace std;
namespace votes
{
	class County
	{
	protected:
		int _countySerial;
		char* _countyName;
		int _numdelegates;
		CitizenList _citizenAllowed;
		countyDelegateArr CDArr;
		static int countyCounter;

	public:
		County(const char* countyName, int numdelegates);
		County();
		virtual ~County();
		void resetCounter() { countyCounter = 0; }
		County(const County& other) = delete;//according to moshe's instructions , we can either implent or delete a copy c'tor.
		County& operator=(const County& other) = delete;//according to moshe's instructions , we can either implent or delete a opertor=.
		void AddCitizen(Citizen* citizen);
		void AddCD(CountyDelegate* delegate);
		CountyDelegate* getDelgate(int delgatePlace)const;
		const char* getCountyName() const { return _countyName; }
		int getCountySerial() const { return _countySerial; }
		const int getdelegatesNum() const { return this->_numdelegates; }
		const int getDelgatesarrSize()const { return CDArr.getSize(); }
		const int getCountySize()const { return _citizenAllowed.getSize(); };
		friend ostream& operator<<(ostream& os, const County& county);
		Citizen* searchCitizen(int id)const;
		void PrintCitizenList() const;
		void getCountyVotes(int* votearr);
		virtual void GetPartiesElectors(float* statisticsArray, int* countyElectors, int partiesSize)const=0;
		virtual void sortAndPrintWinners(int* voteCount,int* Electors,int partiesSize,PartyList* partylist)const = 0;
		virtual void printCountyType() const=0;
		virtual void saveCounty(ostream& out) const=0;
		void loadCounty(istream& in);
		Citizen* getCitizenByIndex(int index)const { return this->_citizenAllowed.getData(index); }
	};
}
