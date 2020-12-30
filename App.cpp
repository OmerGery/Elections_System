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
#include <iostream>
#include <string.h>
using namespace std;
namespace votes
{
	App::App()
	{
		_electorsMatrix = nullptr;
		_delegatesMatrix = nullptr;
		_statisticsMatrix = nullptr;
		_voteCountMatrix = nullptr;
		_partiesSize = 0;
		_countiesSize = 0;
	}
	App::App(Date& electionday)
	{
		_electorsMatrix=nullptr;
		_delegatesMatrix = nullptr;
		_statisticsMatrix = nullptr;
		_voteCountMatrix = nullptr;
		_partiesSize = 0;
		_countiesSize = 0;
		_electionday = electionday;
	}
	App::~App()
	{
		delete[] this->_electorsMatrix;
		delete[] this->_delegatesMatrix;
		delete[] this->_voteCountMatrix;
		delete[] this->_statisticsMatrix;
	}
	void App::PrintAllParties() const
	{
		if (partyList.getData(1)==nullptr)
		{
			cout << "You haven't entered any parties." << endl;
			return;
		}
		int partiesSize = partyList.getData(1)->getPartyCounter();
		int countiesSize = CountyArray.getSize();
		for (int i = 1; i <= partiesSize; i++)
		{
			partyList.PrintaParty(i);
			for(int j=1;j<=countiesSize;j++)
			CountyArray.printDelegatesOfAParty(j,i);
		}
	}
	void App::PrintAllCitizens()const
	{
		CountyArray.printAllCitizens();
	}
	bool App::AddParty(char* partyname, int idCandidate)
	{

		Citizen* leader=CountyArray.getCitizen(idCandidate);
		if (leader == nullptr)
			return false;
		Party* newparty=new Party(partyname, leader);
		partyList.Add(newparty);
		return true;
	}
	bool App::Vote(int id, int partyNum)
	{
		Citizen* citizen = CountyArray.getCitizen(id);
		if (citizen == nullptr)
			return false;
		Party* PartyVote = partyList.getData(partyNum);
		if (PartyVote == nullptr)
			return false;
		if (citizen->vote(PartyVote) == false)
			return false;
		return true;
	}
	void App::saveApp(ostream& out)const
	{
		_electionday.saveDate(out);
		CountyArray.saveCountyArray(out);
		partyList.savePartyList(out);
		savePartyLeaders(out);
		saveCitizenVotes(out);
		saveCountiesDelegates(out);
	}
	void App::loadApp(istream& in)
	{
		_electionday.loadDate(in);
		CountyArray.loadCountyArray(in);
		partyList.loadPartyList(in);
		loadPartyLeaders(in);
		loadCitizenVotes(in);
		loadCountiesDelegates(in);
	}
	void App::savePartyLeaders(ostream& out) const
	{
		for (int i = 1; i <= partyList.getSize(); i++)
		{
			int leaderID = partyList.getData(i)->getLeader()->getID();
			out.write(rcastcc(&leaderID), sizeof(leaderID));
		}
	}
	
	void App::saveCitizenVotes(ostream& out) const
	{
		for (int i = 1; i <= CountyArray.getSize(); i++)
		{
			County* currentCounty = CountyArray.getCounty(i);
			int citizensInCounty = currentCounty->getCountySize();
			for (int j = 1; j <= citizensInCounty; j++)
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
			for (int j = 1; j <= citizensInCounty; j++)
			{
				Citizen* current = currentCounty->getCitizenByIndex(j);
				int partyvotedto;
				in.read(rcastc(&partyvotedto), sizeof(partyvotedto));
				if (partyvotedto != -1)
				{
					Party* PParty = this->partyList.getData(partyvotedto);
					current->vote(PParty);
				}
			}
		}
	}
	void App::loadPartyLeaders(istream& in)
	{
		for (int i = 1; i <= partyList.getSize(); i++)
		{
			int leaderID;
			in.read(rcastc(&leaderID), sizeof(leaderID));
			Party* current = partyList.getData(i);
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
				Party* currentParty = partyList.getData(partyID);
				CountyDelegate* Delegate = new CountyDelegate(currentDelegate, currentParty);
				CountyArray.addCDToCounty(Delegate, i);
			}
		}
	}

	// CALCS: 

	void App::initVotesMatrix() 
	{
		_partiesSize = partyList.getData(1)->getPartyCounter();
		_countiesSize = CountyArray.getSize();
		_voteCountMatrix = new int* [_countiesSize + 1];
		for (int i = 0; i <= _countiesSize; i++)
		{
			_voteCountMatrix[i] = new int[_partiesSize + 1];
			for (int j = 0; j <= _partiesSize; j++)
				_voteCountMatrix[i][j] = 0;
		}
	}
	void App::initElectorsMatrix()
	{
		_partiesSize = partyList.getData(1)->getPartyCounter();
		_countiesSize = CountyArray.getSize();
		_electorsMatrix = new int* [_countiesSize + 1];
		for (int i = 0; i <= _countiesSize; i++)
		{
			_electorsMatrix[i] = new int[_partiesSize + 1];
			for (int j = 0; j <= _partiesSize; j++)
				_electorsMatrix[i][j] = 0;
		}
	}
	void App::initStatisticsMatrix()
	{
		_statisticsMatrix = new float* [_countiesSize + 1];
		for (int i = 0; i <= _countiesSize; i++)
		{
			_statisticsMatrix[i] = new float[_partiesSize + 1];
			for (int j = 0; j <= _partiesSize; j++)
				_statisticsMatrix[i][j] = 0;
		}
	}
	void App::initDeligatesMatrix()
	{
		_delegatesMatrix = new int* [_countiesSize + 1];
		for (int i = 0; i <= _countiesSize; i++)
		{
			_delegatesMatrix[i] = new int[_partiesSize + 1];
			for (int j = 0; j <= _partiesSize; j++)
				_delegatesMatrix[i][j] = 0;
		}
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
