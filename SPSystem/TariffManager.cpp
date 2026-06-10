
// TariffManager.cpp

#include "TariffManager.h"
#include <iostream>
#include <iomanip>

void TariffManager::printRates() const
{
    std::cout << "\n  ┌------------------------------------------------------------------------─┐\n";
    std::cout << "  │        Current Parking Tariffs       │\n";
    std::cout << "  ├------------------------------------┬------------------------------------┤\n";
    std::cout << "  │  Vehicle Type    │  Rate (RWF/hr)   │\n";
    std::cout << "  ├------------------------------------┼------------------------------------┤\n";
    for (auto& pair : rates)
    {
        std::cout << "  │  "
                  << std::left  << std::setw(16) << vehicleTypeToString(pair.first)
                  << "│  "
                  << std::right << std::setw(14) << std::fixed << std::setprecision(0)
                  << pair.second
                  << "  │\n";
    }
    std::cout << "  +------------------+------------------+\n";
}

#include <fstream>

void TariffManager::saveToFile(const std::string& filename) const
{
    std::ofstream outFile(filename);
    if (!outFile) return;
    for (const auto& pair : rates)
    {
        outFile << static_cast<int>(pair.first) << " " << pair.second << "\n";
    }
}

void TariffManager::loadFromFile(const std::string& filename)
{
    std::ifstream inFile(filename);
    if (!inFile) return;
    int type;
    double rate;
    while (inFile >> type >> rate)
    {
        rates[static_cast<VehicleType>(type)] = rate;
    }
}
