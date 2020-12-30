#pragma once
#include "CitizenList.h"
#include "Citizen.h"
#include <iostream>
using namespace std;
using namespace std;
namespace votes
{
	class Party
	{
	private:
		char* _partyName;
		Citizen* _leader;
		int _partySerial;
		static int partyCounter;
	public:
		Party() { _leader = nullptr; _partyName = nullptr; _partySerial = 0; }
		Party(const char* partyName, Citizen* leader);
		Party(const Party& other)=delete;//according to moshe's instructions , we can either implent or delete a copy c'tor.
		Party& operator=(const Party& other) = delete;//according to moshe's instructions , we can either implent or delete a opertor=.
		~Party();
		void resetCounter() { partyCounter = 0; }
		void setLeader(Citizen* leader) { _leader = leader; }
		const char* getPartyName() const { return _partyName; }
		const Citizen* getLeader() const { return _leader; }
		const int getPartySerial() const { return _partySerial; }
		const int getPartyCounter() const { return partyCounter; }
		friend ostream& operator<<(ostream& os, const Party& party);
		void saveParty(ostream& out) const;
		void loadParty(istream& in);
	};
}
