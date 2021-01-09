#define _CRT_SECURE_NO_WARNINGS
#include "Citizen.h"
#include "Party.h"
 
#include "County.h"
#include "CountyArr.h"
#include "CountyDelegate.h"
#include <iostream>
 

using namespace std;

namespace votes
{
	CountyDelegate::CountyDelegate(Citizen* delegate, Party* party)
	{
	
		_delegate = delegate;
		_party = party;
	}
}
