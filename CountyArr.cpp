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
        countyArray = new County[physical];
        _size = 1;
    }
    countyArr::~countyArr()
    {
        delete[] countyArray;
    }
    void countyArr::printAllCounties()const
    {
        for (int i = 1; i < _size; i++)
        {
            County current = countyArray[i];
            cout << current.getCountySerial() << " " << current.getCountyName() << " " << current.getdelegatesNum() << endl;
        }
    }
    void countyArr::printCountyName(int countyNum) const
    {
        cout << countyArray[countyNum].getCountyName() << endl;
    }
    void countyArr::printDelegatesNum(int countyNum) const
    {
        cout << countyArray[countyNum].getdelegatesNum() << endl;
    }
    const int countyArr::getDelegatesNum(int countyNum) const
    {
        return countyArray[countyNum].getdelegatesNum();
    }
    void countyArr::printAllCitizens()const
    {
        for (int i = 1; i < _size; i++)
        {
            County current = countyArray[i];
            (current.GetCitizens()).PrintList(current);
        }
    }
    void countyArr::getCitizensVotes(int** votesMatrix, int counties, int parties)const
    {

        for (int i = 1; i <= counties; i++)
        {
            County current = countyArray[i];
            (current.GetCitizens()).getVotes(votesMatrix[i]);
            for (int j = 0; j <= parties; j++)
            {
                votesMatrix[0][j] += votesMatrix[i][j];
            }
        }
    }
    void countyArr::insert(County & county)
    {
        if (_size == physical)
            resize();
        countyArray[_size]=County(county);
        _size++;
    }
    void countyArr::addCitizenToCounty(Citizen * citizen, int countynum)
    {
        (countyArray[countynum]).AddCitizen(citizen);
    }
    void countyArr::addCDToCounty(CountyDelegate& delegate, int countynum)
    {
        countyArray[countynum].AddCD(delegate);
    }
    const int countyArr::getSize()const { return _size-1; }
    
    void countyArr::resize()
    {
        physical *= 2;
        County* temp = new County[physical];
        std::copy(countyArray, countyArray + _size, temp);
        delete[] countyArray;
        countyArray = temp;
    }
    Citizen* countyArr::getCitizen(int id)
    {
        
        for (int i = 1; i < _size; i++)
        {
            County current = countyArray[i];
            Citizen* search = (current.GetCitizens()).findCitizen(id);
            if (search)
                return search;    
        }
        return nullptr;
    }
};
