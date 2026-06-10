
// ParkingRecord.cpp

#include "ParkingRecord.h"
#include <iostream>
#include <iomanip>
#include <ctime>

void ParkingRecord::print() const {
    char entryBuf[32], exitBuf[32];
    std::tm* t1 = std::localtime(&entryTime);
    std::strftime(entryBuf, sizeof(entryBuf), "%Y-%m-%d %H:%M:%S", t1);
    std::tm* t2 = std::localtime(&exitTime);
    std::strftime(exitBuf,  sizeof(exitBuf),  "%Y-%m-%d %H:%M:%S", t2);

    std::cout << std::left
              << std::setw(16) << plate
              << std::setw(14) << vehicleTypeToString(vehicleType)
              << std::setw(8)  << slotId
              << std::setw(10) << zone
              << std::setw(22) << entryBuf
              << std::setw(22) << exitBuf
              << std::setw(8)  << durationHours
              << std::fixed    << std::setprecision(0)
              << feeCharged    << " RWF"
              << "\n";
}
