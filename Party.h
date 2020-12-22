#pragma once
#include "CitizenList.h"
#include "Citizen.h"
#include <iostream>
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
		Party(const char* partyName, Citizen* leader);
		~Party();
		const char* getPartyName() const { return _partyName; }
		const Citizen* getLeader() const { return _leader; }
		const int getPartySerial() const { return _partySerial; }
		const int getPartyCounter() const { return partyCounter; }
		friend ostream& operator<<(ostream& os, const Party& party);
	};
}
