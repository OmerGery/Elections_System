#define _CRT_SECURE_NO_WARNINGS
#include "Citizen.h"
#include "Party.h"
#include "CitizenList.h"
#include "County.h"
#include "CountyArr.h"
#include "CountyDelegate.h"
#include "PartyList.h"
#include <list>
#include <iterator>
#include <string.h>
#include <iostream>

using namespace std;

namespace votes
{
	PartyList::PartyList()
	{
		PList.push_back(nullptr);
	}
	bool PartyList::Add(Party* party)
	{
		PList.push_back(party);
		return true;
	}
	void PartyList::PrintaParty(int partyserial) const
	{
		Party* party = this->getData(partyserial);
		cout << *party;
	}
	void  PartyList::PrintLeader(int partySerial) const
	{
		cout << this->getData(partySerial)->getLeader()->getName() << endl;
	}
	Party* PartyList::getData(int index) const
	{
		list<Party*>::const_iterator it = PList.begin();
		advance(it, index);
		return *it;
	}
	void PartyList::savePartyList(ostream& out) const
	{
		int size = getSize();
		out.write(rcastcc(&size), sizeof(size));
		std::list<Party*>::const_iterator it;
		for (int i=1; i<=size; i++)
			this->getData(i)->saveParty(out);
		//PListNode* saver = _head;
		//out.write(rcastcc(&this->_size), sizeof(_size));
		/*while (saver != nullptr)
		{
			saver->_data->saveParty(out);
			saver = saver->_next;
		}*/
	}
	void PartyList::loadPartyList(istream& in)
	{
		int loadSize = PList.size();
		in.read(rcastc(&loadSize), sizeof(loadSize));
		for (int i = 0; i < loadSize; i++)
		{
			Party* toadd = new Party();
			toadd->loadParty(in);
			this->Add(toadd);
		}
	}
}