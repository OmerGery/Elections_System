#define _CRT_SECURE_NO_WARNINGS
#include "Citizen.h"
#include "Party.h"
#include "CitizenList.h"
#include "County.h"
#include "CountyArr.h"
#include "CountyDelegate.h"
#include "PartyList.h"
#include "App.h"
#include "Sort.h"
#include <vector>
#include <iostream>
#include <string.h>
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
		_partiesSize = 0;
		_countiesSize = 0;
		_electionday = electionday;
	}
	App::~App()
	{
	}
	void App::PrintAllParties() const
	{
		if (getPListData(1)==nullptr)
		{
			cout << "You haven't entered any parties." << endl;
			return;
		}
		int partiesSize = getPListData(1)->getPartyCounter();
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
	bool App::AddParty(string partyname, int idCandidate)
	{
		string errorName;
		Citizen* leader=CountyArray.getCitizen(idCandidate);
		if (leader == nullptr)
			throw (errorName = "This Party leader ID doesn't match any Citizen's ID");
		Party* newparty=new Party(partyname, leader);
		AddToPlist(newparty);
		return true;
	}
	bool App::Vote(int id, int partyNum)
	{
		string errorName;
		Citizen* citizen = CountyArray.getCitizen(id);
		if (citizen == nullptr)
			throw (errorName = "Citizen ID is invalid");
		Party* PartyVote = getPListData(partyNum);
		if (PartyVote == nullptr)
			throw (errorName = "Party Serial number is invalid");
		if (citizen->vote(PartyVote) == false)
			throw (errorName = "This citizen has already voted");
		return true;
	}
	bool App::printVotes()
	{
		string errorName;
		if (getPListSize() < 1)
			throw (errorName = "Can't show elections results, need to add parties before");
		cout << _electionday;
		calcVotes();
		return true;
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
		for (int i = 1; i <= getPListSize(); i++)
		{
			int leaderID = getPListData(i)->getLeader()->getID();
			out.write(rcastcc(&leaderID), sizeof(leaderID));
		}
	}
	
	void App::saveCitizenVotes(ostream& out) const
	{
		for (int i = 1; i <= CountyArray.getSize(); i++)
		{
			County* currentCounty = CountyArray.getCounty(i);
			int citizensInCounty = currentCounty->getCountySize();
			for (int j = 1; j < citizensInCounty; j++) // was <= , don't know why, there's a correletion problem and there are a lot of things we need to change in order it would make sense with list type
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
			for (int j = 1; j < citizensInCounty; j++) // was <= , don't know why, there's a correletion problem and there are a lot of things we need to change in order it would make sense with list type
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
		for (int i = 1; i <= getPListSize(); i++)
		{
			int leaderID;
			in.read(rcastc(&leaderID), sizeof(leaderID));
			Party* current = getPListData(i);
			Citizen* currentLeader = CountyArray.getCitizen(leaderID);
			current->setLeader(currentLeader);
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
				CountyArray.addCDToCounty(Delegate, i);
			}
		}
	}
	//Party:
	bool App::AddToPlist(Party* party)
	{
		partyList.push_back(party);
		return true;
	}
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
		int size = getPListSize();
		out.write(rcastcc(&size), sizeof(size));
		std::list<Party*>::const_iterator it;
		for (int i = 1; i <= size; i++)
			getPListData(i)->saveParty(out);
	}
	void App::loadPartyList(istream& in)
	{
		int loadSize = static_cast<int>(partyList.size());
		in.read(rcastc(&loadSize), sizeof(loadSize));
		for (int i = 0; i < loadSize; i++)
		{
			Party* toadd = new Party();
			toadd->loadParty(in);
			AddToPlist(toadd);
		}
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
