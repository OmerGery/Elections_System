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
//Maximum string size:
static const int MAX_SIZE = 100;

//MIN and MAX - modify the maximum and minimum age for a citizen to vote:
static const int MIN_YEAR_TO_VOTE = 1700;
static const int MAX_YEAR_TO_VOTE = 2019;

// Modify the rellevant election date:
static const int ElectionDay = 23; 
static const int ElectionMonth = 11;
static const int ElectionYear = 2020;
int main()
{ 
    // WE ASSUME THAT EACH STRING(=name of county/citizen) CONTAINS ONLY ONE WORD(= no space in entered within a name) .
    ifstream inFile;
    inFile.open("votes.txt");
    char name[MAX_SIZE];    
    int option, delegatesNum, id, year, countyNum,partyNum;
    bool correctInput; // used for input checks 
    Date date(ElectionDay, ElectionMonth, ElectionYear);
    App MyApplication(date);
    bool exit = false;
    cout << "1 - Add a County" << endl << "2 - Add a Citizen" << endl << "3 - Add a Party" << endl
        << "4 - Add a Citizen as a party delegate" << endl << "5 - Display all Counties" << endl << "6 - Display all Citizens" << endl
        << "7 - Display all Parties" << endl << "8 - Vote for a Party" << endl << "9 - Display elections results" << endl
        << "10 - EXIT" << endl;
    while (!exit)
    {
        cout << "Choose an option" << endl; 
        inFile >> option;
        switch (option)
        {
        case 1:
            cout << "Enter the County name" << endl;
            inFile >> name;
            cout << "Enter number of delegates" << endl;
            inFile >> delegatesNum;
            while (delegatesNum <= 0)
            {
                cout << "please enter a positive number of delegates" <<endl;
                inFile >> delegatesNum;
            }
            MyApplication.AddCounty(name, delegatesNum);
            break;
        case 2: 
            cout << "Enter the citizen name" << endl;
            inFile >> name;
            cout << "Please Enter ID number" << endl;
            inFile >> id;
            while (id <= 0)
            {
                cout << "please enter a positive ID number" << endl;
                inFile >> id;
            }
            cout << "Please Enter year of birth" << endl;
            inFile >> year;
            while (year < MIN_YEAR_TO_VOTE || year > MAX_YEAR_TO_VOTE)
            {
                cout << "In order to vote ,the citizen age must be valid." << endl;
                cout << "Please Enter year of birth" << endl;
                inFile >> year;    
            }
            cout << "Please Enter serial number of county" << endl;
            inFile >> countyNum;
            correctInput = MyApplication.AddCitizen(name, id, year, countyNum);
            while (!correctInput)
            {
                cout << "The county number or ID number was invalid." << endl;
                cout << "Please Enter serial number of county" << endl;          
                inFile >> countyNum;
                cout << "Please Enter ID number" << endl;
                inFile >> id;
                while (id <= 0)
                {
                    cout << "please enter a positive ID number" << endl;
                    inFile >> id;
                }
                correctInput = MyApplication.AddCitizen(name, id, year, countyNum);
            }
            break;
        case 3: 
            cout << "Enter the party name" << endl;
            inFile >> name;
            cout << "Enter ID number of candidate for presidence" << endl;
            inFile >> id;    
            correctInput=MyApplication.AddParty(name, id);
            while (!correctInput)
            {
                cout << "This citizen doesn't exist,therefore he can't be a candidate."<<endl << 
                "please enter a correct ID of an existing citizen." << endl;
                inFile >> id;
                correctInput = MyApplication.AddParty(name, id);
            }
            break;
        case 4: 
            cout << "Enter the citizen ID" << endl;
            inFile >> id;
            cout << "Enter party serial number" << endl;
            inFile >> partyNum;
            cout << "Enter serial number of county" << endl;
            inFile >> countyNum;
            correctInput=MyApplication.AddCitizenAsDelegate(id,partyNum,countyNum);
            while (!correctInput)
            {
                cout << "Please enter a correct: citizen ID , party serial number and county number." <<endl;
                cout << "Enter the citizen ID" << endl;
                inFile >> id;
                cout << "Enter party serial number" << endl;
                inFile >> partyNum;
                cout << "Enter serial number of county" << endl;
                inFile >> countyNum;
                correctInput = MyApplication.AddCitizenAsDelegate(id, partyNum, countyNum);
            }
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
            correctInput=MyApplication.Vote(id, partyNum);
            while (!correctInput)
            {
                cout << "The Citizen ID or Party Serial number was invalid. please enter them again." << endl;
                cout << "Enter the citizen ID" << endl;
                inFile >> id;
                cout << "Enter Party Serial number" << endl;
                inFile >> partyNum;
                correctInput = MyApplication.Vote(id, partyNum);
            }
            break;
        case 9:
            MyApplication.printVotes();
            break;
        case 10:
            cout << "You have exited the program. " <<endl;
            exit = true;
            break;
        default:
            cout << "Please select an option between 1-10." << endl;
            break;
        }
     }
    return 0;
}
