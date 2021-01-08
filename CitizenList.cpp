#define _CRT_SECURE_NO_WARNINGS
#include "Citizen.h"
#include "CitizenList.h"
#include <string.h>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

namespace votes
{
	
	bool CitizenList::AddCitizen(Citizen* toadd)
	{
		CList.push_back(toadd);
		return true;
	}
	Citizen* CitizenList::getData(int index) const
	{
		list<Citizen*>::const_iterator it = CList.begin();
		advance(it, index);
		return *it;
	}
	void CitizenList::PrintList(string countyName) const
	{
		int size = getSize();
		for (int i = 0; i < size; i++)
		{
			Citizen* c_citizen = this->getData(i);
			cout << *c_citizen;
			cout << " County: " << countyName << endl;
		}
	}
	
	void CitizenList::getVotes(vector<int>& voteArr) const
	{
		int currentVote;
		int size = getSize();
		const Party* PartyVotedTo;
		for (int i = 0; i < size; i++)
		{
			PartyVotedTo = this->getData(i)->getVote();
			if (PartyVotedTo)
				currentVote = PartyVotedTo->getPartySerial();
			else
				currentVote = -1;
			if (currentVote != -1)
			{
				voteArr[currentVote]++;
				voteArr[0]++;
			}
		}
	}
	Citizen* CitizenList::findCitizen(int id) const
	{
		int size = getSize();
		for (int i = 0; i < size; i++)
		{
			if (this->getData(i)->getID() == id)
				return this->getData(i);
		}
		return nullptr;
	}
	void CitizenList::saveCitizensList(ostream& out) const
	{
		int size = getSize();
		out.write(rcastcc(&size), sizeof(size));
		std::list<Citizen*>::const_iterator it;
		for (int i = 0; i <size; i++)
			this->getData(i)->saveCitizen(out);
	}
	void CitizenList::loadCitizensList(istream& in)
	{
		int loadSize = static_cast<int>(CList.size());
		in.read(rcastc(&loadSize), sizeof(loadSize));
		for (int i = 0; i < loadSize; i++)
		{
			Citizen* toadd = new Citizen();
			toadd->loadCitizen(in);
			this->AddCitizen(toadd);
		}
	}
}