#define _CRT_SECURE_NO_WARNINGS
#include "Citizen.h"
#include "Party.h"
#include <iostream>
#include <string.h>
using namespace std;
namespace votes
{
	Citizen::~Citizen()
	{
		delete[] _name;
	}

	Citizen::Citizen(const char* name, int id, int year)
	{
		
		int len = static_cast<int>(strlen(name)+1);
		_name = new char[len];
		strcpy(_name, name);
		_id = id;
		_year = year;
		_PartyVotedTo = NULL;
	}	
	bool Citizen::vote(Party* party)
	{
		if (_PartyVotedTo!=NULL)
			return false;
		_PartyVotedTo = party;
		return true;
	}
	ostream& operator<<(ostream& os, const Citizen& citizen)
	{
		os << "Name:" << citizen._name << " ID:" << citizen._id << " Born in:" << citizen._year;
		return os;
	}
	void Citizen::saveCitizen(ostream& out) const
	{
		out.write(rcastcc(&_id), sizeof(_id));
		out.write(rcastcc(&_year), sizeof(_year));
		int sizename =static_cast<int>(strlen(_name)+1);
		out.write(rcastcc(&sizename), sizeof(sizename));
		out.write(rcastcc(&_name[0]), sizeof(char) * sizename);
	}
	void Citizen::loadCitizen(istream& in)
	{
		in.read(rcastc(&_id), sizeof(_id));
		in.read(rcastc(&_year), sizeof(_year));
		int sizename=0;
		in.read(rcastc(&sizename), sizeof(sizename));
		_name = new char[sizename];
		in.read(rcastc(&_name[0]), sizename);
	}
}
