
// Vehicle.h
// Represents a vehicle currently parked in the system.
// Stores entry details and the slot assigned to this vehicle.

#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <ctime>
#include "types.h"

class Vehicle {
private:
    std::string plate;       // Unique plate number, e.g. "RAB 123 A"
    VehicleType vehicleType; // Motorcycle / Car / Truck
    std::time_t entryTime;   // Unix timestamp of entry
    std::string slotId;      // The slot this vehicle occupies

public:
    // ── Constructor ───────────────────────────────────────────────────────────
    Vehicle(const std::string& plateNum,
            VehicleType        vtype,
            std::time_t        entry,
            const std::string& assignedSlot)
        : plate(plateNum),
          vehicleType(vtype),
          entryTime(entry),
          slotId(assignedSlot)
    {}

    // ── Getters ───────────────────────────────────────────────────────────────
    const std::string& getPlate()       const { return plate;       }
    VehicleType        getVehicleType() const { return vehicleType; }
    std::time_t        getEntryTime()   const { return entryTime;   }
    const std::string& getSlotId()      const { return slotId;      }

    // ── Display helper ────────────────────────────────────────────────────────
    void print() const;
};

#endif // VEHICLE_H
