#pragma once
#include "Citizen.h"
#include "Party.h"
namespace votes
{
	class CountyDelegate
	{
	private:
		Citizen* _delegate;
		Party* _party;
		
	public:
		CountyDelegate(Citizen* delegate,Party* party);
		CountyDelegate() { _delegate = nullptr; _party = nullptr; };
		~CountyDelegate() {};
		const int GetPartySerialOfDeligate()const { return _party->getPartySerial(); }
		const char* getName() const { return _delegate->getName(); }
		const int getID() const { return _delegate->getID(); }
	};
}
