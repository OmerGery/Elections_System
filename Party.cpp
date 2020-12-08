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
	Party::Party(char* partyName, Citizen * leader)
	{
		int len = strlen(partyName) + 1;
		_partyName = new char[len];
		strcpy(_partyName, partyName);
		_delegateslist = CitizenList();
		_partySerial = ++partyCounter;
		_leader = leader;
		
	}
	bool Party::AddDelegate(Citizen* newdelegate)
	{
		_delegateslist.AddCitizen(newdelegate);
		return true;
	}
}
