#include "Partnership.h"
#include <iostream>

using namespace std;

Partnership::Partnership(
    string regNo,
    string name,
    string owner,
    string date,
    int partners)
    : Business(
          regNo,
          name,
          owner,
          date)
{
    numPartners = partners;
}

double Partnership::calculateFee() const
{
    return numPartners * 50000;
}

string Partnership::getType() const
{
    return "Partnership";
}

void Partnership::display() const
{
    Business::display();

    cout << "Business Type: "
         << getType() << endl;

    cout << "Number of Partners: "
         << numPartners << endl;

    cout << "Registration Fee: "
         << calculateFee()
         << " RWF\n";
}
