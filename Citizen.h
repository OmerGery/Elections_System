#pragma once
#include "Party.h"
#include <string>
#include <iostream>
#include <fstream>
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
using namespace std;
namespace votes
{
	class Party;
	class Citizen
	{
	private:
		int _id;
		string _name;
		int _year;
		Party* _PartyVotedTo;

	public:
		//ctors/dtors:
		Citizen(const string& name, int id, int year);
		Citizen() { _id = 0;_year = 0; _PartyVotedTo = nullptr; };
		~Citizen();
		// we don't use a "Citizen" by-val initing, but we make sure no code will be using default operator '=' or 'copy ctor' by cancelling them. 
		Citizen(const Citizen& other) = delete;
		Citizen& operator=(const Citizen& other) = delete;

		void vote(Party* party);
		const string getName() const { return _name; }
		const int getID() const { return _id; }
		const int getYear() const { return _year; }
		const Party* getVote()const { return _PartyVotedTo; } ;
		friend ostream& operator<<(ostream& os, const Citizen& citizen);
		//savers/loaders
		void loadCitizen(istream& in);
		void saveCitizen(ostream& out) const;
	};
}
