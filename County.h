#pragma once
#include "Party.h"
#include "CitizenList.h"
#include "Citizen.h"
#include "CountyDelegateArr.h"
#include "CountyDelegate.h"
#include <iostream>
using namespace std;
namespace votes
{
	class County
	{
	
	private:
		int _countySerial;
		char* _countyName;
		int _numdelegates;
		CitizenList _citizenAllowed;
     	countyDelegateArr CDArr;
		static int countyCounter;

	public:
		County(char* countyName, int numdelegates);
		County();
		~County();
		void AddCitizen(Citizen* citizen);
		void AddCD(CountyDelegate* delegate);
		CountyDelegate* getDelgate(int delgatePlace)const;
		const char* getCountyName() const { return _countyName; }
		int getCountySerial() const { return _countySerial; }
		const int getdelegatesNum() const { return this->_numdelegates; }
		countyDelegateArr getDelgatesArr() const { return CDArr; };
		const int getDelgatesarrSize()const { return CDArr.getSize(); }
		const int getCountySize()const { return _citizenAllowed.getSize(); };
		friend ostream& operator<<(ostream& os, const County& county);
		Citizen* searchCitizen(int id)const;
		void PrintCitizenList() const;
		void getCountyVotes(int* votearr);
	};
}
