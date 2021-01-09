#define _CRT_SECURE_NO_WARNINGS
#include "Citizen.h"
#include "Party.h"
#include <iostream>
 
using namespace std;
namespace votes
{
	Citizen::~Citizen()
	{
	}

	Citizen::Citizen(const string& name, int id, int year)
	{	// we check the age in the app class.
		string errorName;
		if (id < 100000000 || id > 999999999)
			throw (errorName = "The ID is invalid, must be 9 digits length");
		_name=name;
		_id = id;
		_year = year;
		_PartyVotedTo = nullptr;
	}	
	void Citizen::vote(Party* party)
	{
		string errorName;
		if (_PartyVotedTo!=nullptr)
			throw (errorName = "Don't Cheat! this citizen already VOTED!");
		_PartyVotedTo = party;
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
		int sizename =static_cast<int>(_name.size());
		out.write(rcastcc(&sizename), sizeof(sizename));
		out.write(rcastcc(&_name[0]), sizeof(char) * sizename);
	}
	void Citizen::loadCitizen(istream& in)
	{
		in.read(rcastc(&_id), sizeof(_id));
		in.read(rcastc(&_year), sizeof(_year));
		int sizename=0;
		in.read(rcastc(&sizename), sizeof(sizename));
		_name.resize(sizename);
		in.read(rcastc(&_name[0]), sizename);
	}
}
