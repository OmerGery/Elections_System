#define _CRT_SECURE_NO_WARNINGS
#include "RegularApp.h"
#include <iostream>
#include <algorithm>
using namespace std;
namespace votes
{
	bool electors_sorter(Elector const& a, Elector const& b)
	{
		if (a.sumElectors >= b.sumElectors)
			return false;
		else return true;
	}
	void RegularApp::AddCounty(const string& name, int delegatesNum, int type)
	{
		string errorName;
		if (type != SIMPLE && type != COMPLEX)
			throw (errorName = "County Type isn't valid (need to be 0 or 1)");
		County* county = nullptr;
		if (type == SIMPLE)
			county = new SimpleCounty(name, delegatesNum);
		else
			county = new ComplexCounty(name, delegatesNum);
		CountyArray.push_back(county);
	}
	void RegularApp::AddCitizen(const string& name, int id, int year, int countynum)
	{
		string errorName;
		if (countynum > getSize() || countynum <= 0)
			throw (errorName = "this county doesn't exist.");
		App::AddCitizen(name, id, year, countynum);
		CountyArray[countynum]->AddCitizen(name,id,year);
	}
	void RegularApp::AddCitizenAsDelegate(int id, int partynum, int countynum)
	{
		string errorName;
		checkIfDelegate(id);//this func will throw exception if this citizen is already a delegate.
		Citizen* delegate = getCitizen(id);
		if (delegate == nullptr)
			throw (errorName = "Citizen ID wasn't found");
		Party* party = getPListData(partynum);
		if (party == nullptr)
			throw (errorName = "Party number doesn't exist");
		if (countynum <= 0 || countynum > getSize())
			throw (errorName = "County Number is invalid");
		CountyArray[countynum]->AddCD(delegate, party);
	}
	void RegularApp::PrintAllCounties()const
	{
		string errorName;
		if (getSize() == 0)
			throw (errorName = "you haven't entered any counties.");
		for (int i = 1; i < CountyArray.size(); i++)
		{
			County* current = CountyArray[i];
			cout << (*current);
			current->printCountyType();
		}
	}

	void RegularApp::saveApp(ostream& out)const
	{
		out.write(rcastcc(&COMPLEX), sizeof(COMPLEX));
		App::saveApp(out);
	}

	// print for each county : name , amount of Delegates that the county gives , leader name of the winning party.
	void RegularApp::printVotes()
	{
		App::printVotes();
			int i, j, DeligatesPrinted, max = -1, partyNum = -1;
		for (i = 1; i <= _countiesSize; i++)
		{
			cout << "County name: ";  printCountyName(i);
			cout << "Amount of Delegates: ";  printDelegatesNum(i);
			cout << "The total voting precntage in this county is: " << _statisticsMatrix[i][0] * 100 << "%" << endl;
			for (j = 1; j <= _partiesSize; j++)
			{
				DeligatesPrinted = 0;
				int numdeligates = getDelegatesArrSize(i);
				cout << "The party '" << getPListData(j)->getPartyName() << "' received " <<
					_statisticsMatrix[i][j] * 100 << "% of the votes, and total of " <<
					_voteCountMatrix[i][j] << " votes for this county." << endl;

				for (int k = 0; k < numdeligates; k++) // run on all the K delegates from the current county , and print the delegates from the rellevant party
				{
					if (_delegatesMatrix[i][j] == 0)
					{
						cout << "No chosen Delegates from the party '" << getPListData(j)->getPartyName() << "' for this county " << endl;
						break;
					}
					CountyDelegate* currentDelgate = getCounty(i)->getDelgate(k);
					if (currentDelgate->GetPartySerialOfDeligate() == j)// if the delegate is from the current party , print him
					{
						DeligatesPrinted++;
						if (DeligatesPrinted == 1)
							cout << "The chosen Delegates from the party '" << getPListData(j)->getPartyName() << "' are: ";
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
			printWinnersOfCounty(_voteCountMatrix[i], _electorsMatrix[i], i, _partiesSize, partyList);
		}
		
		vector <Elector> electorsArray;
		electorsArray.resize(_partiesSize + 1);
		electorsArray[0].sumElectors = -1;
		for (int j = 1; j <= _partiesSize; j++)
		{
			electorsArray[j].sumElectors = _electorsMatrix[0][j];
			electorsArray[j].party = getPListData(j);
		}
		sort(electorsArray.begin()+1,electorsArray.end(), electors_sorter);
		cout << endl << "The final election results are: " << endl;

		for (int i = _partiesSize; i > 0; i--)
			cout << "#" << _partiesSize - i + 1 << ". " << electorsArray[i].party->getLeader()->getName() << " Has got: "
			<< electorsArray[i].sumElectors << " Electors and his party got " <<
			this->_voteCountMatrix[0][electorsArray[i].party->getPartySerial()] << " votes" << endl;
	}
}
