#include "ComplexCounty.h"
#include <iterator>
namespace votes
{
	void ComplexCounty::GetPartiesElectors(vector<float> &statisticsArray, vector<int> &countyElectors, int partiesSize)const
	{
		int place = 0, tempElectorsNum = 0, remainingDelegates = 0;
		float max = -1;
		float currentPrecent;
		for (int i = 1; i <= partiesSize; i++)
		{
			currentPrecent=statisticsArray[i];
			countyElectors[i] = static_cast<int>(_numdelegates * statisticsArray[i]);
			if (currentPrecent > max)
			{
				max = currentPrecent;
				place = i;
			}
			tempElectorsNum += countyElectors[i];
		}
		remainingDelegates = _numdelegates - tempElectorsNum;
		countyElectors[place] += remainingDelegates;
	}
	void ComplexCounty::sortAndPrintWinners(vector<int>& voteCount, vector<int>& Electors, int partiesSize, list <Party*> partylist)const
	{

		int size = partiesSize+1;
		vector <Elector> electorsArray;
		electorsArray.resize(partiesSize + 1);
		electorsArray[0].sumElectors = -1;
		list<Party*>::const_iterator runner = partylist.begin();
		list<Party*>::const_iterator end = partylist.end();
		runner++;
		for (int i=1; runner != end; ++runner,i++)
		{
			electorsArray[i].sumElectors = Electors[i];
			electorsArray[i].party = *runner;
		}

		bubbleSort(electorsArray,size);
		for (int i = partiesSize; i > 0; i--)
			cout << "#" << partiesSize - i + 1 << ". " << electorsArray[i].party->getLeader()->getName() << " Has got: "
			<< electorsArray[i].sumElectors << " Electors and his party got " <<
			voteCount[electorsArray[i].party->getPartySerial()] << " votes" << endl;
	}
	void ComplexCounty::printCountyType() const
	{
		cout << " County Type: Split " << endl;
	}
	void ComplexCounty::saveCounty(ostream& out) const
	{
		out.write(rcastcc(&COMPLEX), sizeof(COMPLEX));
		County::saveCounty(out);
	}
}