#define _CRT_SECURE_NO_WARNINGS
#include "Citizen.h"
#include "Party.h"
#include "County.h"
#include "CountyDelegate.h"
#include "App.h"
#include <vector>
#include <iostream>
using namespace std;
namespace votes
{
	App::App(Date& electionday)
	{
		CountyArray.push_back(nullptr);
		partyList.push_back(nullptr);
		_partiesSize = 0;
		_countiesSize = 0;
		_electionday = electionday;
	}
	App::~App()
	{
		CountyArray.at(0)->resetCounter();
		for (int i = 1; i < CountyArray.size(); i++)
			delete CountyArray.at(i);
		list<Party*>::const_iterator itr = partyList.begin();
		itr++;
		list<Party*>::const_iterator end = partyList.end();
		for (; itr != end; ++itr)
			delete* itr;
	}
	void App::PrintAllParties() const
	{
		string errorName;
		int partiesSize =static_cast<int>(partyList.size());
		if (partiesSize<=1)
			throw (errorName = "You haven't entered any parties.");
		int countiesSize = getSize();
		list<Party*>::const_iterator itr = partyList.begin();
		itr++;
		list<Party*>::const_iterator end = partyList.end();	
		for (int i = 1; itr != end; ++itr,i++)
		{
			cout << *(*itr);
			for (int j = 1; j <= countiesSize; j++)
				printDelegatesOfAParty(j, i);
		}
	}
	void App::PrintAllCitizens()const
	{
			for (int i = 1; i < CountyArray.size(); i++)
				CountyArray[i]->PrintCitizenList();
	}
	void App::AddParty(string partyname, int idCandidate)
	{
		string errorName;
		Citizen* leader=getCitizen(idCandidate);
		if (leader == nullptr)
			throw (errorName = "This Party leader ID doesn't match any Citizen's ID");
		Party* newparty = new Party(partyname, leader);
		partyList.push_back(newparty);
	}
	void App::Vote(int id, int partyNum)
	{
		string errorName;
		Citizen* citizen = getCitizen(id);
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
		saveCountyArray(out);
		savePartyList(out);
		savePartyLeaders(out);
		saveCitizenVotes(out);
		saveCountiesDelegates(out);
	}
	void App::loadApp(istream& in)
	{
		_electionday.loadDate(in);
		loadCountyArray(in);
		loadPartyList(in);
		loadPartyLeaders(in);
		loadCitizenVotes(in);
		loadCountiesDelegates(in);
	}

	///
// CALCS: 

