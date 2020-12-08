#define _CRT_SECURE_NO_WARNINGS
#include "Citizen.h"
#include "Party.h"
#include "CitizenList.h"
#include "County.h"
#include "CountyArr.h"
#include "CountyDelegate.h"
#include "PartyList.h"
#include <iostream>
#include <string.h>

using namespace std;

namespace votes
{
	CountyDelegate::CountyDelegate(Citizen* delegate, Party* party)
	{
	
		_delegate = delegate;
		_party = party;
	}
}
