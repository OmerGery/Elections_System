#define _CRT_SECURE_NO_WARNINGS
#include "Party.h"
#include "CitizenList.h"
#include "County.h"
#include "CountyArr.h"
#include "CountyDelegate.h"
#include "PartyList.h"
#include <iostream>
#include <string.h>

using namespace std;

namespace votes
{
	int Party::partyCounter = 0;
	Party::Party(const char* partyName, Citizen* leader)
	{
		int len = static_cast<int>(strlen(partyName) + 1);
		_partyName = new char[len];
		strcpy(_partyName, partyName);
		_partySerial = ++partyCounter;
		_leader = leader;
	}
	Party::~Party()
	{		
		delete[] _partyName;	
	}
	ostream& operator<<(ostream& os, const Party& party)
	{
		os << "Party Number:"<< party._partySerial << " Party Name:'" << party._partyName << "' Party Leader:" << party._leader->getName() << endl;
		return os;
	}
	void Party::saveParty(ostream& out) const
	{
		out.write(rcastcc(&_partySerial), sizeof(_partySerial));
		out.write(rcastcc(&partyCounter), sizeof(partyCounter));
		int partyNamelen = static_cast<int> (strlen(_partyName) + 1);
		out.write(rcastcc(&partyNamelen), sizeof(partyNamelen));
		out.write(rcastcc(&_partyName[0]), sizeof(char) * partyNamelen);
	}
	void Party::loadParty(istream& in)
	{
		in.read(rcastc(&_partySerial), sizeof(_partySerial));
		in.read(rcastc(&partyCounter), sizeof(partyCounter));
		int partyNamelen;
		in.read(rcastc(&partyNamelen), sizeof(partyNamelen));
		_partyName = new char[partyNamelen];
		in.read(rcastc(&_partyName[0]), sizeof(char) * partyNamelen);
	}
}
