#define _CRT_SECURE_NO_WARNINGS
#include "County.h"
#include "CountyArr.h"
#include "SimpleCounty.h"
#include "ComplexCounty.h"
#include <string.h>
#include <iostream>

using namespace std;

namespace votes
{
    countyArr::countyArr()
    {
        countyArray.push_back(nullptr);
    }
    countyArr::~countyArr()
    {
        countyArray[0]->resetCounter();
        countyArray.clear();
    }
    void countyArr::printAllCounties()const
    {
        for (int i = 1; i < countyArray.size(); i++)
        {
            County* current = countyArray[i];
            cout << (*current) ;
            current->printCountyType();
        }
    }
    void countyArr::printCountyName(int countyNum) const
    {
        cout << (*countyArray[countyNum]).getCountyName() << endl;
    }
    void countyArr::printWinnersOfCounty(int* voteCount,int* electors,int countyNum,int partiesSize,PartyList* partylist) const
    {
        countyArray[countyNum]->sortAndPrintWinners(voteCount,electors, partiesSize, partylist);
    }

    void countyArr::printDelegatesNum(int countyNum) const
    {
        cout << (*countyArray[countyNum]).getdelegatesNum() << endl;
    }
    const int countyArr::getDelegatesNum(int countyNum) const
    {
        return (*countyArray[countyNum]).getdelegatesNum();
    }
    const int countyArr::getDelegatesArrSize(int countyNum) const
    {
        return countyArray[countyNum]->getDelgatesarrSize();
    }
    void countyArr::printAllCitizens()const
    {
        for (int i = 1; i < countyArray.size(); i++)
            countyArray[i]->PrintCitizenList();
    }
    void countyArr::getCitizensVotes(int** votesMatrix, int counties, int parties)const
    {

        for (int i = 1; i <= counties; i++)
        {
            County* current = countyArray[i];
            current->getCountyVotes(votesMatrix[i]);
            for (int j = 0; j <= parties; j++)
            {
                votesMatrix[0][j] += votesMatrix[i][j];
            }
        }
    }
    void countyArr::getElectors(int** electorsMatrix, float** statsMatrix, int partiesSize)
    {
        
        for (int i = 1; i < countyArray.size(); i++)
        {
            County* current = countyArray[i];
            current->GetPartiesElectors(statsMatrix[i],electorsMatrix[i],partiesSize);
            for (int j = 1; j <= partiesSize; j++)
            {
                electorsMatrix[0][j] += electorsMatrix[i][j];
            }
        }
    }
    const int countyArr::getCountySize(int county)const
    {
        County* tofind = countyArray[county];
        return tofind->getCountySize();
    }
    void countyArr::addCitizenToCounty(Citizen* citizen, int countynum)
    {
        countyArray[countynum]->AddCitizen(citizen);
    }
    void countyArr::addCDToCounty(CountyDelegate* delegate, int countynum)
    {
        countyArray[countynum]->AddCD(delegate);
    }
    
    Citizen* countyArr::getCitizen(int id)
    {
        for (int i = 1; i < countyArray.size(); i++)
        {
            County* current =countyArray[i];
            Citizen* search = current->searchCitizen(id); 
            if (search)
                return search;    
        }
        return nullptr;
    }
    void countyArr::printDelegatesOfAParty(int countynum, int partynum) const
    {
        County* current_C = countyArray[countynum];
        int totalDeligatesinCounty = countyArray[countynum]->getDelgatesarrSize();
        int counter=0;
        for (int i = 0; i < totalDeligatesinCounty; i++)
        {
            CountyDelegate* current = current_C->getDelgate(i);
            if ((*current).GetPartySerialOfDeligate() == partynum)
            {
                counter++;
                if (counter > 1)
                    cout << ",";
                if (counter == 1)
                    cout << "The Delegates from this Party in The County " << (*this->countyArray[countynum]).getCountyName() << " are: ";
                cout << (*current).getName();
            }
        }
        if(counter>0)
        cout << "." << endl;
    }
    bool countyArr::searchDelegate(int id) const
    {
        for (int k = 1; k < countyArray.size(); k++)
        {
            County* current_C = countyArray[k];
            int totalDeligatesinCounty = countyArray[k]->getDelgatesarrSize();
            for (int i = 0; i < totalDeligatesinCounty; i++)
            {
                CountyDelegate* current = current_C->getDelgate(i);
                if (current->getID() == id)
                    return true;
            }
        }
        return false;
    }
    void countyArr::saveCountyArray(ostream& out) const
    {
        int size = countyArray.size();
        out.write(rcastcc(&size), sizeof(size));
        for (int i = 1; i < size; ++i) 
            countyArray[i]->saveCounty(out);
    }
    void countyArr::loadCountyArray(istream& in)
    {
        int loadedCounites;
        in.read(rcastc(&loadedCounites), sizeof(loadedCounites));
        for (int i = 1; i < loadedCounites; ++i)
        {
            int type;
            in.read(rcastc(&type), sizeof(type));
            County* county = nullptr;
            if (type==SIMPLE)
                county = new SimpleCounty();
            else
                county = new ComplexCounty();
           county->loadCounty(in);
           countyArray.push_back(county);
        }
    }
};
