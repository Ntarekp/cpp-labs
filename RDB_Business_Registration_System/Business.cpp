#include "Business.h"
#include <iostream>

using namespace std;

Business::Business(
    string regNo,
    string name,
    string owner,
    string date)
{
    regNumber = regNo;
    businessName = name;
    ownerName = owner;
    regDate = date;
}

Business::~Business()
{
}

string Business::getRegNumber() const
{
    return regNumber;
}

string Business::getBusinessName() const
{
    return businessName;
}

string Business::getOwnerName() const
{
    return ownerName;
}

string Business::getRegDate() const
{
    return regDate;
}

void Business::setBusinessName(string name)
{
    businessName = name;
}

void Business::display() const
{
    cout << "Registration Number: "
         << regNumber << endl;

    cout << "Business Name: "
         << businessName << endl;

    cout << "Owner Name: "
         << ownerName << endl;

    cout << "Registration Date: "
         << regDate << endl;
}
