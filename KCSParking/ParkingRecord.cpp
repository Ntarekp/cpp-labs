
// ============================================================
// ParkingRecord.cpp
// Implements ParkingRecord methods.
// ============================================================

#include "ParkingRecord.h"
#include <iostream>
#include <iomanip>
#include <cstring>

ParkingRecord::ParkingRecord(const std::string& plate,
                             VehicleType type,
                             const std::string& slotID,
                             std::time_t entryTime,
                             std::time_t exitTime,
                             int durationHours,
                             double rateUsed,
                             double totalFee)
    : plate(plate), type(type), slotID(slotID),
      entryTime(entryTime), exitTime(exitTime),
      durationHours(durationHours), rateUsed(rateUsed),
      totalFee(totalFee) {}

// --- Getters ---
std::string ParkingRecord::getPlate()         const { return plate; }
VehicleType ParkingRecord::getType()          const { return type; }
std::string ParkingRecord::getSlotID()        const { return slotID; }
std::time_t ParkingRecord::getEntryTime()     const { return entryTime; }
std::time_t ParkingRecord::getExitTime()      const { return exitTime; }
int         ParkingRecord::getDurationHours() const { return durationHours; }
double      ParkingRecord::getRateUsed()      const { return rateUsed; }
double      ParkingRecord::getTotalFee()      const { return totalFee; }

// Helper: format a time_t as "YYYY-MM-DD HH:MM:SS"
static std::string formatTime(std::time_t t) {
    char buf[32];
    std::tm* tm_info = std::localtime(&t);
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm_info);
    return std::string(buf);
}

std::string ParkingRecord::getEntryTimeStr() const { return formatTime(entryTime); }
std::string ParkingRecord::getExitTimeStr()  const { return formatTime(exitTime); }

// Display a formatted row for the history/revenue report
void ParkingRecord::display() const {
    std::cout << std::left
              << std::setw(16) << plate
              << std::setw(14) << vehicleTypeToString(type)
              << std::setw(8)  << slotID
              << std::setw(22) << getEntryTimeStr()
              << std::setw(22) << getExitTimeStr()
              << std::setw(10) << durationHours
              << std::setw(14) << rateUsed
              << std::setw(12) << totalFee
              << "\n";
}
