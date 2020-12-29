#pragma once
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
#include "Citizen.h"
#include <iostream>
#include <fstream>
using namespace std;
namespace votes
{
	class Citizen;
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
		void PrintList(char* countyName) const;
		Citizen* findCitizen(int id) const;
		void getVotes(int* voteArr) const;
		const int getSize() const { return _size; }
		void saveCitizensList(ostream& out) const;
		void loadCitizensList(istream& in);
	};
}