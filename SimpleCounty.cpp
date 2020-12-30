#include "SimpleCounty.h"

namespace votes
{
	void SimpleCounty::GetPartiesElectors(float* statisticsArray, int* countyElectors, int partiesSize)const 
	{
		float max = -1;
		int winningParty = 0;
		for (int i = 1; i <= partiesSize; i++)
		{
			if (max < statisticsArray[i])
			{
				max = statisticsArray[i];
				winningParty = i;
			}
		}
		countyElectors[winningParty] = this->_numdelegates;
	}
	void SimpleCounty::sortAndPrintWinners(int* voteCount, int* Electors, int partiesSize, PartyList* partylist)const
	{
		for (int i = 1; i <= partiesSize; i++)
		{
			if (Electors[i] > 0)
			{
				cout << "The winner in this county is:"; partylist->PrintLeader(i);
				break;
			}
		}
	}
	void SimpleCounty::printCountyType() const
	{
		cout << " County Type: Simple " << endl;
	}

	void SimpleCounty::saveCounty(ostream& out) const
	{
		out.write(rcastcc(&SIMPLE), sizeof(SIMPLE));
		County::saveCounty(out);
	}

}