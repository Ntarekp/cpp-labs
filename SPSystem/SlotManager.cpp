
// SlotManager.cpp

#include "SlotManager.h"
#include <iostream>
#include <iomanip>

// ---- Add slot ------------------------------------------------------------------------------------------------------------------------------------
bool SlotManager::addSlot(const std::string& slotId,
                          VehicleType        vtype,
                          const std::string& zone)
{
    if (slots.count(slotId)) return false;  // duplicate

    // Emplace constructs the ParkingSlot directly in the map
    slots.emplace(slotId, ParkingSlot(slotId, vtype, zone));

    // Register in the type index
    slotIndex[vtype].push_back(slotId);
    return true;
}

// ---- Find first available slot for a vehicle type ------------------------------------------------------------
ParkingSlot* SlotManager::findAvailableSlot(VehicleType vtype)
{
    auto it = slotIndex.find(vtype);
    if (it == slotIndex.end()) return nullptr;

    for (const std::string& id : it->second)
    {
        auto sit = slots.find(id);
        if (sit != slots.end() && sit->second.isAvailable())
        {
            return &sit->second;
        }
    }
    return nullptr;  // none available
}

// ---- Get slot by ID ------------------------------------------------------------------------------------------------------------------------
ParkingSlot* SlotManager::getSlot(const std::string& slotId)
{
    auto it = slots.find(slotId);
    return (it != slots.end()) ? &it->second : nullptr;
}

// ---- Check existence --------------------------------------------------------------------------------------------------------------------─
bool SlotManager::slotExists(const std::string& slotId) const
{
    return slots.count(slotId) > 0;
}

// ---- Count available slots for a type --------------------------------------------------------------------------------─
int SlotManager::countAvailable(VehicleType vtype) const
{
    auto it = slotIndex.find(vtype);
    if (it == slotIndex.end()) return 0;

    int count = 0;
    for (const std::string& id : it->second)
    {
        auto sit = slots.find(id);
        if (sit != slots.end() && sit->second.isAvailable()) ++count;
    }
    return count;
}

// ---- Print all slots --------------------------------------------------------------------------------------------------------------------─
void SlotManager::printAllSlots() const
{
    if (slots.empty())
    {
        std::cout << "  No slots configured.\n";
        return;
    }
    std::cout << std::left
              << std::setw(8)  << "SlotID"
              << std::setw(14) << "Vehicle Type"
              << std::setw(12) << "Zone"
              << std::setw(12) << "Status"
              << "\n"
              << std::string(46, '-') << "\n";

    for (const auto& pair : slots)
    {
        pair.second.print();
    }
}

// ---- Print only available slots ------------------------------------------------------------------------------------------------
void SlotManager::printAvailableSlots() const
{
    bool found = false;
    std::cout << std::left
              << std::setw(8)  << "SlotID"
              << std::setw(14) << "Vehicle Type"
              << std::setw(12) << "Zone"
              << std::setw(12) << "Status"
              << "\n"
              << std::string(46, '-') << "\n";

    for (const auto& pair : slots)
    {
        if (pair.second.isAvailable())
        {
            pair.second.print();
            found = true;
        }
    }
    if (!found) std::cout << "  No available slots at the moment.\n";
}

#include <fstream>
#include <sstream>

void SlotManager::saveToFile(const std::string& filename) const
{
    std::ofstream outFile(filename);
    if (!outFile) return;
    for (const auto& pair : slots)
    {
        const ParkingSlot& s = pair.second;
        // Format: ID|Type|Zone|Status
        outFile << s.getSlotId() << "|"
                << static_cast<int>(s.getVehicleType()) << "|"
                << s.getZone() << "|"
                << static_cast<int>(s.getStatus()) << "\n";
    }
}

void SlotManager::loadFromFile(const std::string& filename)
{
    std::ifstream inFile(filename);
    if (!inFile) return;

    slots.clear();
    slotIndex.clear();

    std::string line;
    while (std::getline(inFile, line))
    {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string id, typeStr, zone, statusStr;

        if (std::getline(ss, id, '|') &&
                std::getline(ss, typeStr, '|') &&
                std::getline(ss, zone, '|') &&
                std::getline(ss, statusStr, '|'))
        {

            VehicleType vt = static_cast<VehicleType>(std::stoi(typeStr));
            SlotStatus st = static_cast<SlotStatus>(std::stoi(statusStr));

            ParkingSlot slot(id, vt, zone);
            if (st == SlotStatus::OCCUPIED) slot.occupy();

            slots.emplace(id, slot);
            slotIndex[vt].push_back(id);
        }
    }
}
