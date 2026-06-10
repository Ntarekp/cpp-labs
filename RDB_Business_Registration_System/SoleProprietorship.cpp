#include "SoleProprietorship.h"
#include <iostream>

using namespace std;

SoleProprietorship::SoleProprietorship(
    string regNo,
    string name,
    string owner,
    string date,
    double turnover)
    : Business(
          regNo,
          name,
          owner,
          date)
{
    annualTurnover = turnover;
}

double SoleProprietorship::calculateFee() const
{
    double fee =
        annualTurnover * 0.001;

    if(fee < 20000)
    {
        fee = 20000;
    }

    return fee;
}

string SoleProprietorship::getType() const
{
    return "Sole Proprietorship";
}

void SoleProprietorship::display() const
{
    Business::display();

    cout << "Business Type: "
         << getType() << endl;

    cout << "Annual Turnover: "
         << annualTurnover << endl;

    cout << "Registration Fee: "
         << calculateFee()
         << " RWF\n";
}
