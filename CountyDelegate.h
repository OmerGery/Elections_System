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
		//ctors/dtors:
		CountyDelegate(Citizen* delegate,Party* party);
		CountyDelegate() { _delegate = nullptr; _party = nullptr; };
		~CountyDelegate() {};
		// we don't use a "CountyDelegate" by-val initing, but we make sure no code will be using default operator '=' or 'copy ctor' by cancelling them. 
		CountyDelegate(const CountyDelegate& other) = delete;
		CountyDelegate& operator=(const CountyDelegate& other) = delete;

		const int GetPartySerialOfDeligate()const { return _party->getPartySerial(); }
		const string getName() const { return _delegate->getName(); }
		const int getID() const { return _delegate->getID(); }
	};
}
