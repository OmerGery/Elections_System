#define _CRT_SECURE_NO_WARNINGS
#include "County.h"
#include "CountyArr.h"
#include <string.h>
#include <iostream>

using namespace std;

namespace votes
{
    countyArr::countyArr()
    {
        countyArray = new County*[physical];
        _size = 1;
    }
    countyArr::~countyArr()
    {
        for (int i = 1; i < _size; i++)
            delete countyArray[i];
        delete[] countyArray;
    }
    void countyArr::printAllCounties()const
    {
        for (int i = 1; i < _size; i++)
        {
            County* current = countyArray[i];
            cout << (*current);
        }
    }
    void countyArr::printCountyName(int countyNum) const
    {
        cout << (*countyArray[countyNum]).getCountyName() << endl;
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
        County* current = countyArray[countyNum];
        return current->getDelgatesarrSize();
    }
    void countyArr::printAllCitizens()const
    {
        for (int i = 1; i < _size; i++)
        {
            County* current = countyArray[i];
            current->PrintCitizenList();
        }
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
    const int countyArr::getCountySize(int county)const
    {
        County* tofind = countyArray[county];
        return tofind->getCountySize();
    }
    void countyArr::insert(County * county)
    {
        if (_size == physical)
            resize();
        countyArray[_size]=county;
        _size++;
    }
    void countyArr::addCitizenToCounty(Citizen * citizen, int countynum)
    {
        (*(countyArray[countynum])).AddCitizen(citizen);
    }
    void countyArr::addCDToCounty(CountyDelegate* delegate, int countynum)
    {
        (*countyArray[countynum]).AddCD(delegate);
    }
    const int countyArr::getSize()const { return _size-1; }
    
    void countyArr::resize()
    {
        physical *= 2;
        County** temp = new County*[physical];
        std::copy(countyArray, countyArray + _size, temp);
        delete[] countyArray;
        countyArray = temp;
    }
    Citizen* countyArr::getCitizen(int id)
    {
        
        for (int i = 1; i < _size; i++)
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
};
