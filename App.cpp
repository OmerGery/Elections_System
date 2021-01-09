#define _CRT_SECURE_NO_WARNINGS
#include "Citizen.h"
#include "Party.h"
#include "CitizenList.h"
#include "County.h"
#include "CountyArr.h"
#include "CountyDelegate.h"
#include "App.h"
//#include "Sort.h"
#include <vector>
#include <iostream>
 
using namespace std;
namespace votes
{
	App::App()
	{
		partyList.push_back(nullptr);
		_partiesSize = 0;
		_countiesSize = 0;
	}
	App::App(Date& electionday)
	{
		partyList.push_back(nullptr);
		_partiesSize = 0;
		_countiesSize = 0;
		_electionday = electionday;
	}
	App::~App()
	{

	}
	void App::PrintAllParties() const
	{
		string errorName;
		int partiesSize =static_cast<int>(partyList.size());
		if (partiesSize<=1)
			throw (errorName = "You haven't entered any parties.");
		list<Party*>::const_iterator it = partyList.begin();
		advance(it, 1);
		int countiesSize = CountyArray.getSize();
		for (int i = 1; i <= partiesSize; i++)
		{
			PrintaParty(i);
			for(int j=1;j<=countiesSize;j++)
			CountyArray.printDelegatesOfAParty(j,i);
		}
	}
	void App::PrintAllCitizens()const
	{
		CountyArray.printAllCitizens();
	}
	void App::AddParty(string partyname, int idCandidate)
	{
		string errorName;
		Citizen* leader=CountyArray.getCitizen(idCandidate);
		if (leader == nullptr)
			throw (errorName = "This Party leader ID doesn't match any Citizen's ID");
		Party* newparty=new Party(partyname, leader);
		if (!newparty)
			throw (errorName = "Memory Allocation failed.");
		partyList.push_back(newparty);
	}
	void App::Vote(int id, int partyNum)
	{
		string errorName;
		Citizen* citizen = CountyArray.getCitizen(id);
		if (citizen == nullptr)
			throw (errorName = "A Citizen with this ID doesn't exist.");
		Party* PartyVote = getPListData(partyNum);
		if (PartyVote == nullptr)
			throw (errorName = "Party Serial number is invalid");
		citizen->vote(PartyVote);
	}
	void App::printVotes()
	{
		string errorName;
		if (static_cast<int>(partyList.size() - 1) < 1)
			throw (errorName = "Can't show elections results, need to add parties before");
		cout << _electionday;
		calcVotes();
	}
	void App::saveApp(ostream& out)const
	{
		_electionday.saveDate(out);
		CountyArray.saveCountyArray(out);
		savePartyList(out);
		savePartyLeaders(out);
		saveCitizenVotes(out);
		saveCountiesDelegates(out);
	}
	void App::loadApp(istream& in)
	{
		_electionday.loadDate(in);
		CountyArray.loadCountyArray(in);
		loadPartyList(in);
		loadPartyLeaders(in);
		loadCitizenVotes(in);
		loadCountiesDelegates(in);
	}
	void App::savePartyLeaders(ostream& out) const
	{
		list<Party*>::const_iterator runner = partyList.begin();
		advance(runner, 1);
		for (int i = 1; i <= static_cast<int>(partyList.size() - 1); i++)
		{
			int leaderID = (*runner)->getLeader()->getID();
			out.write(rcastcc(&leaderID), sizeof(leaderID));
			advance(runner, 1);
		}
	}
	void App::saveCitizenVotes(ostream& out) const
	{
		for (int i = 1; i <= CountyArray.getSize(); i++)
		{
			County* currentCounty = CountyArray.getCounty(i);
			int citizensInCounty = currentCounty->getCountySize();
			for (int j = 0; j < citizensInCounty; j++) 
			{
				Citizen* current=currentCounty->getCitizenByIndex(j);
				int partyvotedto=-1;
				const Party* pParty = current->getVote();
				if(pParty)
					partyvotedto=pParty->getPartySerial();
				out.write(rcastcc(&partyvotedto), sizeof(partyvotedto));
			}
		}
	}
	void App::loadCitizenVotes(istream& in)
	{
		for (int i = 1; i <= CountyArray.getSize(); i++)
		{
			County* currentCounty = CountyArray.getCounty(i);
			int citizensInCounty = currentCounty->getCountySize();
			for (int j = 0; j < citizensInCounty; j++) 
			{
				Citizen* current = currentCounty->getCitizenByIndex(j);
				int partyvotedto;
				in.read(rcastc(&partyvotedto), sizeof(partyvotedto));
				if (partyvotedto != -1)
				{
					Party* PParty = getPListData(partyvotedto);
					current->vote(PParty);
				}
			}
		}
	}
	void App::loadPartyLeaders(istream& in)
	{
		list<Party*>::const_iterator partyRunner = partyList.begin();
		advance(partyRunner, 1);
		for (int i = 1; i <= static_cast<int>(partyList.size() - 1); i++)
		{
			int leaderID;
			in.read(rcastc(&leaderID), sizeof(leaderID));
			Party* current = *partyRunner;
			Citizen* currentLeader = CountyArray.getCitizen(leaderID);
			current->setLeader(currentLeader);
			advance(partyRunner, 1);
		}
	}
	void App::saveCountiesDelegates(ostream& out) const
	{
		for (int i = 1; i <= CountyArray.getSize(); i++)
		{
			County* currentCounty = CountyArray.getCounty(i);
			int delegatesInCounty = currentCounty->getDelgatesarrSize();
			out.write(rcastcc(&delegatesInCounty), sizeof(delegatesInCounty));
			for (int j = 0; j < delegatesInCounty; j++)
			{
				CountyDelegate* currentDelegate = currentCounty->getDelgate(j);
				int delegateID = currentDelegate->getID();
				out.write(rcastcc(&delegateID), sizeof(delegateID));
				int partyID = currentDelegate->GetPartySerialOfDeligate();
				out.write(rcastcc(&partyID), sizeof(partyID));
			}
		}
	}
	void App::loadCountiesDelegates(istream& in) 
	{
		string errorName;
		for (int i = 1; i <= CountyArray.getSize(); i++)
		{
			County* currentCounty = CountyArray.getCounty(i);
			int delegatesInCounty = 0;
			in.read(rcastc(&delegatesInCounty), sizeof(delegatesInCounty));
			for (int j = 0; j < delegatesInCounty; j++)
			{
				int delegateID;
				in.read(rcastc(&delegateID), sizeof(delegateID));
				Citizen* currentDelegate = CountyArray.getCitizen(delegateID);
				int partyID;
				in.read(rcastc(&partyID), sizeof(partyID));
				Party* currentParty = getPListData(partyID);
				CountyDelegate* Delegate = new CountyDelegate(currentDelegate, currentParty);
				if (!Delegate)
					throw (errorName = "Memory Allocation failed.");
				CountyArray.addCDToCounty(Delegate, i);
			}
		}
	}
	//Party:
	void App::PrintaParty(int partyserial) const
	{
		Party* party = getPListData(partyserial);
		cout << *party;
	}
	void  App::PrintLeader(int partySerial) const
	{
		cout << getPListData(partySerial)->getLeader()->getName() << endl;
	}
	Party* App::getPListData(int index) const
	{
		list<Party*>::const_iterator it = partyList.begin();
		advance(it, index);
		return *it;
	}
	void App::savePartyList(ostream& out) const
	{
		int size = static_cast<int>(partyList.size() - 1);
		out.write(rcastcc(&size), sizeof(size));
		std::list<Party*>::const_iterator PListRunner= partyList.begin();
		advance(PListRunner, 1);
		for (int i = 1; i <= size; i++)
		{
			(*PListRunner)->saveParty(out);
			advance(PListRunner, 1);
		}
	}
	void App::loadPartyList(istream& in)
	{
		string errorName;
		int loadSize = static_cast<int>(partyList.size());
		in.read(rcastc(&loadSize), sizeof(loadSize));
		for (int i = 0; i < loadSize; i++)
		{
			Party* toadd = new Party();
			if (!toadd)
				throw (errorName = "Memory Allocation failed.");
			toadd->loadParty(in);
			partyList.push_back(toadd);
		}
	}
	bool App::AddCitizen(string name, int id, int year, int countynum)
	{
		string errorName;
		if (year > getElectionYear() - MIN_AGE)
			throw (errorName = "Year is invalid, in order to vote, one must need to be at least 18 years old");
		Citizen* citizen = CountyArray.getCitizen(id);
		if (citizen != nullptr)
			throw (errorName = "Citizen ID already exists");
		return true;
	}
	/////////
	// CALCS: 

