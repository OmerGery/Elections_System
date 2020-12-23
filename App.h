#pragma once
#include "Citizen.h"
#include "Party.h"
#include "Date.h"
#include "CitizenList.h"
#include "County.h"
#include "CountyArr.h"
#include "CountyDelegate.h"
#include "PartyList.h"

namespace votes
{
	class App
	{
	private:
		Date _electionday;
		countyArr CountyArray;
		PartyList partyList;

		// Calcing:
		int _partiesSize;
		int _countiesSize;
		int** _voteCountMatrix;
		float** _statisticsMatrix;
		int** _delegatesMatrix;
		struct Elector // internal usage in order to sort the candidates.
		{
			int sumElectors;
			Party* party;
		};
		// Internal usage Calc FUNCS - Private.
		Elector* Electors;
		void initVotesMatrix();
		void initDeligatesMatrix();
		void initStatisticsMatrix();
		void initElectors();
		void initMatrices();
		void calcVotes();
		void swap(Elector& a, Elector& b);
		void bubbleSort(Elector Electors[], int size);
		
	public:
		App(Date& electionday);
		~App();
		virtual void AddCounty(char* name, int delegatesNum);
		virtual bool AddCitizen(char* name, int id, int year, int countynum);
		virtual void PrintAllCounties() const;
		void PrintAllCitizens()const;
		void PrintAllParties() const;
		bool AddParty(char* partyname, int idCandidate);
		bool AddCitizenAsDelegate(int id, int partynum, int countynum);
		bool Vote(int id, int partyNum);
		void printVotes();
	};

	class SimpleApp :public App
	{
		SimpleApp(Date& electionDay, int numOfDelegates):App(electionDay)
		{
			 // initalize single-size array of counties and initalize 1 county with size of numOfDelegates
		}
	};
}
