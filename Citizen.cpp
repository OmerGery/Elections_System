#define _CRT_SECURE_NO_WARNINGS
#include "Citizen.h"
#include "Party.h"
#include <iostream>
#include <string.h>
using namespace std;
namespace votes
{
	Citizen::Citizen(char* name, int id, int year)
	{
		
		int len = strlen(name)+1;
		_name = new char[len];
		strcpy(_name, name);
		_id = id;
		_year = year;
		_PartyVotedTo = NULL;
	}	
	bool Citizen::vote(Party * party)
	{
		if (_PartyVotedTo!=NULL)
			return false;
		_PartyVotedTo = party;
		return true;
	}
}
