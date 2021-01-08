#define _CRT_SECURE_NO_WARNINGS
#include "RegularApp.h"
#include "Sort.h"
#include <iostream>
#include <string.h>
using namespace std;
namespace votes
{
	void RegularApp::AddCounty(string name, int delegatesNum, bool simple)
	{
		County* county = nullptr;
		if (simple)
			county = new SimpleCounty(name, delegatesNum);
		else
			county = new ComplexCounty(name, delegatesNum);
		CountyArray.insert(county);
	}
	bool RegularApp::AddCitizen(string name, int id, int year, int countynum)
	{
		string errorName;
		if (countynum > CountyArray.getSize() || countynum <= 0)
			throw (errorName = "County number doesn't exist/negative");
		Citizen* citizen = CountyArray.getCitizen(id);
		if (citizen != nullptr)
			throw (errorName = "Citizen ID already exists");
		Citizen* newCitizen = new Citizen(name, id, year);
		CountyArray.addCitizenToCounty(newCitizen, countynum);
		return true;
	}
	bool RegularApp::AddCitizenAsDelegate(int id, int partynum, int countynum)
	{
		string errorName;
		if (CountyArray.searchDelegate(id))
			throw (errorName = "Citizen is already a delegate");
		Citizen* delegate = CountyArray.getCitizen(id);
		if (delegate == nullptr)
			throw (errorName = "Citizen ID wasn't found");
		Party* party = partyList.getData(partynum);
		if (party == nullptr)
			throw (errorName = "Party number doesn't exist");
		if (countynum <= 0 || countynum > CountyArray.getSize())
			throw (errorName = "County Number is invalid");
		CountyDelegate* Delegate = new CountyDelegate(delegate, party);
		CountyArray.addCDToCounty(Delegate, countynum);
		return true;
	}
	void RegularApp::PrintAllCounties()const
	{
		if (CountyArray.getSize() == 0)
		{
			cout << "You haven't entered any counties." << endl;
			return;
		}
		CountyArray.printAllCounties();
	}

	void RegularApp::saveApp(ostream& out)const
	{
		out.write(rcastcc(&COMPLEX), sizeof(COMPLEX));
		App::saveApp(out);
	}

	// print for each county : name , amount of Delegates that the county gives , leader name of the winning party.
	bool RegularApp::printVotes()
	{
		bool votes = App::printVotes();
		if (!votes)
			return false;
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
						if (DeligatesPrinted == 1)
							cout << "The chosen Delegates from the party '" << partyList.getData(j)->getPartyName() << "' are: ";
						cout << currentDelgate->getName();
						if (DeligatesPrinted != 0 && DeligatesPrinted != _delegatesMatrix[i][j]) cout << ", ";
					}
					if (DeligatesPrinted == _delegatesMatrix[i][j] && DeligatesPrinted >= 1) // check how many delegates were actually printed from each party
					{
						cout << "." << endl;
						break;
					}
				}
			}
			CountyArray.printWinnersOfCounty(_voteCountMatrix[i], _electorsMatrix[i], i, _partiesSize, &partyList);
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
		delete[] electorsArray;
		return true;
		
	}
}
