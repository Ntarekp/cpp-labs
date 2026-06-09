
#include <iostream>
#include <iomanip>
#include <fstream>

#include "Utilities.h"

using namespace std;

double calculateBill(
    string category,
    double consumption)
{
    if(category == "Residential")
        return consumption * 183;

    else if(category == "Commercial")
        return consumption * 214;

    else if(category == "Industrial")
        return consumption * 198;

    return 0;
}

bool isValidCategory(string category)
{
    return category == "Residential" ||
           category == "Commercial" ||
           category == "Industrial";
}

bool idExists(
    Customer customers[],
    int count,
    string id)
{
    for(int i = 0; i < count; i++)
    {
        if(customers[i].getCustomerID() == id)
            return true;
    }

    return false;
}

int searchCustomer(
    Customer customers[],
    int count,
    string id)
{
    for(int i = 0; i < count; i++)
    {
        if(customers[i].getCustomerID() == id)
            return i;
    }

    return -1;
}

void addCustomer(
    Customer customers[],
    int& count)
{
    string id;
    string name;
    string district;
    string category;
    double consumption;

    cout << "\nEnter Customer ID: ";
    getline(cin, id);

    if(idExists(customers, count, id))
    {
        cout << "Duplicate Customer ID not allowed.\n";
        return;
    }

    cout << "Enter Full Name: ";
    getline(cin, name);

    cout << "Enter District: ";
    getline(cin, district);

    do
    {
        cout << "Enter Category "
             << "(Residential/Commercial/Industrial): ";

        getline(cin, category);

    } while(!isValidCategory(category));

    do
    {
        cout << "Enter Monthly Consumption (kWh): ";
        cin >> consumption;

        if(consumption <= 0)
            cout << "Consumption must be positive.\n";

    } while(consumption <= 0);

    cin.ignore();

    customers[count] =
        Customer(
            id,
            name,
            district,
            category,
            consumption
        );

    count++;

    cout << "Customer Added Successfully.\n";
}

void displayCustomers(
    Customer customers[],
    int count)
{
    cout << "\n";

    cout << left
         << setw(12) << "ID"
         << setw(25) << "Name"
         << setw(15) << "Category"
         << setw(10) << "kWh"
         << setw(15) << "Bill(RWF)"
         << endl;

    cout << string(80, '-') << endl;

    for(int i = 0; i < count; i++)
    {
        double bill =
            calculateBill(
                customers[i].getCategory(),
                customers[i].getConsumption()
            );

        customers[i].setBillComputed(true);

        cout << setw(12)
             << customers[i].getCustomerID()

             << setw(25)
             << customers[i].getFullName()

             << setw(15)
             << customers[i].getCategory()

             << setw(10)
             << customers[i].getConsumption()

             << setw(15)
             << bill

             << endl;
    }
}

void editCustomer(
    Customer customers[],
    int count)
{
    string id;

    cout << "Enter Customer ID: ";
    getline(cin, id);

    int index =
        searchCustomer(
            customers,
            count,
            id
        );

    if(index == -1)
    {
        cout << "Customer not found.\n";
        return;
    }

    string name;
    string category;

    cout << "Enter New Name: ";
    getline(cin, name);

    do
    {
        cout << "Enter New Category: ";
        getline(cin, category);

    } while(!isValidCategory(category));

    customers[index].setFullName(name);
    customers[index].setCategory(category);

    cout << "Customer Updated Successfully.\n";
}

void searchAndDisplayCustomer(
    Customer customers[],
    int count)
{
    string id;

    cout << "Enter Customer ID: ";
    getline(cin, id);

    int index =
        searchCustomer(
            customers,
            count,
            id
        );

    if(index == -1)
    {
        cout << "Customer not found.\n";
        return;
    }

    double bill =
        calculateBill(
            customers[index].getCategory(),
            customers[index].getConsumption()
        );

    cout << "\nCustomer Details\n";

    cout << "ID: "
         << customers[index].getCustomerID()
         << endl;

    cout << "Name: "
         << customers[index].getFullName()
         << endl;

    cout << "District: "
         << customers[index].getDistrict()
         << endl;

    cout << "Category: "
         << customers[index].getCategory()
         << endl;

    cout << "Consumption: "
         << customers[index].getConsumption()
         << " kWh\n";

    cout << "Bill: "
         << bill
         << " RWF\n";
}

void saveToFile(
    Customer customers[],
    int count)
{
    ofstream file("customers.txt");

    if(!file)
    {
        cout << "Error opening file.\n";
        return;
    }

    file
    << "Index\tID\tName\tCategory\tkWh\tBill\n";

    for(int i = 0; i < count; i++)
    {
        double bill =
            calculateBill(
                customers[i].getCategory(),
                customers[i].getConsumption()
            );

        file
        << i + 1 << "\t"
        << customers[i].getCustomerID() << "\t"
        << customers[i].getFullName() << "\t"
        << customers[i].getCategory() << "\t"
        << customers[i].getConsumption() << "\t"
        << bill << "\n";
    }

    file.close();

    cout << "Data saved successfully.\n";
}

void displayMenu()
{
    cout << "\n";
    cout << "=======================================\n";
    cout << " RURA CUSTOMER MANAGEMENT SYSTEM\n";
    cout << "=======================================\n";
    cout << "1. Add New Customer\n";
    cout << "2. Calculate and Display Bills\n";
    cout << "3. Edit Customer\n";
    cout << "4. Search Customer by ID\n";
    cout << "5. Display All Customers\n";
    cout << "6. Save To File\n";
    cout << "7. Exit\n";
    cout << "=======================================\n";
    cout << "Enter Choice: ";
}
