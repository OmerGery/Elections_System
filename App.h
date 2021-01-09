
#pragma once
#include "Citizen.h"
#include "Party.h"
#include "Date.h"
 
#include "County.h"
#include "CountyArr.h"
#include "CountyDelegate.h"
#include "SimpleCounty.h"
#include "ComplexCounty.h"
#include <vector>
#include "Sort.h"
#include <string>
#include <fstream>
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
using namespace std;
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
//MIN and MAX - modify the maximum and minimum age for a citizen to vote:
static const int MIN_AGE = 18;
using namespace std;
namespace votes
{
	//A class we use for holding the date, counties and list of parties in the election round. 
	// App is an Abstract class, the classes SimpleApp and RegularApp uses it.
	class App
	{
	protected:
		Date _electionday;
		countyArr CountyArray;
		list <Party*> partyList;

		// Calcing:
		int _partiesSize;
		int _countiesSize;
		vector<vector<int>> _voteCountMatrix;
		vector<vector<float>> _statisticsMatrix;
		vector<vector<int>> _delegatesMatrix;
		vector<vector<int>> _electorsMatrix;
		// Internal usage Calc FUNCS - Private.
		void initVotesMatrix();
		void initDeligatesMatrix();
		void initStatisticsMatrix();
		void initElectorsMatrix();
		void initMatrices();
		void calcVotes();
		
	public:
		//ctors/dtors:
		App();
		App(Date& electionday);
		virtual ~App();

		void AddParty(string partyname, int idCandidate);
		void Vote(int id, int partyNum);
		virtual void AddCounty(string name, int delegatesNum, int type) = 0;
		virtual bool AddCitizen(string name, int id, int year, int countynum) = 0;
		virtual bool AddCitizenAsDelegate(int id, int partynum, int countynum) = 0;
		const int getElectionYear()const { return _electionday.getYear(); }
		void PrintAllCitizens()const;
		void PrintAllParties() const;
		virtual void PrintAllCounties() const = 0;
		virtual void printVotes() = 0;

		virtual void saveApp(ostream& out)const=0;
		void loadApp(istream& in);
		void loadPartyLeaders(istream& in);
		void savePartyLeaders(ostream& out) const;
		void saveCitizenVotes(ostream& out) const;
		void loadCitizenVotes(istream& in);
		void saveCountiesDelegates(ostream& out) const;
		void loadCountiesDelegates(istream& in);

		//party:

		Party* getPListData(int index) const;
		void PrintLeader(int partySerial) const;

		void savePartyList(ostream& out) const;
		void loadPartyList(istream& in);
		/////
	};
}
