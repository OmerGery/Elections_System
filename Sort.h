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
	template<class T>
	void swap(T& a, T& b)
	{
		T c = a;
		a = b;
		b = c;
	}
	void bubbleSort(Elector* Electors, int size);
	void bubbleSort(voteData* voteDataArr, int size);	
}