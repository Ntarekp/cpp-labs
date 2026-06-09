#include <iostream>

#include "Customer.h"
#include "Utilities.h"

using namespace std;

const int MAX_CUSTOMERS = 100;

int main()
{
    Customer customers[MAX_CUSTOMERS];
    int customerCount = 0;
    int choice;

    do
    {
        displayMenu();

        cin >> choice;
        cin.ignore();

        switch(choice)
        {
            case 1:
                addCustomer(customers, customerCount);
                break;

            case 2:
                displayCustomers(customers, customerCount);
                break;

            case 3:
                editCustomer(customers, customerCount);
                break;

            case 4:
                searchAndDisplayCustomer(
                    customers,
                    customerCount
                );
                break;

            case 5:
                displayCustomers(
                    customers,
                    customerCount
                );
                break;

            case 6:
                saveToFile(
                    customers,
                    customerCount
                );
                break;

            case 7:
                cout << "\nProgram Terminated.\n";
                break;

            default:
                cout << "\nInvalid Choice.\n";
        }

    } while(choice != 7);

    return 0;
}
