#pragma once
#include "CitizenList.h"
#include "Citizen.h"
namespace votes
{
	class Party
	{
	private:
		char* _partyName;
		Citizen* _leader;
//		CitizenList _delegateslist;
		int _partySerial;
		static int partyCounter;
	public:
		Party(char* partyName, Citizen * leader);
		~Party() 
		{
		//	delete[] _partyName;
		//	delete[] _leaderName;
			//delete[]  _delegatesArr;
		};
//		bool AddDelegate(Citizen* newdelegate);
		const char* getPartyName() const { return _partyName; }
		const Citizen* getLeader() const { return _leader; }
		const int getPartySerial() const { return _partySerial; }
		const int getPartyCounter() const { return partyCounter; }
	//	CitizenList getDelegatesList() const { return _delegateslist; }

	};
}
