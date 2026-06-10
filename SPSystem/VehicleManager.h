
// VehicleManager.h
// Manages currently parked vehicles (active sessions).
//
// DSA Choice:
//   - std::unordered_map<plate, Vehicle> → O(1) average lookup/insert/delete
//     by plate number. Plate is the natural key (unique identifier).
//   - This is the right structure because the most frequent operations are:
//     "is this plate already parked?" (entry check) and
//     "get vehicle by plate on exit" — both O(1) with hash map.

#ifndef VEHICLEMANAGER_H
#define VEHICLEMANAGER_H

#include <unordered_map>
#include <string>
#include "Vehicle.h"

class VehicleManager
{
private:
    // plate → Vehicle (active parked vehicles only)
    std::unordered_map<std::string, Vehicle> activeVehicles;

public:
    // ---- Park a vehicle ----------------------------------------------------------------------------------------------------------------─
    // Returns false if plate is already parked
    bool parkVehicle(const std::string& plate,
                     VehicleType        vtype,
                     std::time_t        entryTime,
                     const std::string& slotId);

    // ---- Check if a vehicle is currently parked ----------------------------------------------------------------─
    bool isParked(const std::string& plate) const;

    // ---- Get active vehicle by plate ----------------------------------------------------------------------------------------
    // Returns nullptr if not found
    const Vehicle* getVehicle(const std::string& plate) const;

    // ---- Remove vehicle on exit ------------------------------------------------------------------------------------------------─
    // Returns false if plate not found
    bool removeVehicle(const std::string& plate);

    // ---- Display all currently parked vehicles --------------------------------------------------------------------
    void printParkedVehicles() const;

    // ---- Count active vehicles ----------------------------------------------------------------------------------------------------
    int count() const
    {
        return static_cast<int>(activeVehicles.size());
    }

    // ---- Persistence --------------------------------------------------------------------------------------------------------------------─
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif // VEHICLEMANAGER_H
