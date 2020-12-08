#pragma once
#include <iostream>
#include "CountyDelegate.h"

using namespace std;
namespace votes
{
    class countyDelegateArr
    {
    private:
        CountyDelegate* CDArray;
        int physical = 1;
        int _size;

    public:
        countyDelegateArr();
        ~countyDelegateArr();
        void insert(CountyDelegate& cd);
        int getSize()const;
        void resize();
        void printPartyCDs(Party & party)const;
        CountyDelegate getDel(int place)const { return CDArray[place]; }
    };
}
