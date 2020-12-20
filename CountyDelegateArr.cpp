#define _CRT_SECURE_NO_WARNINGS
#include "CountyDelegateArr.h"
#include "CountyDelegate.h"
#include <string.h>
#include <iostream>

using namespace std;

namespace votes
{
    countyDelegateArr::countyDelegateArr()
    {
        CDArray= new CountyDelegate*[physical];
        _size = 0;
    }
    countyDelegateArr::~countyDelegateArr()
    {
        delete[] CDArray;
    }
    void countyDelegateArr::insert(CountyDelegate* CD)
    {
        if (_size == physical)
            resize();
        CDArray[_size] = CD;
        _size++;
    }
    int countyDelegateArr::getSize()const { return _size; }

    void countyDelegateArr::resize()
    {
        physical *= 2;
        CountyDelegate** temp = new CountyDelegate*[physical];
        std::copy(CDArray, CDArray + _size, temp);
        delete[] CDArray;
        CDArray = temp;
    }
};
