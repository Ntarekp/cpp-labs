// ============================================================
// Vehicle.h
// Declares the Vehicle class representing a vehicle currently
// parked in the system (active session).
// ============================================================

#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <ctime>
#include "VehicleType.h"

// ---------------------------------------------------------------
// Vehicle: Represents an active parking session for a vehicle.
// Stores entry time and the slot assigned to this vehicle.
// OOP: Encapsulates vehicle state; no public direct member access.
// ---------------------------------------------------------------
class Vehicle {
private:
    std::string plate;       // Unique plate number, e.g., "RAC 123 A"
    VehicleType type;        // Type of vehicle
    std::time_t entryTime;   // Unix timestamp when vehicle entered
    std::string assignedSlot;// ID of the slot this vehicle is parked in

public:
    // Constructor: captures entry time automatically
    Vehicle(const std::string& plate,
            VehicleType type,
            const std::string& slotID);

    // --- Getters ---
    std::string  getPlate()        const;
    VehicleType  getType()         const;
    std::time_t  getEntryTime()    const;
    std::string  getAssignedSlot() const;

    // Format entry time as a readable string
    std::string  getEntryTimeStr() const;

    // Display vehicle info to console
    void display() const;
};

#endif // VEHICLE_H
