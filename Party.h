#pragma once
#include "Citizen.h"
#include <iostream>
using namespace std;
namespace votes
{
	class Citizen;
	class Party
	{
	private:
		string _partyName;
		Citizen* _leader;
		int _partySerial;
		static int partyCounter;
	public:
		//ctors/dtors:
		Party() { _leader = nullptr; _partySerial = 0; }
		Party(const string& partyName, Citizen* leader);
		// we don't use a "Party" by-val initing, but we make sure no code will be using default operator '=' or 'copy ctor' by cancelling them. 
		Party& operator=(const Party& other) = delete;
		Party(const Party& other) = delete;

		//getters:
		const string getPartyName() const { return _partyName; }
		const Citizen* getLeader() const { return _leader; }
		const int getPartySerial() const { return _partySerial; }
		const int getPartyCounter() const { return partyCounter; }
		//setters
		void resetCounter() { partyCounter = 0; }
		void setLeader(Citizen* leader) { _leader = leader; }
		//
		friend ostream& operator<<(ostream& os, const Party& party);
		//save/load
		void saveParty(ostream& out) const;
		void loadParty(istream& in);
	};
}
