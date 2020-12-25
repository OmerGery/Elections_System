#pragma once
#include "Party.h"
#include "CitizenList.h"
#include "PartyList.h"
#include "Citizen.h"
#include "CountyDelegateArr.h"
#include "CountyDelegate.h"
#include "Sort.h"
#include <iostream>
using namespace std;
namespace votes
{
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
		County(const char* countyName, int numdelegates);
		County();
		~County();
		void resetCounter() { countyCounter = 0; }
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
		virtual void GetPartiesElectors(float* statisticsArray, int* countyElectors, int partiesSize)const=0;
		virtual void sortAndPrintWinners(int* voteCount,int* Electors,int partiesSize,PartyList* partylist)const = 0;
		virtual void printCountyType() const=0;
	};

	

	class SimpleCounty :public County
	{	
	public:
		SimpleCounty(const char* countyName, int numdelegates) : County(countyName, numdelegates) {}
		virtual void GetPartiesElectors (float* statisticsArray,int* countyElectors,int partiesSize)const override
		{
			float max = -1;
			int winningParty = 0;
			for (int i = 1; i <= partiesSize; i++)
			{
				if (max < statisticsArray[i])
				{
					max = statisticsArray[i];
					winningParty = i;
				}
			}
			countyElectors[winningParty] = this->_numdelegates;
		}
		virtual void sortAndPrintWinners(int* voteCount,int* Electors, int partiesSize,PartyList* partylist)const override
		{
			for (int i = 1; i <= partiesSize; i++)
			{
				if (Electors[i] > 0)
				{
					cout << "The winner in this county is:"; partylist->PrintLeader(i);
					break;
				}
			}
		}
		virtual void printCountyType() const override
		{
			cout << " County Type: Simple " << endl;
		}
	};

	class ComplexCounty :public County
	{
	public:
		ComplexCounty(const char* countyName, int numdelegates) : County(countyName, numdelegates) {}
		virtual void GetPartiesElectors (float* statisticsArray,int* countyElectors,int partiesSize)const override
		{
			int place = 0, tempElectorsNum = 0, remainingDelegates=0, max=-1;
			for (int i = 1; i <= partiesSize; i++)
			{
				countyElectors[i] = static_cast<int>(_numdelegates * statisticsArray[i]);
				if (countyElectors[i] > max)
				{
					max = countyElectors[i];
					place = i;
				}
				tempElectorsNum += countyElectors[i];
			}
			remainingDelegates = _numdelegates - tempElectorsNum;
			countyElectors[place] += remainingDelegates;
			
		}
		virtual void sortAndPrintWinners(int* voteCount,int* Electors, int partiesSize, PartyList* partylist)const override
		{

			int size = partiesSize + 1;
			Elector* electorsArray = new Elector[size];
			electorsArray[0].sumElectors = -1;
			for (int i = 1; i <= partiesSize; i++)
			{
				electorsArray[i].sumElectors = Electors[i];
				electorsArray[i].party = partylist->getData(i);
			}
			
			bubbleSort(electorsArray, size);
			for (int i = partiesSize; i > 0; i--)
				cout << "#" << partiesSize - i + 1 << ". " << electorsArray[i].party->getLeader()->getName() << " Has got: "
					<< electorsArray[i].sumElectors << " Electors and his party got " <<
					voteCount[electorsArray[i].party->getPartySerial()] << " votes" << endl; 
		}
		virtual void printCountyType() const override
		{
			cout << " County Type: Split " << endl;
		}
	};

}
