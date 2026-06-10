
#include "Corporation.h"
#include <iostream>

using namespace std;

Corporation::Corporation(
    string regNo,
    string name,
    string owner,
    string date,
    int board,
    double capital)
    : Business(
          regNo,
          name,
          owner,
          date)
{
    boardSize = board;
    shareCapital = capital;
}

double Corporation::calculateFee() const
{
    double fee =
        shareCapital * 0.0005;

    if(fee < 500000)
    {
        fee = 500000;
    }

    return fee;
}

string Corporation::getType() const
{
    return "Corporation";
}

void Corporation::display() const
{
    Business::display();

    cout << "Business Type: "
         << getType() << endl;

    cout << "Board Size: "
         << boardSize << endl;

    cout << "Share Capital: "
         << shareCapital << endl;

    cout << "Registration Fee: "
         << calculateFee()
         << " RWF\n";
}