	void App::initVotesMatrix()
	{
		_partiesSize = static_cast<int>(this->partyList.size() - 1);
		_countiesSize = getSize();
		_voteCountMatrix.assign(_countiesSize + 1, vector < int >(_partiesSize + 1, 0));
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
		_delegatesMatrix.assign(_countiesSize + 1, vector < int >(_partiesSize + 1, 0));
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
		getCitizensVotes(_voteCountMatrix, _countiesSize, _partiesSize);
		for (i = 1; i <= _countiesSize; i++)
		{
			int totalCitizensInCounty = getCountySize(i);
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
			int countyDelegatesNum = getDelegatesNum(i);
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
		getElectors(_electorsMatrix, _statisticsMatrix, _partiesSize);
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
		for (int i = 1; i <= getSize(); i++)
		{
			County* currentCounty = getCounty(i);
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
		for (int i = 1; i <= getSize(); i++)
		{
			County* currentCounty = getCounty(i);
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
			Citizen* currentLeader = getCitizen(leaderID);
			current->setLeader(currentLeader);
			advance(partyRunner, 1);
		}
	}
	void App::saveCountiesDelegates(ostream& out) const
	{
		for (int i = 1; i <= getSize(); i++)
		{
			County* currentCounty = getCounty(i);
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
		for (int i = 1; i <= getSize(); i++)
		{
			County* currentCounty = getCounty(i);
			int delegatesInCounty = 0;
			in.read(rcastc(&delegatesInCounty), sizeof(delegatesInCounty));
			for (int j = 0; j < delegatesInCounty; j++)
			{
				int delegateID;
				in.read(rcastc(&delegateID), sizeof(delegateID));
				Citizen* currentDelegate = getCitizen(delegateID);
				int partyID;
				in.read(rcastc(&partyID), sizeof(partyID));
				Party* currentParty = getPListData(partyID);
				CountyArray[i]->AddCD(currentDelegate, currentParty);
			}
		}
	}
	//Party:

	void  App::PrintLeader(int partySerial) const
	{
		cout << getPListData(partySerial)->getLeader()->getName() << endl;
	}
	Party* App::getPListData(int index) const
	{
		if (index >= partyList.size())
			return nullptr;
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
			toadd->loadParty(in);
			partyList.push_back(toadd);
		}
	}
	void App::AddCitizen(string name, int id, int year, int countynum)
	{
		string errorName;
		if (year > getElectionYear() - MIN_AGE)
			throw (errorName = "Year is invalid, in order to vote, one must need to be at least 18 years old");
		Citizen* citizen = getCitizen(id);
		if (citizen != nullptr)
			throw (errorName = "Citizen ID already exists");
	}

	void App::printCountyName(int countyNum) const
	{
		cout << (*CountyArray[countyNum]).getCountyName() << endl;
	}
	void App::printWinnersOfCounty(vector<int>& voteCount, vector<int>& electors, int countyNum, int partiesSize, list <Party*> partylist) const
	{
		CountyArray[countyNum]->sortAndPrintWinners(voteCount, electors, partiesSize, partylist);
	}

	void App::printDelegatesNum(int countyNum) const
	{
		cout << (*CountyArray[countyNum]).getdelegatesNum() << endl;
	}
	const int App::getDelegatesNum(int countyNum) const
	{
		return (*CountyArray[countyNum]).getdelegatesNum();
	}
	const int App::getDelegatesArrSize(int countyNum) const
	{
		return CountyArray[countyNum]->getDelgatesarrSize();
	}
	void App::getCitizensVotes(vector<vector<int>>& votesMatrix, int counties, int parties)const
	{

		for (int i = 1; i <= counties; i++)
		{
			County* current = CountyArray[i];
			current->getCountyVotes(votesMatrix[i]);
			for (int j = 0; j <= parties; j++)
			{
				votesMatrix[0][j] += votesMatrix[i][j];
			}
		}
	}
	void App::getElectors(vector<vector<int>>& electorsMatrix, vector<vector<float>>& statsMatrix, int partiesSize)
	{

		for (int i = 1; i < CountyArray.size(); i++)
		{
			County* current = CountyArray[i];
			current->GetPartiesElectors(statsMatrix[i], electorsMatrix[i], partiesSize);
			for (int j = 1; j <= partiesSize; j++)
			{
				electorsMatrix[0][j] += electorsMatrix[i][j];
			}
		}
	}
	const int App::getCountySize(int county)const
	{
		County* tofind = CountyArray[county];
		return tofind->getCountySize();
	}
	void App::addCitizenToCounty(Citizen* citizen, int countynum)
	{
		CountyArray[countynum]->AddCitizen(citizen);
	}

	Citizen* App::getCitizen(int id)
	{
		for (int i = 1; i < CountyArray.size(); i++)
		{
			County* current = CountyArray[i];
			Citizen* search = current->searchCitizen(id);
			if (search)
				return search;
		}
		return nullptr;
	}
	void App::printDelegatesOfAParty(int countynum, int partynum) const
	{
		County* current_C = CountyArray[countynum];
		int totalDeligatesinCounty = CountyArray[countynum]->getDelgatesarrSize();
		int counter = 0;
		for (int i = 0; i < totalDeligatesinCounty; i++)
		{
			CountyDelegate* current = current_C->getDelgate(i);
			if ((*current).GetPartySerialOfDeligate() == partynum)
			{
				counter++;
				if (counter > 1)
					cout << ",";
				if (counter == 1)
					cout << "The Delegates from this Party in The County " << (*this->CountyArray[countynum]).getCountyName() << " are: ";
				cout << (*current).getName();
			}
		}
		if (counter > 0)
			cout << "." << endl;
	}
	bool App::searchDelegate(int id) const
	{
		for (int k = 1; k < CountyArray.size(); k++)
		{
			County* current_C = CountyArray[k];
			int totalDeligatesinCounty = CountyArray[k]->getDelgatesarrSize();
			for (int i = 0; i < totalDeligatesinCounty; i++)
			{
				CountyDelegate* current = current_C->getDelgate(i);
				if (current->getID() == id)
					return true;
			}
		}
		return false;
	}
	void App::saveCountyArray(ostream& out) const
	{
		int size = CountyArray.size();
		out.write(rcastcc(&size), sizeof(size));
		for (int i = 1; i < size; ++i)
			CountyArray[i]->saveCounty(out);
	}
	void App::loadCountyArray(istream& in)
	{
		string errorName;
		int loadedCounites;
		in.read(rcastc(&loadedCounites), sizeof(loadedCounites));
		for (int i = 1; i < loadedCounites; ++i)
		{
			int type;
			in.read(rcastc(&type), sizeof(type));
			County* county = nullptr;
			if (type == SIMPLE)
			{
				county = new SimpleCounty();
			}
			else
			{
				county = new ComplexCounty();
			}
			county->loadCounty(in);
			CountyArray.push_back(county);
		}
	}
}
