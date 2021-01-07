#pragma once
#include <iostream>
#include "CountyDelegate.h"
#include <vector>
using namespace std;
namespace votes
{
    class countyDelegateArr
    {
    private:
        vector<CountyDelegate*> CDArray;

    public:
        CountyDelegate* getDel(int place)const { return CDArray[place]; }
        const int getSize()  const { return CDArray.size(); }
        void insert(CountyDelegate* cd) { CDArray.push_back(cd); }
    };
}
