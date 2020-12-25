#include "Sort.h"
namespace votes
{
	void swap(Elector& a, Elector& b)
	{
		Elector c = a;
		a = b;
		b = c;
	}
	void bubbleSort(Elector* Electors, int size)
	{
		int i, j;
		for (i = 0; i < size - 1; i++)
			for (j = 0; j < size - i - 1; j++)
				if (Electors[j].sumElectors > Electors[j + 1].sumElectors)
					swap(Electors[j], Electors[j + 1]);
	}
}