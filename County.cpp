#define _CRT_SECURE_NO_WARNINGS
#include "County.h"
#include <iostream>
#include <string.h>


using namespace std;

namespace votes
{
	
	int County::countyCounter=0;
	County::County(char* countyName, int numdelegates)
	{
		CDArr = countyDelegateArr();
		_citizenAllowed = CitizenList();
		_countyName = new char[strlen(countyName)+1];
		strcpy(_countyName,countyName);
		_numdelegates = numdelegates;
		_countySerial=++countyCounter;
	}
	CountyDelegate County::getDelgate(int delgatePlace)const
	{
		return this->CDArr.getDel(delgatePlace);
	}
	County::~County()
	{
	//	delete[] _countyName;
	}
	//County::County(County const&  tocopyfrom)
	//{
	//	this->_citizenAllowed = tocopyfrom._citizenAllowed;
	//	this->_countySerial = tocopyfrom._countySerial;
	//	this->_numdelegates = tocopyfrom._numdelegates;
	//	int len = strlen(tocopyfrom._countyName+1);
	//	this->_countyName = new char[len];
	//	strcpy(_countyName, tocopyfrom._countyName);
	//	delete[] tocopyfrom._countyName;
	//}
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
	void County::AddCD(CountyDelegate& delegate)
	{
		(this->CDArr).insert(delegate);
	}
	CitizenList County::GetCitizens() const
	{
		return _citizenAllowed;
	}
}
