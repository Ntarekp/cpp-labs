// ============================================================
// ParkingSlot.cpp
// Implements all ParkingSlot methods.
// ============================================================

#include "ParkingSlot.h"
#include <iostream>
#include <iomanip>

// Constructor: slot starts as AVAILABLE with no occupying vehicle
ParkingSlot::ParkingSlot(const std::string& id,
                         VehicleType type,
                         const std::string& zone)
    : slotID(id), supportedType(type), zone(zone),
      status(SlotStatus::AVAILABLE), occupiedByPlate("") {}

// --- Getters ---
std::string ParkingSlot::getSlotID()          const { return slotID; }
VehicleType ParkingSlot::getSupportedType()   const { return supportedType; }
std::string ParkingSlot::getZone()            const { return zone; }
SlotStatus  ParkingSlot::getStatus()          const { return status; }
std::string ParkingSlot::getOccupiedByPlate() const { return occupiedByPlate; }

bool ParkingSlot::isAvailable() const {
    return status == SlotStatus::AVAILABLE;
}

// Occupy: transition AVAILABLE → OCCUPIED and record which plate
void ParkingSlot::occupy(const std::string& plate) {
    status = SlotStatus::OCCUPIED;
    occupiedByPlate = plate;
}

// Release: transition OCCUPIED → AVAILABLE and clear plate record
void ParkingSlot::release() {
    status = SlotStatus::AVAILABLE;
    occupiedByPlate = "";
}

// Display a formatted row of slot information
void ParkingSlot::display() const {
    std::string statusStr = isAvailable() ? "Available" : "Occupied";
    std::string plateInfo = isAvailable() ? "-" : occupiedByPlate;

    std::cout << std::left
              << std::setw(10) << slotID
              << std::setw(14) << vehicleTypeToString(supportedType)
              << std::setw(12) << zone
              << std::setw(12) << statusStr
              << std::setw(12) << plateInfo
              << "\n";
}
