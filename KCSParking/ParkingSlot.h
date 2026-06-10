
// ============================================================
// ParkingSlot.h
// Declares the ParkingSlot class.
// Each slot has a unique ID, supports a specific vehicle type,
// belongs to a zone, and tracks its occupancy status.
// ============================================================

#ifndef PARKINGSLOT_H
#define PARKINGSLOT_H

#include <string>
#include "VehicleType.h"

// Enum for slot availability status
enum class SlotStatus {
    AVAILABLE,
    OCCUPIED
};

// ---------------------------------------------------------------
// ParkingSlot: Represents a single physical parking slot.
// OOP: Encapsulates all slot-related attributes and behavior.
// ---------------------------------------------------------------
class ParkingSlot {
private:
    std::string slotID;          // Unique identifier, e.g., "A1", "B3"
    VehicleType supportedType;   // Vehicle type this slot accepts
    std::string zone;            // Zone label, e.g., "Zone A", "Zone B"
    SlotStatus  status;          // Current status: AVAILABLE or OCCUPIED
    std::string occupiedByPlate; // Plate of vehicle currently parked (empty if available)

public:
    // Constructor: initializes all fields; status defaults to AVAILABLE
    ParkingSlot(const std::string& id,
                VehicleType type,
                const std::string& zone);

    // --- Getters (read-only access to private members) ---
    std::string  getSlotID()          const;
    VehicleType  getSupportedType()   const;
    std::string  getZone()            const;
    SlotStatus   getStatus()          const;
    std::string  getOccupiedByPlate() const;

    // --- Status mutators ---
    bool isAvailable() const;              // true if slot is free
    void occupy(const std::string& plate); // Mark as occupied by given plate
    void release();                        // Mark as available again

    // Display slot info to console
    void display() const;
};

#endif // PARKINGSLOT_H
