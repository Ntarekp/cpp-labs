#include "Utilities.h"

#include "SoleProprietorship.h"
#include "Partnership.h"
#include "Corporation.h"

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

bool regNumberExists(
    Business* businesses[],
    int count,
    string regNo)
{
    for(int i = 0; i < count; i++)
    {
        if(businesses[i]->getRegNumber() == regNo)
        {
            return true;
        }
    }

    return false;
}

int searchBusiness(
    Business* businesses[],
    int count,
    string regNo)
{
    for(int i = 0; i < count; i++)
    {
        if(businesses[i]->getRegNumber() == regNo)
        {
            return i;
        }
    }

    return -1;
}

void registerBusiness(
    Business* businesses[],
    int& count)
{
    int choice;

    string regNo;
    string name;
    string owner;
    string date;

    cout << "\n===== BUSINESS TYPES =====\n";
    cout << "1. Sole Proprietorship\n";
    cout << "2. Partnership\n";
    cout << "3. Corporation\n";

    cout << "\nEnter choice: ";
    cin >> choice;
    cin.ignore();

    cout << "Registration Number: ";
    getline(cin, regNo);

    if(regNumberExists(
        businesses,
        count,
        regNo))
    {
        cout << "\nRegistration Number already exists.\n";
        return;
    }

    cout << "Business Name: ";
    getline(cin, name);

    cout << "Owner Name: ";
    getline(cin, owner);

    cout << "Registration Date: ";
    getline(cin, date);

    switch(choice)
    {
        case 1:
        {
            double turnover;

            do
            {
                cout << "Annual Turnover: ";
                cin >> turnover;

                if(turnover <= 0)
                {
                    cout << "Must be positive.\n";
                }

            } while(turnover <= 0);

            businesses[count] =
                new SoleProprietorship(
                    regNo,
                    name,
                    owner,
                    date,
                    turnover
                );

            count++;

            break;
        }

        case 2:
        {
            int partners;

            do
            {
                cout << "Number of Partners: ";
                cin >> partners;

                if(partners <= 0)
                {
                    cout << "Must be positive.\n";
                }

            } while(partners <= 0);

            businesses[count] =
                new Partnership(
                    regNo,
                    name,
                    owner,
                    date,
                    partners
                );

            count++;

            break;
        }

        case 3:
        {
            int boardSize;
            double capital;

            do
            {
                cout << "Board Size: ";
                cin >> boardSize;

                if(boardSize <= 0)
                {
                    cout << "Must be positive.\n";
                }

            } while(boardSize <= 0);

            do
            {
                cout << "Share Capital: ";
                cin >> capital;

                if(capital <= 0)
                {
                    cout << "Must be positive.\n";
                }

            } while(capital <= 0);

            businesses[count] =
                new Corporation(
                    regNo,
                    name,
                    owner,
                    date,
                    boardSize,
                    capital
                );

            count++;

            break;
        }

        default:
        {
            cout << "\nInvalid Business Type.\n";
            return;
        }
    }

    cout << "\nBusiness Registered Successfully.\n";
}

void calculateAllFees(
    Business* businesses[],
    int count)
{
    if(count == 0)
    {
        cout << "\nNo businesses registered.\n";
        return;
    }

    cout << "\n";

    cout << left
         << setw(15) << "Reg Number"
         << setw(25) << "Business Name"
         << setw(20) << "Type"
         << setw(15) << "Fee(RWF)"
         << endl;

    cout << string(75, '-') << endl;

    for(int i = 0; i < count; i++)
    {
        cout << left
             << setw(15)
             << businesses[i]->getRegNumber()

             << setw(25)
             << businesses[i]->getBusinessName()

             << setw(20)
             << businesses[i]->getType()

             << setw(15)
             << businesses[i]->calculateFee()

             << endl;
    }
}

void displayAllBusinesses(
    Business* businesses[],
    int count)
{
    if(count == 0)
    {
        cout << "\nNo businesses registered.\n";
        return;
    }

    cout << "\n";

    for(int i = 0; i < count; i++)
    {
        cout << "\n=========================\n";

        businesses[i]->display();

        cout << "=========================\n";
    }
}

void searchAndDisplayBusiness(
    Business* businesses[],
    int count)
{
    string regNo;

    cout << "\nEnter Registration Number: ";
    getline(cin, regNo);

    int index =
        searchBusiness(
            businesses,
            count,
            regNo
        );

    if(index == -1)
    {
        cout << "\nBusiness Not Found.\n";
        return;
    }

    cout << "\nBusiness Found\n";
    cout << "====================\n";

    businesses[index]->display();
}

void editBusinessName(
    Business* businesses[],
    int count)
{
    string regNo;

    cout << "\nEnter Registration Number: ";
    getline(cin, regNo);

    int index =
        searchBusiness(
            businesses,
            count,
            regNo
        );

    if(index == -1)
    {
        cout << "\nBusiness Not Found.\n";
        return;
    }

    string newName;

    cout << "Enter New Business Name: ";
    getline(cin, newName);

    businesses[index]->
        setBusinessName(newName);

    cout << "\nBusiness Name Updated Successfully.\n";
}

void saveToFile(
    Business* businesses[],
    int count)
{
    ofstream file("businesses.txt");

    if(!file)
    {
        cout << "\nFailed to open file.\n";
        return;
    }

    file << left
         << setw(15) << "RegNumber"
         << setw(25) << "BusinessName"
         << setw(20) << "Type"
         << setw(15) << "Fee(RWF)"
         << endl;

    for(int i = 0; i < count; i++)
    {
        file << left
             << setw(15)
             << businesses[i]->getRegNumber()

             << setw(25)
             << businesses[i]->getBusinessName()

             << setw(20)
             << businesses[i]->getType()

             << setw(15)
             << businesses[i]->calculateFee()

             << endl;
    }

    file.close();

    cout << "\nData Saved Successfully.\n";
}

void displayMenu()
{
    cout << "\n";
    cout << "=====================================\n";
    cout << " RDB BUSINESS REGISTRATION SYSTEM\n";
    cout << "=====================================\n";
    cout << "1. Register New Business\n";
    cout << "2. Calculate Registration Fees\n";
    cout << "3. Edit Business Name\n";
    cout << "4. Search Business\n";
    cout << "5. Display All Businesses\n";
    cout << "6. Save To File\n";
    cout << "7. Exit\n";
    cout << "=====================================\n";
    cout << "Enter Choice: ";
}
