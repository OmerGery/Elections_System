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

		// calcing

		
		int _partiesSize;
		int _countiesSize;
		int** _voteCountMatrix;
		float** _statisticsMatrix;
		int** _delegatesMatrix;
		struct Elector
		{
			int sumElectors;
			Party* party;
		};
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
		~App() {};
		void AddCounty(char* name, int delegatesNum);
		void AddCitizen(char* name, int id, int year, int countynum);
		void PrintAllCounties() const;
		void PrintAllCitizens()const;
		void PrintAllParties() const;
		void AddParty(char* partyname, int idCandidate);
		void AddCitizenAsDelegate(int id, int partynum, int countynum);
		void Vote(int id, int partyNum);
		void printVotes();
	};
}
