#pragma once
#include "Party.h"
#include <list>
namespace votes
{
	class PartyList
	{
	private:
		list <Party*> PList;
	public:

		bool Add(Party* party);
		Party* getData(int index) const;
		const int getSize() const { return PList.size(); }

		void PrintaParty(int partyserial) const;
		void PrintLeader(int partySerial) const;

		void savePartyList(ostream& out) const;
		void loadPartyList(istream& in);
	};
}


