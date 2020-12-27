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
	protected:
		Date* _electionday;
		countyArr CountyArray;
		PartyList partyList;

		// Calcing:
		int _partiesSize;
		int _countiesSize;
		int** _voteCountMatrix;
		float** _statisticsMatrix;
		int** _delegatesMatrix;
		int** _electorsMatrix;
		// Internal usage Calc FUNCS - Private.
		void initVotesMatrix();
		void initDeligatesMatrix();
		void initStatisticsMatrix();
		void initElectorsMatrix();
		void initMatrices();
		void calcVotes();
		
	public:
		App(Date* electionday);
		virtual ~App();
		void PrintAllCitizens()const;
		void PrintAllParties() const;
		bool AddParty(char* partyname, int idCandidate);
		bool Vote(int id, int partyNum);
		virtual void AddCounty(char* name, int delegatesNum, bool simple) = 0;
		virtual bool AddCitizen(char* name, int id, int year, int countynum) = 0;
		virtual void PrintAllCounties() const = 0;
		virtual bool AddCitizenAsDelegate(int id, int partynum, int countynum) = 0;
		virtual void printVotes() = 0;
	};
}
