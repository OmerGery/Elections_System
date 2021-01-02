#pragma once
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
		int _size;
		PListNode* _head;
		PListNode* _tail;
	public:
		//ctors/dtors:
		PartyList() :_head(nullptr), _tail(nullptr), _size(0) {}
		~PartyList() ;

		bool Add(Party* party);
		Party* getData(int index) const;
		const int getSize() const { return _size; }

		void PrintaParty(int partyserial) const;
		void PrintLeader(int partySerial) const;
		
		void savePartyList(ostream& out) const;
		void loadPartyList(istream& in);
		
	};
}


