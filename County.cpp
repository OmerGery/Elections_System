#define _CRT_SECURE_NO_WARNINGS
#include "County.h"
#include <iostream>
#include <string.h>


using namespace std;

namespace votes
{
	
	int County::countyCounter=0;
	County::County(const char* countyName, int numdelegates)
	{
		_countyName = new char[strlen(countyName)+1];
		strcpy(_countyName,countyName);
		_numdelegates = numdelegates;
		_countySerial=++countyCounter;
	}
	CountyDelegate* County::getDelgate(int delgatePlace)const
	{
		return CDArr.getDel(delgatePlace);
	}
	ostream& operator<<(ostream& os, const County& county)
	{
		os<< "County Number:"<<county._countySerial << " County Name:" << county._countyName << " Amount of Delegates:" << county._numdelegates;
		return os;
	}
	County::~County()
	{
		delete[] _countyName;
	}
	County::County()
	{
		_countyName = nullptr;
		_numdelegates =-1;
		_countySerial =-1;
	}
	void County::AddCitizen(Citizen* citizen)
	{
		_citizenAllowed.AddCitizen(citizen);
	}
	void County::AddCD(CountyDelegate* delegate)
	{
		(this->CDArr).insert(delegate);
	}
	Citizen* County::searchCitizen(int id)const
	{
		return _citizenAllowed.findCitizen(id);
	}
	void County::getCountyVotes(int* votearr)
	{
		_citizenAllowed.getVotes(votearr);
	}
	void County::PrintCitizenList() const
	{
		this->_citizenAllowed.PrintList();
	}
	void County::saveCounty(ostream& out) const
	{

		//CitizenList _citizenAllowed;
		//countyDelegateArr CDArr;
		out.write(rcastcc(&_countySerial), sizeof(_countySerial));
		out.write(rcastcc(&_numdelegates), sizeof(_numdelegates));
		out.write(rcastcc(&countyCounter), sizeof(countyCounter));
		int countyNamelen = static_cast<int> (strlen(_countyName));
		out.write(rcastcc(&countyNamelen), sizeof(countyNamelen));
		for (int i = 0; i <countyNamelen; i++)
			out.write(rcastcc(&_countyName[i]), sizeof(char));
		_citizenAllowed.saveCitizensList(out);

	}
}
