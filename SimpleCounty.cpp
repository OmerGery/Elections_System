#include "SimpleCounty.h"

namespace votes
{
	void SimpleCounty::GetPartiesElectors(vector<float>& statisticsArray, vector<int>& countyElectors, int partiesSize)const
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
	void SimpleCounty::sortAndPrintWinners(vector<int>& voteCount, vector<int>& Electors, int partiesSize, list <Party*> partylist)const
	{
		list<Party*>::const_iterator it = partylist.begin();
		for (int i = 1; i <= partiesSize; i++)
		{
			if (Electors[i] > 0)
			{
				cout << "The winner in this county is:" << (*it)->getLeader()->getName() << endl;
				break;
			}
			advance(it, 1);
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