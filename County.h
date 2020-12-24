#pragma once
#include "Party.h"
#include "CitizenList.h"
#include "PartyList.h"
#include "Citizen.h"
#include "CountyDelegateArr.h"
#include "CountyDelegate.h"
#include <iostream>
using namespace std;
namespace votes
{
	struct Elector
	{
		int sumElectors;
		Party* party;
	};
	class County
	{

	protected:
		int _countySerial;
		char* _countyName;
		int _numdelegates;
		CitizenList _citizenAllowed;
		countyDelegateArr CDArr;
		static int countyCounter;

	public:
		County(char* countyName, int numdelegates);
		County();
		~County();
		County(const County& other) = delete;//according to moshe's instructions , we can either implent or delete a copy c'tor.
		County& operator=(const County& other) = delete;//according to moshe's instructions , we can either implent or delete a opertor=.
		void AddCitizen(Citizen* citizen);
		void AddCD(CountyDelegate* delegate);
		CountyDelegate* getDelgate(int delgatePlace)const;
		const char* getCountyName() const { return _countyName; }
		int getCountySerial() const { return _countySerial; }
		const int getdelegatesNum() const { return this->_numdelegates; }
		countyDelegateArr getDelgatesArr() const { return CDArr; };
		const int getDelgatesarrSize()const { return CDArr.getSize(); }
		const int getCountySize()const { return _citizenAllowed.getSize(); };
		friend ostream& operator<<(ostream& os, const County& county);
		Citizen* searchCitizen(int id)const;
		void PrintCitizenList() const;
		void getCountyVotes(int* votearr);
		virtual void GetPartiesElectors (int* partiesVotes,int* countyElectors,int partiesSize)const=0;
		virtual void printWinners(int* Electors,int partiesSize,PartyList* partylist)const = 0;
		//virtual char* GetCountyType();
	};


	class SimpleCounty :public County
	{	
	public:
		SimpleCounty(char* countyName, int numdelegates) : County(countyName, numdelegates) {}
		virtual void GetPartiesElectors (int* partiesVotes,int* countyElectors,int partiesSize)const override
		{
			int max = -1;
			int winningParty = 0;
			for (int i = 1; i <= partiesSize; i++)
			{
				if (max < partiesVotes[i])
				{
					max = partiesVotes[i];
					winningParty = i;
				}
			}
			countyElectors[winningParty] = this->_numdelegates;
		}
		virtual void printWinners(int* Electors, int partiesSize,PartyList* partylist)const override
		{
			for (int i = 1; i < partiesSize; i++)
			{
				if (Electors[i] > 0)
				{
					cout << "The winner is:"; partylist->PrintLeader(i);
					break;
				}
			}
		}
	//	char* GetCountyType();
	};

	class ComplexCounty :public County
	{
	public:
		ComplexCounty(char* countyName, int numdelegates) : County(countyName, numdelegates) {}
		virtual void GetPartiesElectors (int* partiesVotes,int* countyElectors,int partiesSize)const override
		{
			
			
		}
		virtual void printWinners(int* Electors, int partiesSize, PartyList* partylist)const override
		{

			Elector* electorsArray = new Elector[partiesSize + 1];
			for (int i = 1; i <= partiesSize; i++)
			{
				electorsArray[i].sumElectors = Electors[i];
				electorsArray[i].party = partylist->getData(i);
			}

		}
	//	char* GetCountyType();
	};
}
