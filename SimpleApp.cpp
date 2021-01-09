#define _CRT_SECURE_NO_WARNINGS
#include "SimpleApp.h"
#include <iostream>
 
using namespace std;
namespace votes
{
	SimpleApp::SimpleApp(Date electionday, int delegatesNum):App(electionday)
	{
		string errorName;
		if (delegatesNum <= 0)
			throw (errorName = "number of delegates must be positive");
		County* county = new ComplexCounty(defaultName, delegatesNum);
		if (!county)
			throw (errorName = "Memory Allocation failed.");
		CountyArray.insert(county);
	}
	void SimpleApp::PrintAllCounties()const
	{
		string errorName;
		throw (errorName = "There are no counties in this type of elections");
	}
	void SimpleApp::AddCounty(string name, int delegatesNum, int type)
	{
		string errorName;
		throw (errorName = "Can't add counties in this type of elections.");
	}
	bool SimpleApp::AddCitizen(string name, int id, int year, int countynum)
	{
		string errorName;
		App::AddCitizen(name, id, year, countynum);
		Citizen* newCitizen = new Citizen(name, id, year);
		if (!newCitizen)
			throw (errorName = "Memory Allocation failed.");
		CountyArray.addCitizenToCounty(newCitizen, 1);
		return true;
	}
	bool SimpleApp::AddCitizenAsDelegate(int id, int partynum, int countynum)
	{
		string errorName;
		if (CountyArray.searchDelegate(id))
			throw (errorName = "Citizen is already a delegate");
		Citizen* delegate = CountyArray.getCitizen(id);
		if (delegate == nullptr)
			throw (errorName = "Citizen ID wasn't found");
		Party* party = getPListData(partynum);
		if (party == nullptr)
			throw (errorName = "Party number doesn't exist");
		CountyDelegate* Delegate = new CountyDelegate(delegate, party);
		if (!Delegate)
			throw (errorName = "Memory Allocation failed.");
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
		int DeligatesPrinted,partyNumber,totalDels;
		int numdeligates = CountyArray.getDelegatesArrSize(1);
		cout << "The total voting precntage is: " << _statisticsMatrix[1][0] * 100 << "%" << endl;
		vector <voteData> voteDataArr;
		voteDataArr.resize(_partiesSize + 1);
		voteDataArr[0].sumDelegates = -1;
		for (int j = 1; j <= _partiesSize; j++)
		{
			voteDataArr[j].sumDelegates = _electorsMatrix[1][j];
			voteDataArr[j].party = getPListData(j);
			voteDataArr[j].precentage =_statisticsMatrix[1][j]*100;
			voteDataArr[j].numVotes = _voteCountMatrix[0][j];
		}
		bubbleSort(voteDataArr, _partiesSize + 1);
		cout << "The final election results are: " << endl;

		for (int i = _partiesSize; i > 0; i--)
		{
			partyNumber = voteDataArr[i].party->getPartySerial();
			DeligatesPrinted = 0;
			totalDels = _electorsMatrix[1][partyNumber];
			cout << "#" << _partiesSize - i + 1 << ". The Party '" << voteDataArr[i].party->getPartyName() << "' Has got: ";
			cout << totalDels << " Delegates ," << voteDataArr[i].numVotes << " votes, ";
			cout << voteDataArr[i].precentage << "% of votes." << endl <<"The Leader name of this party is: " << voteDataArr[i].party->getLeader()->getName() << "." << endl;
			for (int k = 0; k < numdeligates; k++) // run on all the K delegates from the current county , and print the delegates from the rellevant party
			{
				if (totalDels == 0)
				{
				cout << "No chosen Delegates from the party '" << voteDataArr[i].party->getPartyName() << "." << endl;
				break;
				}
			CountyDelegate* currentDelgate = this->CountyArray.getCounty(1)->getDelgate(k);
			if (currentDelgate->GetPartySerialOfDeligate() == partyNumber)// if the delegate is from the current party , print him
			{
				DeligatesPrinted++;
				if (DeligatesPrinted == 1)
					cout << "The chosen Delegates from the party '" << getPListData(partyNumber)->getPartyName() << "' are: ";
				cout << currentDelgate->getName();
				if (DeligatesPrinted != 0 && DeligatesPrinted < totalDels) cout << ", ";
			}
			if (DeligatesPrinted == totalDels && DeligatesPrinted >= 1) // check how many delegates were actually printed from each party
				{
				cout << "." << endl;
				break;
				}
			}
		}
		return true;
	}
}
