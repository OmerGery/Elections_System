#include "ComplexCounty.h"
namespace votes
{
	void ComplexCounty::GetPartiesElectors(float* statisticsArray, int* countyElectors, int partiesSize)const
	{
		int place = 0, tempElectorsNum = 0, remainingDelegates = 0, max = -1;
		for (int i = 1; i <= partiesSize; i++)
		{
			countyElectors[i] = static_cast<int>(_numdelegates * statisticsArray[i]);
			if (countyElectors[i] > max)
			{
				max = countyElectors[i];
				place = i;
			}
			tempElectorsNum += countyElectors[i];
		}
		remainingDelegates = _numdelegates - tempElectorsNum;
		countyElectors[place] += remainingDelegates;

	}
	void ComplexCounty::sortAndPrintWinners(int* voteCount, int* Electors, int partiesSize, PartyList* partylist)const
	{

		int size = partiesSize + 1;
		Elector* electorsArray = new Elector[size];
		electorsArray[0].sumElectors = -1;
		for (int i = 1; i <= partiesSize; i++)
		{
			electorsArray[i].sumElectors = Electors[i];
			electorsArray[i].party = partylist->getData(i);
		}

		bubbleSort(electorsArray, size);
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
		//countyDelegateArr CDArr;
		int complex = 0;
		out.write(rcastcc(&complex), sizeof(complex));
		out.write(rcastcc(&_countySerial), sizeof(_countySerial));
		out.write(rcastcc(&_numdelegates), sizeof(_numdelegates));
		out.write(rcastcc(&countyCounter), sizeof(countyCounter));
		int countyNamelen = static_cast<int> (strlen(_countyName) + 1);
		out.write(rcastcc(&countyNamelen), sizeof(countyNamelen));
		out.write(rcastcc(&_countyName[0]), sizeof(char) * countyNamelen);
		_citizenAllowed.saveCitizensList(out);
	}
}