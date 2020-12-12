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
	void PartyList::PrintaParty(int partyserial) const
	{
		Party* party = this->getData(partyserial);
		cout << *party;
	}
	PartyList::~PartyList()
	{
		PListNode* deleter = this->_head;
		if (deleter == nullptr)
			return;
		if (deleter->_next == nullptr)
		{
			delete deleter->_data;
			delete deleter;
			return;
		}
		PListNode* runner = deleter;
		while (runner!=nullptr)
		{
			deleter = runner;
			runner = runner->_next;
			delete deleter->_data;
			delete deleter;
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
		{
			if (toReturn == NULL)
				return nullptr;
			toReturn = toReturn->_next;
		}
		return toReturn->_data;
	}
}