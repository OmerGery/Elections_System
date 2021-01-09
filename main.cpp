#define _CRT_SECURE_NO_WARNINGS
#include "Date.h"
#include "Citizen.h"
#include "Party.h"
#include "CitizenList.h"
#include "County.h"
#include "CountyArr.h"
#include "CountyDelegate.h"
#include "App.h"
#include "SimpleApp.h"
#include "RegularApp.h"
#include <iostream>
#include <fstream>
using namespace std;
using namespace votes;
enum options {
    AddCounty=1, AddCitizen, AddParty, AddDelegate, DisplayCounties, DisplayCitizens, DisplayParties, Vote, ShowRes, Exit, Save, Load
}option;
enum preOptions {
    NewRound = 1, LoadVotes, PreExit
}preoption;
int main()
{ 
    ifstream infile;
    ofstream outfile;
    // WE ASSUME THAT EACH STRING(=name of county/citizen) CONTAINS ONLY ONE WORD(= no space in entered within a name) . 
    string name, fname, errorName;
    int option, delegatesNum, id, day, month, year, countyNum, partyNum, type;
    bool exit=false, prexit=false;
    App* mainApp = nullptr;
    Date date;
    int loaded = 0;
    while (!prexit)
    {
        try {
            cout << endl << "1 - Create a new Elections round" << endl << "2 - Load an exisiting Elections round" << endl << "3 - Exit" << endl;
            cout << "Choose an option" << endl;
            cin >> option;
            switch (option)
            {
            case preOptions::NewRound:
                cout << "Please enter the type of elections (0 for regular and 1 for simple)" << endl;
                cin >> type;
                if (type != SIMPLE && type != COMPLEX)
                    throw (errorName = "Round Type isn't valid (need to be 0 or 1)");
                cout << "Please enter election day" << endl;
                cin >> day;
                cout << "Please enter election month" << endl;
                cin >> month;
                cout << "Please enter election year" << endl;
                cin >> year;
                date = Date(day, month, year);
                if (type == SIMPLE) //during runtime we select which app will be constructed (using polymorphism)
                {
                    cout << "Enter number of delegates" << endl;
                    cin >> delegatesNum;
                    mainApp = new SimpleApp(date, delegatesNum);
                    if(!mainApp)
                        throw (errorName = "Memory Allocation Of App failed.");
                }
                else//type == COMPLEX
                {
                    mainApp = new RegularApp(date);
                    if (!mainApp)
                        throw (errorName = "Memory Allocation Of App failed.");
                }
                prexit = true;
                break;
            case preOptions::LoadVotes:
                cout << "Please enter the file name you want to load" << endl;
                cin >> fname;
                infile.open(fname, ios::binary | ios::in);
                if (!infile.is_open())
                    throw (errorName = "File name wasn't found");
                infile.read(rcastc(&type), sizeof(type));
                date = Date();
                if (type == SIMPLE) //during runtime we select which app will be constructed (using polymorphism)
                {
                    mainApp = new SimpleApp(date);
                    if (!mainApp)
                        throw (errorName = "Memory Allocation Of App failed.");
                }
                else//type == COMPLEX
                {
                    mainApp = new RegularApp(date);
                    if (!mainApp)
                        throw (errorName = "Memory Allocation Of App failed.");
                }
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
        catch (string error)
        {
            cout << error << endl;
        }
    }
        while (!exit)
        {
            try {
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
                cin >> type;
                cout << "Enter the County name" << endl;
                cin >> name;
                cout << "Enter number of delegates" << endl;
                cin >> delegatesNum;
                mainApp->AddCounty(name, delegatesNum, type);
                break;
            case options::AddCitizen:
                cout << "Enter the citizen name" << endl;
                cin >> name;
                cout << "Please Enter ID number" << endl;
                cin >> id;
                cout << "Please Enter year of birth" << endl;
                cin >> year;
                cout << "Please Enter serial number of county" << endl;
                cin >> countyNum;
                mainApp->AddCitizen(name, id, year, countyNum);
                break;
            case options::AddParty:
                cout << "Enter the party name" << endl;
                cin >> name;
                cout << "Enter ID number of candidate for presidence" << endl;
                cin >> id;
                mainApp->AddParty(name, id);
                break;
            case options::AddDelegate:
                cout << "Enter the citizen ID" << endl;
                cin >> id;
                cout << "Enter party serial number" << endl;
                cin >> partyNum;
                cout << "Enter serial number of county" << endl;
                cin >> countyNum;
                mainApp->AddCitizenAsDelegate(id, partyNum, countyNum);
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
                mainApp->Vote(id, partyNum);
                break;
            case options::ShowRes:
                if (loaded)
                    int x = 1;
                mainApp->printVotes();
                break;
            case options::Exit:
                cout << "You have exited the program. " << endl;
                delete mainApp;
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
                    throw (errorName = "File name wasn't found");
                delete mainApp; // delete the current app before loading the new app from file
                date = Date();
                infile.read(rcastc(&type), sizeof(type));
                if (type == SIMPLE)
                {
                    mainApp = new SimpleApp(date);
                    if (!mainApp)
                        throw (errorName = "Memory Allocation Of App failed.");
                }
                else
                {
                    mainApp = new RegularApp(date);
                           if(!mainApp)
                        throw (errorName = "Memory Allocation Of App failed.");
                }
                mainApp->loadApp(infile);
                infile.close();
                loaded = 1;
                break;
            default:
                cout << "Please select an option between 1-12." << endl;
                break;
            }
        }
        catch (string error)
        {
            cout << error << endl;
        }
    }
        return 0;
}
