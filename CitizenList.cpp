#define _CRT_SECURE_NO_WARNINGS
#include "Citizen.h"
#include "CitizenList.h"
#include <string.h>
#include <vector>
#include <iostream>
using namespace std;

namespace votes
{
	CitizenList::~CitizenList()
	{
		CzListNode* deleter = this->_head;
		if (deleter == nullptr)
			return;
		if (deleter->_next == nullptr)
		{
			delete deleter->_data;
			delete deleter;
			return;
		}
		CzListNode* runner = deleter;
		while (runner != nullptr)
		{
			deleter = runner;
			runner = runner->_next;
 			delete deleter->_data;
			delete deleter;
		}
	}
	bool CitizenList::AddCitizen(Citizen* toadd)
	{
		CzListNode* newTail = new CzListNode(toadd, nullptr, _tail);
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
		_size++;
		return true;
	}
	Citizen* CitizenList::getData(int index) const
	{
		CzListNode* toReturn = _head;
		if (index < 1 || toReturn == nullptr)
			return nullptr;
		for (int i = 1; i < index; i++)
		{
			if (toReturn == NULL)
				return nullptr;
			toReturn = toReturn->_next;
		}
		return toReturn->_data;
	}
	void CitizenList::PrintList(string countyName) const
	{
		CzListNode* current = _head;
		while (current != nullptr)
		{
			Citizen* C_Citizen = current->_data;
			cout << *(C_Citizen);
			cout << " County: " << countyName << endl;
			
			current = current->_next;
		}
	}
	
	void CitizenList::getVotes(vector<int>& voteArr) const
	{
		CzListNode* current = _head;
		int currentVote;
		const Party* PartyVotedTo;
		while (current != nullptr)
		{
			PartyVotedTo = current->_data->getVote();
			if (PartyVotedTo)
				currentVote = PartyVotedTo->getPartySerial();
			else
				currentVote = -1;
			if (currentVote != -1)
			{
				voteArr[currentVote]++;
				voteArr[0]++;
			}
			current = current->_next;
		}
	}
	Citizen* CitizenList::findCitizen(int id) const
	{
		CzListNode* toReturn = _head;
		while (toReturn!=nullptr)
		{
			if (toReturn->_data->getID() == id)
				return toReturn->_data;
			toReturn = toReturn->_next;
		}
		return nullptr;
	}
	void CitizenList::saveCitizensList(ostream& out) const
	{
		CzListNode* saver =_head;
		out.write(rcastcc(&_size), sizeof(_size));
		while(saver!=nullptr)
		{
			saver->_data->saveCitizen(out);
			saver = saver->_next;
		}
	}
	void CitizenList::loadCitizensList(istream& in)
	{
		int loadSize=_size;
		in.read(rcastc(&loadSize), sizeof(loadSize));
		for(int i=0;i<loadSize;i++)
		{
			Citizen* toadd =new Citizen();
			toadd->loadCitizen(in);
			this->AddCitizen(toadd);
		}
	}

}