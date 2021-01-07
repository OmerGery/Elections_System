#pragma once
#include <iostream>
#include "CountyDelegate.h"
#include "DynamicArray.h"
using namespace std;
namespace votes
{
    class countyDelegateArr
    {
    private:
        DynamicArray<CountyDelegate*> CDArray;

    public:
        CountyDelegate* getDel(int place)const { return CDArray[place]; }
        const int getSize()  const { return static_cast<const int>(CDArray.size()); }
        void insert(CountyDelegate* cd) { CDArray.push_back(cd); }
    };
}
