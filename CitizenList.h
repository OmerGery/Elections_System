#pragma once
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
#include "Citizen.h"
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
using namespace std;
namespace votes
{
	class Citizen;
	class CitizenList
	{
	private:
		list <Citizen*> CList;
	public:
		//ctors/dtors:

		bool AddCitizen(Citizen* toadd);
		Citizen* findCitizen(int id) const;
		void getVotes(vector<int> &voteArr) const;
		Citizen* getData(int index) const;
		const int getSize() const { return CList.size(); }
		void PrintList(string countyName) const;

		void saveCitizensList(ostream& out) const;
		void loadCitizensList(istream& in);


	};
}