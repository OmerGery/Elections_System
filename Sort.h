#pragma once
#include "Party.h"
using namespace std;
namespace votes
{
	struct Elector
	{
		int sumElectors;
		Party* party;
	};
	void swap(Elector& a, Elector& b);
	void bubbleSort(Elector* Electors, int size);
}