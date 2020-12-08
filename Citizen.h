#pragma once
#include "Party.h"
namespace votes
{
	class Party;

	class Citizen
	{
	private:
		int _id;
		char* _name;
		int _year;
		int _PartyVotedToSerial;

	public:
	//	Citizen();
		Citizen(char* name, int id, int year);
		~Citizen() {}; //delete [] _name; 
		bool vote(int partyserial);
		const char* getName() const { return _name; }
		const int getID() const { return _id; }
		const int getYear() const { return _year; }
		const int getVote() const { return _PartyVotedToSerial; }
	};
}
