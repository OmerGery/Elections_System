#pragma once
#include "Party.h"
#include <iostream>
using namespace std;
namespace votes
{
	class Party;
	class Citizen
	{
	private:
		int _id;
		char* _name;
		int _year;
		Party* _PartyVotedTo;

	public:
		Citizen(char* name, int id, int year);
		~Citizen(); 
		Citizen(const Citizen& other) = delete;//according to moshe's instructions , we can either implent or delete a copy c'tor.
		Citizen& operator=(const Citizen& other) = delete;//according to moshe's instructions , we can either implent or delete a opertor=.
		bool vote(Party* party);
		const char* getName() const { return _name; }
		const int getID() const { return _id; }
		const int getYear() const { return _year; }
		const Party* getVote()const { return _PartyVotedTo; } ;
		friend ostream& operator<<(ostream& os, const Citizen& citizen);
	};
}
