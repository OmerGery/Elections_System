#define _CRT_SECURE_NO_WARNINGS
#include "SimpleApp.h"
#include "Sort.h"
#include <iostream>
#include <string.h>
using namespace std;
namespace votes
{
	SimpleApp::SimpleApp(Date& electionday, int delegatesNum):App(electionday)
	{	
		_countiesSize = 1;
		County* county = new ComplexCounty("default", delegatesNum);
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


	
	// print: name , amount of Delegates that the county gives , leader name of the winning party.
	void SimpleApp::printVotes()
	{
		calcVotes();
		int  j, DeligatesPrinted, max = -1, partyNum = -1;
			cout << "Amount of Delegates: ";  CountyArray.printDelegatesNum(1);
			cout << "The total voting precntage is: " << _statisticsMatrix[1][0] * 100 << "%" << endl;
			for (j = 1; j <= _partiesSize; j++)
			{
				DeligatesPrinted = 0;
				int numdeligates = CountyArray.getDelegatesArrSize(1);
				cout << "The party '" << partyList.getData(j)->getPartyName() << "' received " <<
					_statisticsMatrix[1][j] * 100 << "% of the votes, and total of " <<
					_voteCountMatrix[1][j] << " votes." << endl;

				for (int k = 0; k < numdeligates; k++) // run on all the K delegates from the current county , and print the delegates from the rellevant party
				{
					if (_delegatesMatrix[1][j] == 0)
					{
						cout << "No chosen Delegates from the party '" << partyList.getData(j)->getPartyName() << endl;
						break;
					}
					CountyDelegate* currentDelgate = this->CountyArray.getCounty(1)->getDelgate(k);
					if (currentDelgate->GetPartySerialOfDeligate() == j)// if the delegate is from the current party , print him
					{
						DeligatesPrinted++;
						if (DeligatesPrinted == 1)
							cout << "The chosen Delegates from the party '" << partyList.getData(j)->getPartyName() << "' are: ";
						cout << currentDelgate->getName();
						if (DeligatesPrinted != 0 && DeligatesPrinted != _delegatesMatrix[1][j]) cout << ", ";
					}
					if (DeligatesPrinted == _delegatesMatrix[1][j] && DeligatesPrinted >= 1) // check how many delegates were actually printed from each party
					{
						cout << "." << endl;
						break;
					}
				}
		}
		Elector* electorsArray = new Elector[_partiesSize + 1];
		electorsArray[0].sumElectors = -1;
		for (int j = 1; j <= _partiesSize; j++)
		{
			electorsArray[j].sumElectors = _electorsMatrix[0][j];
			electorsArray[j].party = partyList.getData(j);
		}
		bubbleSort(electorsArray, _partiesSize + 1);
		cout << endl << "The final election results are: " << endl;

		for (int i = _partiesSize; i > 0; i--)
			cout << "#" << _partiesSize - i + 1 << ". " << electorsArray[i].party->getLeader()->getName() << " Has got: "
			<< electorsArray[i].sumElectors << " Electors and his party got " <<
			this->_voteCountMatrix[0][electorsArray[i].party->getPartySerial()] << " votes" << endl;
	}

}
