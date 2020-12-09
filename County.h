#pragma once

#include "Party.h"
#include "CitizenList.h"
#include "Citizen.h"
#include "CountyDelegateArr.h"
#include "CountyDelegate.h"
namespace votes
{
	class County
	{
	
	private:
		int _countySerial;//id 
		char* _countyName;
		int _numdelegates;
		CitizenList _citizenAllowed;
     	countyDelegateArr CDArr;
		static int countyCounter;

	public:
		County(char* countyName, int numdelegates);
		County();
		//County(County const& tocopyfrom);
		
		~County();
		void AddCitizen(Citizen* citizen);
		void AddCD(CountyDelegate& delegate);
		CitizenList GetCitizens() const;
		CountyDelegate getDelgate(int delgatePlace)const;
		const char* getCountyName() const { return _countyName; }
		int getCountySerial() const { return _countySerial; }
		const int getdelegatesNum() const { return this->_numdelegates; }
		countyDelegateArr getDelgatesArr() const { return CDArr; };
	};
}
