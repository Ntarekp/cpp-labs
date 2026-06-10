

// ParkingSlot.cpp
#include "ParkingSlot.h"
#include <iostream>
#include <iomanip>

void ParkingSlot::print() const
{
    std::cout << std::left
              << std::setw(8)  << slotId
              << std::setw(14) << vehicleTypeToString(vehicleType)
              << std::setw(12) << zone
              << std::setw(12) << slotStatusToString(status)
              << "\n";
}
