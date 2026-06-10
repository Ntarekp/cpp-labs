
// ============================================================
// Vehicle.cpp
// Implements Vehicle class methods.
// ============================================================

#include "Vehicle.h"
#include <iostream>
#include <iomanip>
#include <cstring>

// Constructor: sets entry time to "now" using time()
Vehicle::Vehicle(const std::string& plate,
                 VehicleType type,
                 const std::string& slotID)
    : plate(plate), type(type),
      entryTime(std::time(nullptr)), assignedSlot(slotID) {}

// --- Getters ---
std::string Vehicle::getPlate()        const { return plate; }
VehicleType Vehicle::getType()         const { return type; }
std::time_t Vehicle::getEntryTime()    const { return entryTime; }
std::string Vehicle::getAssignedSlot() const { return assignedSlot; }

// Format time_t as "YYYY-MM-DD HH:MM:SS"
std::string Vehicle::getEntryTimeStr() const {
    char buf[32];
    std::tm* tm_info = std::localtime(&entryTime);
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm_info);
    return std::string(buf);
}

// Display a formatted row of currently-parked vehicle info
void Vehicle::display() const {
    std::cout << std::left
              << std::setw(16) << plate
              << std::setw(14) << vehicleTypeToString(type)
              << std::setw(22) << getEntryTimeStr()
              << std::setw(10) << assignedSlot
              << "\n";
}
