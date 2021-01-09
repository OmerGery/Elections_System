#pragma once
#include "Party.h"
#include "Citizen.h"
#include "CitizenList.h"
#include "CountyDelegate.h"
#include "Sort.h"
#include "DynamicArray.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;
namespace votes
{
	class County
	{
	protected:
		DynamicArray <CountyDelegate*> CDArr;
		int _countySerial;
		string _countyName;
		int _numdelegates;
		list <Citizen*> _citizenAllowed;
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
				//citizenlist:
		void getVotes(vector<int>& voteArr) const;
		Citizen* getData(int index) const;
		const int getSize() const { return static_cast<int>(_citizenAllowed.size()); }

		Citizen* findCitizen(int id) const;
		void PrintList(string countyName) const;

		void saveCitizensList(ostream& out) const;
		void loadCitizensList(istream& in);
		///
		CountyDelegate* getDelgate(int delgatePlace)const;
		const string getCountyName() const { return _countyName; }
		int getCountySerial() const { return _countySerial; }
		const int getdelegatesNum() const { return this->_numdelegates; }
		const int getDelgatesarrSize()const { return static_cast<const int>(CDArr.size()); }
		const int getCountySize()const { return _citizenAllowed.size(); };
		Citizen* getCitizenByIndex(int index)const { return getData(index); }
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

		CountyDelegate* getDel(int place)const { return CDArr.at(place); }

	};
}
