#define _CRT_SECURE_NO_WARNINGS
#include "Date.h"
#include "Citizen.h"
#include "Party.h"
#include "CitizenList.h"
#include "County.h"
#include "CountyArr.h"
#include "CountyDelegate.h"
#include "PartyList.h"
#include <iostream>
#include "App.h"
#include <fstream>
using namespace std;
using namespace votes;
static const int MAX_SIZE = 100;
int main()
{ 
    // WE ASSUME THAT EACH STRING(=name of county/citizen) CONTAINS ONLY ONE WORD(= no space in entered within a name) . 
    ifstream inFile;
    inFile.open("test1.txt");
    char name[MAX_SIZE];    
    int option, delegatesNum, id=-1, year, countyNum,partyNum;
    Date date(23, 11, 2020);
    App MyApplication(date);
    bool exit = false;
    bool read = true;
    cout << "1 - Add a County" << endl << "2 - Add a Citizen" << endl << "3 - Add a Party" << endl
        << "4 - Add a Citizen as a party delegate" << endl << "5 - Display all Counties" << endl << "6 - Display all Citizens" << endl
        << "7 - Display all Parties" << endl << "8 - Vote for a Party" << endl << "9 - Display elections results" << endl
        << "10 - EXIT" << endl;
    while (!exit)
    {
        cout << "Choose an option" << endl; 
        if (read)
            inFile >> option;
        else
            cin >> option;
        switch (option)
        {
        case 1:
            cout << "Enter the County name" << endl;
            
            inFile >> name;
            cout << "Enter number of delegates" << endl;
            inFile >> delegatesNum;
            MyApplication.AddCounty(name, delegatesNum);
            break;
        case 2: 
            cout << "Enter the citizen name" << endl;
            
            inFile >> name;
            cout << "Enter ID number" << endl;
            inFile >> id;
            cout << "Enter year of birth" << endl;
            inFile >> year;
            cout << "Enter serial number of county" << endl;
            inFile >> countyNum;
            MyApplication.AddCitizen(name, id, year, countyNum);
     
            break;
        case 3: 
            cout << "Enter the party name" << endl;
            inFile >> name;
            cout << "Enter ID number of candidate for presidence" << endl;
            inFile >> id;    
            MyApplication.AddParty(name, id);
            break;
        case 4: 
            cout << "Enter the citizen ID" << endl;
            inFile >> id;
            while (id < 0)
            {
                cout << "Please enter a correct ID." <<endl;
                inFile >> id;   
            }
            cout << "Enter Party Serial number" << endl;
            inFile >> partyNum;
            while (partyNum < 0)
            {
                cout << "Please enter a correct Party Number." << endl;
                inFile >> partyNum;
            }
            cout << "Enter serial number of county" << endl;
            inFile >> countyNum;
            MyApplication.AddCitizenAsDelegate(id,partyNum,countyNum);
            break;
        case 5:
            MyApplication.PrintAllCounties();
            break;
        case 6: 
            MyApplication.PrintAllCitizens();
            break;
        case 7:
            MyApplication.PrintAllParties();
            break;
        case 8:
            cout << "Enter the citizen ID" << endl;
            inFile >> id;
            cout << "Enter Party Serial number" << endl;
            inFile >> partyNum;
            MyApplication.Vote(id, partyNum);
            break;
        case 9:
            MyApplication.printVotes();
            break;
        case 10:
            cout << "You have exited the program. " <<endl;
            exit = true;
            break;
        case 11:
            read = false;
            cout << "Input stopped" << endl;
            break;
        }
     }
    return 0;
}
