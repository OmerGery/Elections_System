#pragma once

#include "Party.h"
#include "CitizenList.h"
#include "Citizen.h"
#include "CountyDelegateArr.h"
#include "CountyDelegate.h"
#include "Sort.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;
namespace votes
{
	class County
	{
	protected:
		int _countySerial;
		string _countyName;
		int _numdelegates;
		CitizenList _citizenAllowed;
		countyDelegateArr CDArr;
		static int countyCounter;

	public:
		//ctors/dtors:
		County(const string& countyName, int numdelegates);
		County();
		virtual ~County();
		// we don't use a "County" by-val initing, but we make sure no code will be using default operator '=' or 'copy ctor' by cancelling them. 
		County(const County& other) = delete;
		County& operator=(const County& other) = delete;

		//getters:
		CountyDelegate* getDelgate(int delgatePlace)const;
		const string getCountyName() const { return _countyName; }
		int getCountySerial() const { return _countySerial; }
		const int getdelegatesNum() const { return this->_numdelegates; }
		const int getDelgatesarrSize()const { return CDArr.getSize(); }
		const int getCountySize()const { return _citizenAllowed.getSize(); };
		Citizen* getCitizenByIndex(int index)const { return this->_citizenAllowed.getData(index); }
		void getCountyVotes(vector<int> &votearr);
		virtual void GetPartiesElectors(vector<float>& statisticsArray, vector<int>& countyElectors, int partiesSize)const = 0;

		void AddCitizen(Citizen* citizen);
		void AddCD(CountyDelegate* delegate);
		friend ostream& operator<<(ostream& os, const County& county);
		Citizen* searchCitizen(int id)const;
		void resetCounter() { countyCounter = 0; }

		virtual void sortAndPrintWinners(vector<int>& voteCount, vector<int>& Electors,int partiesSize, list <Party*> partylist)const = 0;
		void PrintCitizenList() const;
		virtual void printCountyType() const=0;

		virtual void saveCounty(ostream& out) const=0;
		void loadCounty(istream& in);
	};
}
