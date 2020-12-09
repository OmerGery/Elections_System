#pragma once
#include "Party.h"
namespace votes
{
	class PListNode
	{
		friend class PartyList;
	private:
		Party* _data;
		PListNode* _next;
		PListNode* _prev;
	public:
		PListNode(Party* Party, PListNode* next, PListNode* prev)
		{
			_data = Party;
			_next = next;
			_prev = prev;
		}
	};

	class PartyList
	{
	private:
		PListNode* _head;
		PListNode* _tail;
	public:
		PartyList() :_head(nullptr), _tail(nullptr) {}
		~PartyList() {};
		bool Add(Party* party);
		void addDelegateToParty(Citizen* delegate, int partynum);
		Party* getData(int index) const;
		void PrintaParty(int partyserial) const;
		void PrintLeader(int partySerial) const;
		
	};
}