	void App::initVotesMatrix()
	{
		_partiesSize = getPListData(1)->getPartyCounter();
		_countiesSize = CountyArray.getSize();
		_voteCountMatrix.assign(_countiesSize+1, vector < int >(_partiesSize+1, 0));
	}
	void App::initElectorsMatrix()
	{
		_electorsMatrix.assign(_countiesSize + 1, vector < int >(_partiesSize + 1, 0));
	}
	void App::initStatisticsMatrix()
	{
		_statisticsMatrix.assign(_countiesSize + 1, vector <float >(_partiesSize + 1, 0));
	}
	void App::initDeligatesMatrix()
	{
		_delegatesMatrix.assign(_countiesSize+1, vector < int >(_partiesSize+1, 0));
	}
	void App::initMatrices()
	{
		initVotesMatrix();
		initStatisticsMatrix();
		initDeligatesMatrix();
		initElectorsMatrix();
	}
	void App::calcVotes()
	{
		int i, j, max = 1, partyNum = -1, place = 1, tempDelegatesNum = 0, remainingDelegates;
		initMatrices();
		// fill the matrices with the citizen votes 
		CountyArray.getCitizensVotes(_voteCountMatrix, _countiesSize, _partiesSize);
		for (i = 1; i <= _countiesSize; i++)
		{
			int totalCitizensInCounty = CountyArray.getCountySize(i);
			if (totalCitizensInCounty != 0)
				_statisticsMatrix[i][0] = static_cast<float>(_voteCountMatrix[i][0]) / static_cast<float>(totalCitizensInCounty);
			for (j = 1; j <= _partiesSize; j++)
			{
				if (_voteCountMatrix[i][0] != 0)
					_statisticsMatrix[i][j] = static_cast<float>(_voteCountMatrix[i][j]) / static_cast<float>(_voteCountMatrix[i][0]);
			}
		}
		for (i = 1; i <= _countiesSize; i++)
		{
			int countyDelegatesNum = CountyArray.getDelegatesNum(i);
			max = 0;
			tempDelegatesNum = 0;
			for (j = 1; j <= _partiesSize; j++)
			{
				_delegatesMatrix[i][j] = static_cast<int>(countyDelegatesNum * _statisticsMatrix[i][j]);
				if (_delegatesMatrix[i][j] > max)
					place = j;
				tempDelegatesNum += _delegatesMatrix[i][j];
			}
			remainingDelegates = countyDelegatesNum - tempDelegatesNum;
			_delegatesMatrix[i][place] += remainingDelegates;
		}
		CountyArray.getElectors(_electorsMatrix, _statisticsMatrix, _partiesSize);
	}
}
