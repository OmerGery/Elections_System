#pragma once
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
#include "Citizen.h"
#include <vector>
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
		//ctors/dtors:
		CitizenList() :_head(nullptr), _tail(nullptr), _size(0){}
		~CitizenList();

		bool AddCitizen(Citizen* toadd);
		Citizen* findCitizen(int id) const;
		void getVotes(vector<int> &voteArr) const;
		Citizen* getData(int index) const;
		const int getSize() const { return _size; }
		void PrintList(string countyName) const;

		void saveCitizensList(ostream& out) const;
		void loadCitizensList(istream& in);
	};
}