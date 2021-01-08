#define _CRT_SECURE_NO_WARNINGS
#include "County.h"
#include <iostream>
#include <string.h>


using namespace std;

namespace votes
{
	
	int County::countyCounter=0;
	County::County(const string& countyName, int numdelegates)
	{
		_countyName = countyName;
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
	}
	County::County()
	{
		_numdelegates =-1;
		_countySerial =-1;
	}
	void County::AddCitizen(Citizen* citizen)
	{
		_citizenAllowed.AddCitizen(citizen);
	}
	void County::AddCD(CountyDelegate* delegate)
	{
		CDArr.insert(delegate);
	}
	Citizen* County::searchCitizen(int id)const
	{
		return _citizenAllowed.findCitizen(id);
	}
	void County::getCountyVotes(vector<int> &votearr)
	{
		_citizenAllowed.getVotes(votearr);
	}
	void County::PrintCitizenList() const
	{
		this->_citizenAllowed.PrintList(_countyName);
	}
	void County::saveCounty(ostream& out) const
	{
		out.write(rcastcc(&_countySerial), sizeof(_countySerial));
		out.write(rcastcc(&_numdelegates), sizeof(_numdelegates));
		out.write(rcastcc(&countyCounter), sizeof(countyCounter));
		int countyNamelen = static_cast<int> (_countyName.size());
		out.write(rcastcc(&countyNamelen), sizeof(countyNamelen));
		out.write(rcastcc(&_countyName[0]), sizeof(char) * countyNamelen);
		_citizenAllowed.saveCitizensList(out);
	}
	void County::loadCounty(istream& in)
	{
		in.read(rcastc(&_countySerial), sizeof(_countySerial));
		in.read(rcastc(&_numdelegates), sizeof(_numdelegates));
		in.read(rcastc(&countyCounter), sizeof(countyCounter));
		int countyNamelen = 0;
		in.read(rcastc(&countyNamelen), sizeof(countyNamelen));
		_countyName.resize(countyNamelen);
		in.read(rcastc(&_countyName[0]), sizeof(char) * countyNamelen);
		_citizenAllowed.loadCitizensList(in);
	}
}
