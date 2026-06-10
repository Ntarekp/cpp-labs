
// Vehicle.cpp
// Implementation of Vehicle display method.

#include "Vehicle.h"
#include <iostream>
#include <iomanip>
#include <ctime>

void Vehicle::print() const
{
    // Format the entry time into a readable string
    char buf[32];
    std::tm* tm_info = std::localtime(&entryTime);
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm_info);

    std::cout << std::left
              << std::setw(16) << plate
              << std::setw(14) << vehicleTypeToString(vehicleType)
              << std::setw(22) << buf
              << std::setw(10) << slotId
              << "\n";
}
