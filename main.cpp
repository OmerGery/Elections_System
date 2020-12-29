#define _CRT_SECURE_NO_WARNINGS
#include "Date.h"
#include "Citizen.h"
#include "Party.h"
#include "CitizenList.h"
#include "County.h"
#include "CountyArr.h"
#include "CountyDelegate.h"
#include "PartyList.h"  
#include "App.h"
#include "SimpleApp.h"
#include "RegularApp.h"
#include <iostream>
#include <fstream>
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

using namespace std;
using namespace votes;
static const int first_option = 1;
enum options {
    AddCounty=first_option, AddCitizen, AddParty, AddDelegate, DisplayCounties, DisplayCitizens, DisplayParties, Vote, ShowRes, Exit, Save, Load
}option;
enum preOptions {
    NewRound = first_option, LoadVotes, PreExit
}preoption;
//Maximum string size:
static const int MAX_SIZE = 100;

//MIN and MAX - modify the maximum and minimum age for a citizen to vote:
static const int MIN_YEAR_TO_VOTE = 1700;
static const int MAX_YEAR_TO_VOTE = 2020;

int main()
{ 
    ifstream infile;
    ofstream outfile;
    // WE ASSUME THAT EACH STRING(=name of county/citizen) CONTAINS ONLY ONE WORD(= no space in entered within a name) . 
    char name[MAX_SIZE], fname[MAX_SIZE];        
    int option, delegatesNum, id, day, month, year, countyNum, partyNum, simple;
    bool correctInput; // used for input checks 
    bool exit=false, prexit=false;
    App* mainApp = nullptr;
    Date* date = nullptr;
    
    while (!prexit)
    {
        cout << endl << "1 - Create a new Elections round" << endl << "2 - Load an exisiting Elections round" << endl << "3 - Exit" << endl;
        cout << "Choose an option" << endl;
        cin >> option;
        switch (option)
        {
        case preOptions::NewRound:
            cout << "Please enter the Elections type - 1 for simple or 0 for regular " << endl;
            cin >> simple;
            while (simple != 1 && simple != 0)
            {
                cout << "Please enter 0 or 1 ." << endl;
                cin >> simple;
            }
            cout << "Please enter election day" << endl;
            cin >> day;
            cout << "Please enter election month" << endl;
            cin >> month;
            cout << "Please enter election year" << endl;
            cin >> year;
            date = new Date(day, month, year);
            if (simple)
            {
                cout << "Enter number of delegates" << endl;
                cin >> delegatesNum;
                while (delegatesNum <= 0)
                {
                    cout << "please enter a positive number of delegates" << endl;
                    cin >> delegatesNum;
                }
                mainApp = new SimpleApp(date, delegatesNum);
            }
            else
                mainApp = new RegularApp(date);
            prexit = true;
            break;
        case preOptions::LoadVotes:
            cout << "Please enter the file name you want to load" << endl;
            cin >> fname;
            infile.open(fname, ios::binary | ios::in);
            if (!infile.is_open())
            {
                cout << "File name wasn't found";
                prexit = true;
                exit = true;
                break;
            }
            date = new Date();
            int simple;
            infile.read(rcastc(&simple), sizeof(simple));
            if (simple)
                mainApp = new SimpleApp(date,0);
            else
                mainApp = new RegularApp(date);
            mainApp->loadApp(infile);
            infile.close();
            prexit = true;
            break;
        case preOptions::PreExit:
            cout << "You have exited the program. " << endl;
            prexit = true;
            exit = true;
            break;
        default:
            cout << "Please select an option between 1-3." << endl;
            break;
        }
    }
        
            while (!exit)
            {
                cout << endl << "1 - Add a County" << endl << "2 - Add a Citizen" << endl << "3 - Add a Party" << endl
                    << "4 - Add a Citizen as a party delegate" << endl << "5 - Display all Counties" << endl << "6 - Display all Citizens" << endl
                    << "7 - Display all Parties" << endl << "8 - Vote for a Party" << endl << "9 - Display Election Results" << endl
                    << "10 - EXIT" << endl << "11 - Save Election Round" << endl << "12 - Load Election Round" << endl;
                cout << "Choose an option" << endl;
                cin >> option;
                switch (option)
                {
                case options::AddCounty:
                    cout << "Please Enter 1 for simple county or 0 for split county" << endl;
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
                        cout << "please enter a positive number of delegates" << endl;
                        cin >> delegatesNum;
                    }
                    mainApp->AddCounty(name, delegatesNum, simple);
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
                    correctInput = mainApp->AddCitizen(name, id, year, countyNum);
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
                        correctInput = mainApp->AddCitizen(name, id, year, countyNum);
                    }
                    break;
                case options::AddParty:
                    cout << "Enter the party name" << endl;
                    cin >> name;
                    cout << "Enter ID number of candidate for presidence" << endl;
                    cin >> id;
                    correctInput = mainApp->AddParty(name, id);
                    while (!correctInput)
                    {
                        cout << "This citizen doesn't exist,therefore he can't be a candidate." << endl <<
                            "please enter a correct ID of an existing citizen." << endl;
                        cin >> id;
                        correctInput = mainApp->AddParty(name, id);
                    }
                    break;
                case options::AddDelegate:
                    cout << "Enter the citizen ID" << endl;
                    cin >> id;
                    cout << "Enter party serial number" << endl;
                    cin >> partyNum;
                    cout << "Enter serial number of county" << endl;
                    cin >> countyNum;
                    correctInput = mainApp->AddCitizenAsDelegate(id, partyNum, countyNum);
                    while (!correctInput)
                    {
                        cout << "Please enter a correct: citizen ID , party serial number and county number." << endl;
                        cout << "Enter the citizen ID" << endl;
                        cin >> id;
                        cout << "Enter party serial number" << endl;
                        cin >> partyNum;
                        cout << "Enter serial number of county" << endl;
                        cin >> countyNum;
                        correctInput = mainApp->AddCitizenAsDelegate(id, partyNum, countyNum);
                    }
                    break;
                case options::DisplayCounties:
                    mainApp->PrintAllCounties();
                    break;
                case options::DisplayCitizens:
                    mainApp->PrintAllCitizens();
                    break;
                case options::DisplayParties:
                    mainApp->PrintAllParties();
                    break;
                case options::Vote:
                    cout << "Enter the citizen ID" << endl;
                    cin >> id;
                    cout << "Enter Party Serial number" << endl;
                    cin >> partyNum;
                    correctInput = mainApp->Vote(id, partyNum);
                    while (!correctInput)
                    {
                        cout << "This citizen has already voted / Citizen ID or Party Serial number was invalid. please enter them again." << endl;
                        cout << "Enter the citizen ID" << endl;
                        cin >> id;
                        cout << "Enter Party Serial number" << endl;
                        cin >> partyNum;
                        correctInput = mainApp->Vote(id, partyNum);
                    }
                    break;
                case options::ShowRes:
                    mainApp->printVotes();
                    break;
                case options::Exit:
                    cout << "You have exited the Election round. " << endl;
                    delete mainApp;
                    delete date;
                    exit = true;
                    break;
                case options::Save:
                    cout << "Please enter the file name you want to save into" << endl;
                    cin >> fname;
                    outfile.open(fname, ios::binary | ios::out);
                    mainApp->saveApp(outfile);
                    outfile.close();
                    break;
                case options::Load:
                    cout << "Please enter the file name you want to load" << endl;
                    cin >> fname;
                    infile.open(fname, ios::binary | ios::in);
                    if (!infile.is_open())
                    {
                        cout << "File name wasn't found";
                        exit = true;
                        break;
                    }
                    date = new Date();
                    int simple;
                    infile.read(rcastc(&simple), sizeof(simple));
                    if (simple)
                        mainApp = new SimpleApp(date,0);
                    else
                        mainApp = new RegularApp(date);
                    mainApp->loadApp(infile);
                    infile.close();
                    break;
                default:
                    cout << "Please select an option between 1-12." << endl;
                    break;
                }
            }
            return 0;
}
