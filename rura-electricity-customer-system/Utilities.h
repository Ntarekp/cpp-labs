#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include "Customer.h"

double calculateBill(
    std::string category,
    double consumption
);

bool isValidCategory(
    std::string category
);

bool idExists(
    Customer customers[],
    int count,
    std::string id
);

int searchCustomer(
    Customer customers[],
    int count,
    std::string id
);

void addCustomer(
    Customer customers[],
    int& count
);

void displayCustomers(
    Customer customers[],
    int count
);

void editCustomer(
    Customer customers[],
    int count
);

void searchAndDisplayCustomer(
    Customer customers[],
    int count
);

void saveToFile(
    Customer customers[],
    int count
);

void displayMenu();

#endif
