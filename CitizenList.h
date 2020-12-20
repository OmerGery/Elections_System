#pragma once
#include "Citizen.h"

namespace votes
{
	class Citizen;
	class County;
	class CzListNode
	{
		friend class CitizenList;
	private:
		Citizen* _data;
		CzListNode* _next;
		CzListNode* _prev;
	public:
		CzListNode(Citizen* citizen, CzListNode* next, CzListNode* prev)
		{
			_data = citizen;
			_next = next;
			_prev = prev;
		}
	};

	class CitizenList
	{
	private:
		int _size;
		CzListNode* _head;
		CzListNode* _tail;
	public:
		CitizenList() :_head(nullptr), _tail(nullptr), _size(0){}
		~CitizenList();
		bool AddCitizen(Citizen* toadd);
		void PrintList() const;
		Citizen* findCitizen(int id) const;
		void getVotes(int* voteArr) const;
		const int getSize() const { return _size; }
	};
}