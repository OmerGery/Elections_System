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
	struct voteData
	{
		int sumDelegates;
		Party* party;
		int numVotes;
		float precentage;
	};
	void swap(Elector& a, Elector& b);
	void bubbleSort(Elector* Electors, int size);
	void swapvoteData(voteData& a, voteData& b);
	void bubbleSortvoteData(voteData* voteDataArr, int size);
}