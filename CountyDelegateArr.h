#pragma once
#include <iostream>
#include "CountyDelegate.h"

using namespace std;
namespace votes
{
    class countyDelegateArr
    {
    private:
        CountyDelegate** CDArray;
        int physical = 1;
        int _size;

    public:
        //ctors/dtors:
        countyDelegateArr();
        ~countyDelegateArr();

        void insert(CountyDelegate* cd);
        int getSize()const;
        void resize();
        CountyDelegate* getDel(int place)const { return CDArray[place]; }
    };
}
