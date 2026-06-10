
#ifndef UTILITIES_H
#define UTILITIES_H

#include "Business.h"

bool regNumberExists(
    Business* businesses[],
    int count,
    std::string regNo
);

int searchBusiness(
    Business* businesses[],
    int count,
    std::string regNo
);

void registerBusiness(
    Business* businesses[],
    int& count
);

void displayAllBusinesses(
    Business* businesses[],
    int count
);

void calculateAllFees(
    Business* businesses[],
    int count
);

void searchAndDisplayBusiness(
    Business* businesses[],
    int count
);

void editBusinessName(
    Business* businesses[],
    int count
);

void saveToFile(
    Business* businesses[],
    int count
);

void displayMenu();

#endif
