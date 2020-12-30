#pragma once
#include "Party.h"
using namespace std;
namespace votes
{
	static const int SIMPLE = 1;
	static const int COMPLEX = 0;
	struct Elector
	{
		int sumElectors;
		Party* party;
	};
	void swap(Elector& a, Elector& b);
	void bubbleSort(Elector* Electors, int size);
}