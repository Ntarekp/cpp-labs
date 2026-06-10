
// SlotManager.h
// Manages all parking slots in the system.
//
// DSA Choice:
//   - std::unordered_map<slotId, ParkingSlot>  → O(1) average lookup/insert by ID
//   - std::map<VehicleType, std::vector<slotId>> → grouped index for fast
//     "find first available slot of type X" without scanning all slots
//
// This two-layer design avoids O(n) linear scan every time a vehicle enters.

#ifndef SLOTMANAGER_H
#define SLOTMANAGER_H

#include <unordered_map>
#include <map>
#include <vector>
#include <string>
#include "ParkingSlot.h"

class SlotManager {
private:
    // Primary store: slotId → ParkingSlot object
    std::unordered_map<std::string, ParkingSlot> slots;

    // Secondary index: VehicleType → list of slotIds that support it
    // Used to quickly find available slots per type
    std::map<VehicleType, std::vector<std::string>> slotIndex;

public:
    // ── Add a new slot ─────────────────────────────────────────────────────────
    // Returns false if slotId already exists
    bool addSlot(const std::string& slotId, VehicleType vtype, const std::string& zone);

    // ── Find first available slot for a given vehicle type ─────────────────────
    // Returns pointer to slot or nullptr if none available
    ParkingSlot* findAvailableSlot(VehicleType vtype);

    // ── Get slot by ID ─────────────────────────────────────────────────────────
    ParkingSlot* getSlot(const std::string& slotId);

    // ── Check if a slot ID already exists ─────────────────────────────────────
    bool slotExists(const std::string& slotId) const;

    // ── Count available slots by type ─────────────────────────────────────────
    int countAvailable(VehicleType vtype) const;

    // ── Display all slots ──────────────────────────────────────────────────────
    void printAllSlots() const;

    // ── Display only available slots ──────────────────────────────────────────
    void printAvailableSlots() const;

    // ── Total slot count ──────────────────────────────────────────────────────
    int totalSlots() const { return static_cast<int>(slots.size()); }

    // ── Persistence ───────────────────────────────────────────────────────────
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif // SLOTMANAGER_H
