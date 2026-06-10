#include <iostream>

#include "Utilities.h"

using namespace std;

const int MAX_BUSINESSES = 100;

int main()
{
    Business* businesses[MAX_BUSINESSES];

    int businessCount = 0;

    int choice;

    do
    {
        displayMenu();

        cin >> choice;
        cin.ignore();

        switch(choice)
        {
        case 1:
            registerBusiness(
                businesses,
                businessCount
            );
            break;

        case 2:
            calculateAllFees(
                businesses,
                businessCount
            );
            break;

        case 3:
            editBusinessName(
                businesses,
                businessCount
            );
            break;

        case 4:
            searchAndDisplayBusiness(
                businesses,
                businessCount
            );
            break;

        case 5:
            displayAllBusinesses(
                businesses,
                businessCount
            );
            break;

        case 6:
            saveToFile(
                businesses,
                businessCount
            );
            break;

        case 7:
            cout
                    << "\nProgram Terminated.\n";
            break;

        default:
            cout
                    << "\nInvalid Choice.\n";
        }

    }
    while(choice != 7);

    // Memory cleanup
    for(int i = 0; i < businessCount; i++)
    {
        delete businesses[i];
    }

    return 0;
}
