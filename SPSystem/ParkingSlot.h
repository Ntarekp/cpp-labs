
// ParkingSlot.h
// Represents a single physical parking slot in the system.
// Encapsulates all slot attributes and provides controlled access via getters/setters.

#ifndef PARKINGSLOT_H
#define PARKINGSLOT_H

#include <string>
#include "types.h"

class ParkingSlot {
private:
    std::string  slotId;       // Unique identifier, e.g. "A1", "B3"
    VehicleType  vehicleType;  // Which vehicle category this slot supports
    std::string  zone;         // Physical zone label, e.g. "Zone-A"
    SlotStatus   status;       // AVAILABLE or OCCUPIED

public:
    // ── Constructor ──────────────────────────────────────────────────────────
    ParkingSlot(const std::string& id,
                VehicleType       vtype,
                const std::string& zoneLabel)
        : slotId(id),
          vehicleType(vtype),
          zone(zoneLabel),
          status(SlotStatus::AVAILABLE)   // all slots start as available
    {}

    // ── Getters ──────────────────────────────────────────────────────────────
    const std::string& getSlotId()     const { return slotId;      }
    VehicleType        getVehicleType()const { return vehicleType;  }
    const std::string& getZone()       const { return zone;         }
    SlotStatus         getStatus()     const { return status;       }
    bool               isAvailable()   const { return status == SlotStatus::AVAILABLE; }

    // ── Status mutators ───────────────────────────────────────────────────────
    void occupy()   { status = SlotStatus::OCCUPIED;  }
    void release()  { status = SlotStatus::AVAILABLE; }

    // ── Display helper ────────────────────────────────────────────────────────
    void print() const;
};

#endif // PARKINGSLOT_H
