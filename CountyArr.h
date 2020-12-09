#pragma once
#include "County.h"
#include <iostream>
using namespace std;
namespace votes
{
    class countyArr
    {
    private:
        County* countyArray;
        int physical = 1;
        int _size;

    public:
      countyArr();
      ~countyArr();
      void insert(County & county);
      const int getSize()const;
      void resize();
      void addCitizenToCounty(Citizen * citizen, int countynum);
      void addCDToCounty(CountyDelegate& delegate,int countynum);
      void printAllCounties()const;
      void printAllCitizens()const;
      Citizen* getCitizen(int id);
      void getCitizensVotes(int** votesMatrix, int counties, int parties)const;
      void printCountyName(int countyNum) const;
      void printDelegatesNum(int countyNum) const;
      void printDelegatesOfAParty(int countynum, int partynum) const;
      const int getDelegatesNum(int countyNum) const;
      County getCounty(int i) const  { return countyArray[i]; }
    };
}
