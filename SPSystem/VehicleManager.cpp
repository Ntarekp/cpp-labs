

// VehicleManager.cpp
#include "VehicleManager.h"
#include <iostream>
#include <iomanip>

bool VehicleManager::parkVehicle(const std::string& plate,
                                 VehicleType        vtype,
                                 std::time_t        entryTime,
                                 const std::string& slotId)
{
    if (activeVehicles.count(plate)) return false;
    activeVehicles.emplace(plate, Vehicle(plate, vtype, entryTime, slotId));
    return true;
}

bool VehicleManager::isParked(const std::string& plate) const
{
    return activeVehicles.count(plate) > 0;
}

const Vehicle* VehicleManager::getVehicle(const std::string& plate) const
{
    auto it = activeVehicles.find(plate);
    return (it != activeVehicles.end()) ? &(it->second) : nullptr;
}

bool VehicleManager::removeVehicle(const std::string& plate)
{
    return activeVehicles.erase(plate) > 0;
}

void VehicleManager::printParkedVehicles() const
{
    if (activeVehicles.empty())
    {
        std::cout << "  No vehicles currently parked.\n";
        return;
    }
    std::cout << std::left
              << std::setw(16) << "Plate Number"
              << std::setw(14) << "Vehicle Type"
              << std::setw(22) << "Entry Time"
              << std::setw(10) << "Slot ID"
              << "\n"
              << std::string(62, '-') << "\n";
    for (const auto& pair : activeVehicles)
    {
        pair.second.print();
    }
}

#include <fstream>
#include <sstream>

void VehicleManager::saveToFile(const std::string& filename) const
{
    std::ofstream outFile(filename);
    if (!outFile) return;
    for (const auto& pair : activeVehicles)
    {
        const Vehicle& v = pair.second;
        // Format: Plate|Type|EntryTime|SlotId
        outFile << v.getPlate() << "|"
                << static_cast<int>(v.getVehicleType()) << "|"
                << v.getEntryTime() << "|"
                << v.getSlotId() << "\n";
    }
}

void VehicleManager::loadFromFile(const std::string& filename)
{
    std::ifstream inFile(filename);
    if (!inFile) return;

    activeVehicles.clear();
    std::string line;
    while (std::getline(inFile, line))
    {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string plate, typeStr, entryStr, slotId;

        if (std::getline(ss, plate, '|') &&
                std::getline(ss, typeStr, '|') &&
                std::getline(ss, entryStr, '|') &&
                std::getline(ss, slotId, '|'))
        {

            VehicleType vt = static_cast<VehicleType>(std::stoi(typeStr));
            std::time_t entry = static_cast<std::time_t>(std::stoll(entryStr));

            activeVehicles.emplace(plate, Vehicle(plate, vt, entry, slotId));
        }
    }
}
