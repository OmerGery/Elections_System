#define _CRT_SECURE_NO_WARNINGS
#include "Citizen.h"
#include "Party.h"
#include "CitizenList.h"
#include "County.h"
#include "CountyArr.h"
#include "CountyDelegate.h"
#include "PartyList.h"
#include "App.h"
#include <iostream>
#include <string.h>
using namespace std;
namespace votes
{

	App::App(Date & electionday)
	{
		Electors = nullptr;
		_delegatesMatrix = nullptr;
		_statisticsMatrix = nullptr;
		_voteCountMatrix = nullptr;
		_partiesSize = 0;
		_countiesSize = 0;
		_electionday = electionday;
	}
	App::~App()
	{
		delete[] Electors;
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
	void App::PrintAllCounties ()const
	{
		if (CountyArray.getSize() == 0)
		{
			cout << "You haven't entered any counties." << endl;
			return;
		}
		CountyArray.printAllCounties();
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
	void App::AddCounty(char* name, int delegatesNum)
	{
		County* county = new County(name, delegatesNum);
		CountyArray.insert(county);
	}
	bool App::AddCitizen(char* name, int id, int year, int countynum)
	{
		if (countynum > CountyArray.getSize() || countynum <= 0)
			return false;
		Citizen* citizen = CountyArray.getCitizen(id);
		if (citizen != nullptr)
			return false;
		Citizen* newCitizen= new Citizen(name, id, year);
		CountyArray.addCitizenToCounty(newCitizen, countynum);
		return true;
	}
	bool App::AddCitizenAsDelegate(int id, int partynum, int countynum)
	{
		if (CountyArray.searchDelegate(id))
			return false;
		Citizen* delegate = CountyArray.getCitizen(id);
		if (delegate == nullptr)
			return false;
		Party* party = partyList.getData(partynum);
		if (party == nullptr)
			return false;
		if (countynum <= 0 || countynum > CountyArray.getSize())
				return false;
		CountyDelegate* Delegate = new CountyDelegate(delegate, party);
		CountyArray.addCDToCounty(Delegate, countynum);
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
	void App::initElectors()
	{
		Electors = new Elector[_partiesSize + 1];
		Electors[0].sumElectors = -1;
		for (int i = 1; i <= _partiesSize; i++)
		{
			Electors[i].sumElectors = 0;
			Electors[i].party = this->partyList.getData(i);
		}
	}
	void App::initMatrices()
	{
		initVotesMatrix();
		initStatisticsMatrix();
		initDeligatesMatrix();
		initElectors();
	}
	void App::calcVotes()
	{
		int i, j, max=1, partyNum = -1, place=1, tempDelegatesNum=0, remainingDelegates;
		initMatrices();
		// fill the matrices with the citizen votes 
		CountyArray.getCitizensVotes(_voteCountMatrix, _countiesSize, _partiesSize);
		for (i = 1; i <= _countiesSize; i++)
		{
			int totalCitizensInCounty = CountyArray.getCountySize(i);
			if(totalCitizensInCounty!=0)
			_statisticsMatrix[i][0] = static_cast<float>(_voteCountMatrix[i][0]) / static_cast<float>(totalCitizensInCounty);
			for (j = 1; j <= _partiesSize; j++)
			{
				if(_voteCountMatrix[i][0]!=0)
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
			
	}
		// print for each county : name , amount of Delegates that the county gives , leader name of the winning party.
	void App::printVotes()
	{
		calcVotes();
		int i, j, DeligatesPrinted, max = -1, partyNum = -1;
		for (i = 1; i <= _countiesSize; i++)
		{
			cout << "County name: ";  CountyArray.printCountyName(i);
			cout << "Amount of Delegates: ";  CountyArray.printDelegatesNum(i);
			cout << "The total voting precntage in this county is: " << _statisticsMatrix[i][0] * 100 << "%" << endl;
			for (j = 1; j <= _partiesSize; j++)
			{
				DeligatesPrinted = 0;
				int numdeligates = CountyArray.getDelegatesArrSize(i);
				if (max < _voteCountMatrix[i][j])
				{
					max = _voteCountMatrix[i][j];
					partyNum = j;
				}
				cout << "The party '" << partyList.getData(j)->getPartyName() << "' received " <<
					_statisticsMatrix[i][j] * 100 << "% of the votes, and total of " <<
					_voteCountMatrix[i][j] << " votes for this county." << endl;

				for (int k = 0; k < numdeligates; k++) // run on all the K delegates from the current county , and print the delegates from the rellevant party
				{
					if (_delegatesMatrix[i][j] == 0)
					{
						cout << "No chosen Delegates from the party '" << partyList.getData(j)->getPartyName() << "' for this county " << endl;
						break;
					}
					CountyDelegate* currentDelgate = this->CountyArray.getCounty(i)->getDelgate(k);
					if (currentDelgate->GetPartySerialOfDeligate() == j)// if the delegate is from the current party , print him
					{
						DeligatesPrinted++;
						if (DeligatesPrinted==1)
							cout << "The chosen Delegates from the party '" << partyList.getData(j)->getPartyName() << "' are: ";
						cout << currentDelgate->getName();
						if (DeligatesPrinted != 0 && DeligatesPrinted != _delegatesMatrix[i][j]) cout << ", ";
					}
					if (DeligatesPrinted == _delegatesMatrix[i][j] && DeligatesPrinted>=1) // check how many delegates were actually printed from each party
					{
						cout << "." << endl;
						break;
					}
				}
			}
			cout << "The winner in this county is: "; partyList.PrintLeader(partyNum); cout << endl;
			Electors[partyNum].sumElectors += CountyArray.getDelegatesNum(i);
		}
	
		
		bubbleSort(Electors, _partiesSize + 1);
		for (int i = _partiesSize; i > 0; i--)
			cout << "#" << _partiesSize - i+1 << ". " << Electors[i].party->getLeader()->getName() << " Has got: "
			<< Electors[i].sumElectors << " Electors and his party got " <<
			this->_voteCountMatrix[0][Electors[i].party->getPartySerial()] << " votes" << endl;
	}
	void App::swap(Elector& a, Elector& b)
	{
		Elector c = a;
		a = b;
		b = c;
	}
	void App::bubbleSort(Elector Electors[], int size)
	{
		int i, j;
		for (i = 0; i < size - 1; i++)
			for (j = 0; j < size - i - 1; j++)
				if (Electors[j].sumElectors > Electors[j + 1].sumElectors)
					swap(Electors[j], Electors[j+1]);
	}
}
