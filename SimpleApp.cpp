#define _CRT_SECURE_NO_WARNINGS
#include "SimpleApp.h"
#include "Sort.h"
#include <iostream>
#include <string.h>
using namespace std;
namespace votes
{
	SimpleApp::SimpleApp(Date electionday, int delegatesNum):App(electionday)
	{
		County* county = new ComplexCounty(defaultName, delegatesNum);
		CountyArray.insert(county);
	}
	void SimpleApp::PrintAllCounties()const
	{
		cout << "There are no counties in this type of elections";
	}
	void SimpleApp::AddCounty(char* name, int delegatesNum, bool simple)
	{
		cout << "Can't add counties in this type of elections";
	}
	bool SimpleApp::AddCitizen(char* name, int id, int year, int countynum)
	{
		Citizen* citizen = CountyArray.getCitizen(id);
		if (citizen != nullptr)
			return false;
		Citizen* newCitizen = new Citizen(name, id, year);
		CountyArray.addCitizenToCounty(newCitizen, 1);
		return true;
	}
	bool SimpleApp::AddCitizenAsDelegate(int id, int partynum, int countynum)
	{
		if (CountyArray.searchDelegate(id))
			return false;
		Citizen* delegate = CountyArray.getCitizen(id);
		if (delegate == nullptr)
			return false;
		Party* party = partyList.getData(partynum);
		if (party == nullptr)
			return false;
		CountyDelegate* Delegate = new CountyDelegate(delegate, party);
		CountyArray.addCDToCounty(Delegate, 1);
		return true;
	}

	void SimpleApp::saveApp(ostream& out)const
	{
		out.write(rcastcc(&SIMPLE), sizeof(SIMPLE));
		App::saveApp(out);
	}
	bool SimpleApp::printVotes()
	{
		bool votes = App::printVotes();
		if (!votes)
			return false;
		int DeligatesPrinted;
		cout << "The total voting precntage is: " << _statisticsMatrix[1][0] * 100 << "%" << endl;
		voteData* voteDataArr = new voteData[_partiesSize + 1];
		voteDataArr[0].sumDelegates = -1;
		for (int j = 1; j <= _partiesSize; j++)
		{
			voteDataArr[j].sumDelegates = _electorsMatrix[0][j];
			voteDataArr[j].party = partyList.getData(j);
			voteDataArr[j].precentage =_statisticsMatrix[1][j]*100;
			voteDataArr[j].numVotes = _voteCountMatrix[0][j];
		}
		bubbleSortvoteData(voteDataArr, _partiesSize + 1);
		cout << endl << "The final election results are: " << endl;

		for (int i = _partiesSize; i > 0; i--)
		{
			int partyNumber = voteDataArr[i].party->getPartySerial();
			DeligatesPrinted = 0;
			cout << "#" << _partiesSize - i + 1 << ". '" << voteDataArr[i].party->getPartyName() << "' Has got: ";
			cout << voteDataArr[i].sumDelegates << " Delegates ," << voteDataArr[i].numVotes << " votes, ";
			cout << voteDataArr[i].precentage << "% of votes. The Leader name of this party is: " << voteDataArr[i].party->getLeader()->getName() << endl;
			for (int k = 0; k < voteDataArr[i].sumDelegates; k++) // run on all the K delegates from the current county , and print the delegates from the rellevant party
			{
				if (voteDataArr[i].sumDelegates == 0)
				{
				cout << "No chosen Delegates from the party '" << voteDataArr[i].party->getPartyName() << endl;
				break;
				}
			CountyDelegate* currentDelgate = this->CountyArray.getCounty(1)->getDelgate(k);
			if (currentDelgate->GetPartySerialOfDeligate() == i)// if the delegate is from the current party , print him
			{
				DeligatesPrinted++;
				if (DeligatesPrinted == 1)
					cout << "The chosen Delegates from the party '" << partyList.getData(partyNumber)->getPartyName() << "' are: ";
				cout << currentDelgate->getName();
				if (DeligatesPrinted != 0 && DeligatesPrinted != _delegatesMatrix[1][partyNumber]) cout << ", ";
			}
			if (DeligatesPrinted == _delegatesMatrix[1][partyNumber] && DeligatesPrinted >= 1) // check how many delegates were actually printed from each party
			{
				cout << "." << endl;
				break;
			}
			}
		}
		delete [] voteDataArr;
		return true;
	}
}
