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
static const int first_option = 1;
enum options {
    AddCounty=first_option, AddCitizen, AddParty, AddDelegate, DisplayCounties, DisplayCitizens, DisplayParties, Vote, ShowRes,Exit
}option;
//Maximum string size:
static const int MAX_SIZE = 100;

//MIN and MAX - modify the maximum and minimum age for a citizen to vote:
static const int MIN_YEAR_TO_VOTE = 1700;
static const int MAX_YEAR_TO_VOTE = 2020;

// Modify the rellevant election date:
static const int ElectionDay = 23; 
static const int ElectionMonth = 11;
static const int ElectionYear = 2020;
int main()
{ 
    // WE ASSUME THAT EACH STRING(=name of county/citizen) CONTAINS ONLY ONE WORD(= no space in entered within a name) . 
    char name[MAX_SIZE];        
    int option, delegatesNum, id, year, countyNum,partyNum,simple;
    bool correctInput; // used for input checks 
    Date date(ElectionDay, ElectionMonth, ElectionYear);
    App MyApplication(date);
    bool exit = false;
    
    while (!exit)
    {
        cout << "1 - Add a County" << endl << "2 - Add a Citizen" << endl << "3 - Add a Party" << endl
            << "4 - Add a Citizen as a party delegate" << endl << "5 - Display all Counties" << endl << "6 - Display all Citizens" << endl
            << "7 - Display all Parties" << endl << "8 - Vote for a Party" << endl << "9 - Display elections results" << endl
            << "10 - EXIT" << endl;
        cout << "Choose an option" << endl; 
        cin >> option;
        switch (option)
        {
        case options::AddCounty:
            cout << "Please Enter 1 for simple county or 0 for complex county" <<endl;
            cin >> simple;
            while (simple != 1 && simple != 0)
            {
                cout << "Please enter 0 or 1 ." << endl;
                cin >> simple;
            }
            cout << "Enter the County name" << endl;
            cin >> name;
            cout << "Enter number of delegates" << endl;
            cin >> delegatesNum;
            while (delegatesNum <= 0)
            {
                cout << "please enter a positive number of delegates" <<endl;
                cin >> delegatesNum;
            }
            MyApplication.AddCounty(name, delegatesNum,simple);
            break;
        case options::AddCitizen:
            cout << "Enter the citizen name" << endl;
            cin >> name;
            cout << "Please Enter ID number" << endl;
            cin >> id;
            while (id <= 0)
            {
                cout << "please enter a positive ID number" << endl;
                cin >> id;
            }
            cout << "Please Enter year of birth" << endl;
            cin >> year;
            while (year < MIN_YEAR_TO_VOTE || year > MAX_YEAR_TO_VOTE)
            {
                cout << "In order to vote ,the citizen age must be valid." << endl;
                cout << "Please Enter year of birth" << endl;
                cin >> year;
            }
            cout << "Please Enter serial number of county" << endl;
            cin >> countyNum;
            correctInput = MyApplication.AddCitizen(name, id, year, countyNum);
            while (!correctInput)
            {
                cout << "The county number or ID number was invalid." << endl;
                cout << "Please Enter serial number of county" << endl;          
                cin >> countyNum;
                cout << "Please Enter ID number" << endl;
                cin >> id;
                while (id <= 0)
                {
                    cout << "please enter a positive ID number" << endl;
                    cin >> id;
                }
                correctInput = MyApplication.AddCitizen(name, id, year, countyNum);
            }
            break;
        case options::AddParty:
            cout << "Enter the party name" << endl;
            cin >> name;
            cout << "Enter ID number of candidate for presidence" << endl;
            cin >> id;    
            correctInput=MyApplication.AddParty(name, id);
            while (!correctInput)
            {
                cout << "This citizen doesn't exist,therefore he can't be a candidate."<<endl << 
                "please enter a correct ID of an existing citizen." << endl;
                cin >> id;
                correctInput = MyApplication.AddParty(name, id);
            }
            break;
        case options::AddDelegate:
            cout << "Enter the citizen ID" << endl;
            cin >> id;
            cout << "Enter party serial number" << endl;
            cin >> partyNum;
            cout << "Enter serial number of county" << endl;
            cin >> countyNum;
            correctInput=MyApplication.AddCitizenAsDelegate(id,partyNum,countyNum);
            while (!correctInput)
            {
                cout << "Please enter a correct: citizen ID , party serial number and county number." <<endl;
                cout << "Enter the citizen ID" << endl;
                cin >> id;
                cout << "Enter party serial number" << endl;
                cin >> partyNum;
                cout << "Enter serial number of county" << endl;
                cin >> countyNum;
                correctInput = MyApplication.AddCitizenAsDelegate(id, partyNum, countyNum);
            }
            break;
        case options::DisplayCounties:
            MyApplication.PrintAllCounties();
            break;
        case options::DisplayCitizens:
            MyApplication.PrintAllCitizens();
            break;
        case options::DisplayParties:
            MyApplication.PrintAllParties();
            break;
        case options::Vote:
            cout << "Enter the citizen ID" << endl;
            cin >> id;
            cout << "Enter Party Serial number" << endl;
            cin >> partyNum;
            correctInput=MyApplication.Vote(id, partyNum);
            while (!correctInput)
            {
                cout << "This citizen has already voted / Citizen ID or Party Serial number was invalid. please enter them again." << endl;
                cout << "Enter the citizen ID" << endl;
                cin >> id;
                cout << "Enter Party Serial number" << endl;
                cin >> partyNum;
                correctInput = MyApplication.Vote(id, partyNum);
            }
            break;
        case options::ShowRes:
            MyApplication.printVotes();
            break;
        case options::Exit:
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
