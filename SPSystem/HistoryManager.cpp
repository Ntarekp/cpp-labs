

// HistoryManager.cpp
#include "HistoryManager.h"
#include <iostream>
#include <iomanip>
#include <ctime>

void HistoryManager::addRecord(const ParkingRecord& record) {
    history.push_back(record);
}

void HistoryManager::printPlateHistory(const std::string& plate) const {
    bool found = false;
    std::cout << std::left
              << std::setw(16) << "Plate"
              << std::setw(14) << "Type"
              << std::setw(8)  << "Slot"
              << std::setw(10) << "Zone"
              << std::setw(22) << "Entry"
              << std::setw(22) << "Exit"
              << std::setw(8)  << "Hours"
              << "Fee" << "\n"
              << std::string(110, '-') << "\n";

    for (const auto& record : history) {
        if (record.getPlate() == plate) {
            record.print();
            found = true;
        }
    }
    if (!found) std::cout << "  No history found for plate: " << plate << "\n";
}

void HistoryManager::printAllHistory() const {
    if (history.empty()) {
        std::cout << "  Parking history is empty.\n";
        return;
    }
    std::cout << std::left
              << std::setw(16) << "Plate"
              << std::setw(14) << "Type"
              << std::setw(8)  << "Slot"
              << std::setw(10) << "Zone"
              << std::setw(22) << "Entry"
              << std::setw(22) << "Exit"
              << std::setw(8)  << "Hours"
              << "Fee" << "\n"
              << std::string(110, '-') << "\n";

    for (const auto& record : history) {
        record.print();
    }
}

void HistoryManager::printDailyRevenue(const std::string& dateStr) const {
    double total = 0;
    int count = 0;

    for (const auto& record : history) {
        std::time_t exitTime = record.getExitTime();
        char buf[16];
        std::tm* tm_info = std::localtime(&exitTime);
        std::strftime(buf, sizeof(buf), "%Y-%m-%d", tm_info);

        if (std::string(buf) == dateStr) {
            total += record.getFeeCharged();
            count++;
        }
    }

    std::cout << "  Revenue Report for: " << dateStr << "\n";
    std::cout << "  Total Transactions:  " << count << "\n";
    std::cout << "  Total Revenue:       " << std::fixed << std::setprecision(0) << total << " RWF\n";
}

#include <fstream>
#include <sstream>

void HistoryManager::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile) return;
    for (const auto& r : history) {
        // Format: Plate|Type|SlotId|Zone|Entry|Exit|Hours|Fee
        outFile << r.getPlate() << "|"
                << static_cast<int>(r.getVehicleType()) << "|"
                << r.getSlotId() << "|"
                << r.getZone() << "|"
                << r.getEntryTime() << "|"
                << r.getExitTime() << "|"
                << r.getDurationHours() << "|"
                << r.getFeeCharged() << "\n";
    }
}

void HistoryManager::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) return;

    history.clear();
    std::string line;
    while (std::getline(inFile, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string plate, typeStr, slotId, zone, entryStr, exitStr, hoursStr, feeStr;

        if (std::getline(ss, plate, '|') &&
            std::getline(ss, typeStr, '|') &&
            std::getline(ss, slotId, '|') &&
            std::getline(ss, zone, '|') &&
            std::getline(ss, entryStr, '|') &&
            std::getline(ss, exitStr, '|') &&
            std::getline(ss, hoursStr, '|') &&
            std::getline(ss, feeStr, '|')) {

            VehicleType vt = static_cast<VehicleType>(std::stoi(typeStr));
            std::time_t entry = static_cast<std::time_t>(std::stoll(entryStr));
            std::time_t exit = static_cast<std::time_t>(std::stoll(exitStr));
            int hours = std::stoi(hoursStr);
            double fee = std::stod(feeStr);

            history.emplace_back(plate, vt, slotId, zone, entry, exit, hours, fee);
        }
    }
}
