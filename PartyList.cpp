#define _CRT_SECURE_NO_WARNINGS
#include "Citizen.h"
#include "Party.h"
#include "CitizenList.h"
#include "County.h"
#include "CountyArr.h"
#include "CountyDelegate.h"
#include "PartyList.h"
#include <string.h>
#include <iostream>


using namespace std;

namespace votes
{
	bool PartyList::Add(Party * party)
	{
		PListNode* newTail = new PListNode(party, nullptr, _tail);
		if (_head == nullptr)
		{
			_head = newTail;
			_tail = newTail;
		}
		else
		{
			_tail->_next = newTail;
			_tail = newTail;
		}
		return true;
	}
	void PartyList::addDelegateToParty(Citizen* delegate, int partynum)
	{
		Party* party = getData(partynum);
		party->AddDelegate(delegate);
	}
	void PartyList::PrintAllList() const
	{
		PListNode* current = _head;
		while (current != nullptr)
		{
			cout << current->_data->getPartySerial() << " " << current->_data->getPartyName() << " " << current->_data->getLeader()->getName() << endl;
			(current->_data->getDelegatesList()).PrintList();
			current = current->_next;
		}
	}
	void  PartyList::PrintLeader(int partySerial) const
	{
		cout << this->getData(partySerial)->getLeader()->getName() << endl;
	}
	Party* PartyList::getData(int index) const
	{
		PListNode* toReturn = _head;
		for (int i = 1; i < index; i++)
			toReturn = toReturn->_next;

		return toReturn->_data;
	}
}