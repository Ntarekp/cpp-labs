#include "Customer.h"

using namespace std;

Customer::Customer()
{
    customerID = "";
    fullName = "";
    district = "";
    category = "";
    monthlyConsumption = 0;
    billComputed = false;
}

Customer::Customer(
    string id,
    string name,
    string district,
    string category,
    double consumption)
{
    customerID = id;
    fullName = name;
    this->district = district;
    this->category = category;
    monthlyConsumption = consumption;
    billComputed = false;
}

string Customer::getCustomerID() const
{
    return customerID;
}

string Customer::getFullName() const
{
    return fullName;
}

string Customer::getDistrict() const
{
    return district;
}

string Customer::getCategory() const
{
    return category;
}

double Customer::getConsumption() const
{
    return monthlyConsumption;
}

bool Customer::isBillComputed() const
{
    return billComputed;
}

void Customer::setFullName(string name)
{
    fullName = name;
}

void Customer::setCategory(string category)
{
    this->category = category;
}

void Customer::setConsumption(double consumption)
{
    monthlyConsumption = consumption;
}

void Customer::setBillComputed(bool status)
{
    billComputed = status;
}
