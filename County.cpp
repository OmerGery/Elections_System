#define _CRT_SECURE_NO_WARNINGS
#include "County.h"
#include <iostream>


using namespace std;

namespace votes
{
	
	int County::countyCounter=0;
	County::County(const string& countyName, int numdelegates)
	{
		string errorName;
		if (numdelegates <= 0)
			throw (errorName = "Number of delegate must be a positive number");
		_countyName = countyName;
		_numdelegates = numdelegates;
		_countySerial=++countyCounter;
	}
	CountyDelegate* County::getDelgate(int delgatePlace)const
	{
		return CDArr.at(delgatePlace);
	}
	ostream& operator<<(ostream& os, const County& county)
	{
		os<< "County Number:"<<county._countySerial << " County Name:" << county._countyName << " Amount of Delegates:" << county._numdelegates;
		return os;
	}
	County::~County()
	{
		for (int i = 0; i < CDArr.size(); i++)
			delete CDArr.at(i);
		list<Citizen*>::const_iterator itr = _citizenAllowed.begin();
		list<Citizen*>::const_iterator end = _citizenAllowed.end();
		for (; itr != end; ++itr)
			delete(*itr);
	}
	County::County()
	{
		_numdelegates =-1;
		_countySerial =-1;
	}
	void County::AddCD(CountyDelegate* delegate)
	{
		CDArr.push_back(delegate);
	}
	Citizen* County::searchCitizen(int id)const
	{
		return findCitizen(id);
	}
	void County::getCountyVotes(vector<int> &votearr)
	{
		getVotes(votearr);
	}
	void County::PrintCitizenList() const
	{
		PrintList(_countyName);
	}
	void County::saveCounty(ostream& out) const
	{
		out.write(rcastcc(&_countySerial), sizeof(_countySerial));
		out.write(rcastcc(&_numdelegates), sizeof(_numdelegates));
		out.write(rcastcc(&countyCounter), sizeof(countyCounter));
		int countyNamelen = static_cast<int> (_countyName.size());
		out.write(rcastcc(&countyNamelen), sizeof(countyNamelen));
		out.write(rcastcc(&_countyName[0]), sizeof(char) * countyNamelen);
		saveCitizensList(out);
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
		loadCitizensList(in);
	}
	//citizenlist:
	void County::AddCitizen(Citizen* toadd)
	{
		_citizenAllowed.push_back(toadd);
	}
	Citizen* County::getCitizenByIndex(int index) const
	{
		list<Citizen*>::const_iterator it = _citizenAllowed.begin();
		advance(it, index);
		return *it;
	}
	void County::PrintList(string countyName) const
	{
		list<Citizen*>::const_iterator itr = _citizenAllowed.begin();
		list<Citizen*>::const_iterator end = _citizenAllowed.end();
		for (; itr != end; ++itr) 
		{
			cout << **itr;
			cout << " County: " << countyName << endl;
		}
	}
	void County::getVotes(vector<int>& voteArr) const
	{
		int currentVote;
		list<Citizen*>::const_iterator itr = _citizenAllowed.begin();
		list<Citizen*>::const_iterator end = _citizenAllowed.end();
		const Party* PartyVotedTo;
		for (; itr != end; ++itr)
		{
			PartyVotedTo = (*itr)->getVote();
			if (PartyVotedTo)
				currentVote = PartyVotedTo->getPartySerial();
			else
				currentVote = -1;
			if (currentVote != -1)
			{
				voteArr[currentVote]++;
				voteArr[0]++;
			}
		}
	}
	Citizen* County::findCitizen(int id) const
	{
		list<Citizen*>::const_iterator itr = _citizenAllowed.begin();
		list<Citizen*>::const_iterator end = _citizenAllowed.end();
		for (; itr != end; ++itr)
		{
			if ((*itr)->getID() == id)
				return *itr;
		}
		return nullptr;
	}
	void County::saveCitizensList(ostream& out) const
	{
		int size = static_cast<int>(_citizenAllowed.size());
		out.write(rcastcc(&size), sizeof(size));
		list<Citizen*>::const_iterator itr = _citizenAllowed.begin();
		list<Citizen*>::const_iterator end = _citizenAllowed.end();
		for (; itr != end; ++itr)
			(*itr)->saveCitizen(out);
	}
	void County::loadCitizensList(istream& in)
	{
		string errorName;
		int loadSize = static_cast<int>(_citizenAllowed.size());
		in.read(rcastc(&loadSize), sizeof(loadSize));
		for (int i = 0; i < loadSize; i++)
		{
			Citizen* toadd = new Citizen();
			if (!toadd)
				throw (errorName = "Memory Allocation failed.");
			toadd->loadCitizen(in);
			AddCitizen(toadd);
		}
	}
}
