#pragma once
#include "County.h"
#include "DynamicArray.h"
#include <iostream>
using namespace std;
namespace votes
{
    // CountyArr is the class we use for handling the counties in the election round, we hold them in an array.
    class countyArr
    {
    private:
        DynamicArray <County*> countyArray;
    public:
        //ctors/dtors:
      countyArr();
      ~countyArr();
      void addCitizenToCounty(Citizen* citizen, int countynum);
      void addCDToCounty(CountyDelegate* delegate,int countynum);

      //getters:
      const int getSize()const { return static_cast<const int>(countyArray.size() - 1); }
      Citizen* getCitizen(int id);
      void getCitizensVotes(int** votesMatrix, int counties, int parties)const;
      void getElectors(int** electorsMatrix,float** statsMatrix,int partiesSize);
      const int getDelegatesNum(int countyNum) const;
      County* getCounty(int i) const { return countyArray[i]; }
      const int getCountySize(int county) const;
      const int getDelegatesArrSize(int countyNum) const;

      void printCountyName(int countyNum) const;
      void printWinnersOfCounty(int* voteCount,int* electors, int countyNum, int partiesSize, PartyList* partylist) const;
      void printDelegatesNum(int countyNum) const;
      void printDelegatesOfAParty(int countynum, int partynum) const;
      void printAllCounties()const;
      void printAllCitizens()const;

      bool searchDelegate(int id) const;
      void saveCountyArray(ostream& out) const;
      void loadCountyArray(istream& in);
      void insert(County* county) { countyArray.push_back(county); }
    };
}
