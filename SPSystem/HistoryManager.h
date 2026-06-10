

// HistoryManager.h
// Manages completed parking transactions (history).
//
// DSA Choice:
//   - std::vector<ParkingRecord> → Sequential storage for audit/reporting.
//     Fast O(1) appending of new records. Ideal for traversal-heavy reports
//     like "All History" and "Daily Revenue" where filtering/aggregation
//     often requires scanning the collection anyway.
//
#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <vector>
#include <string>
#include "ParkingRecord.h"

class HistoryManager
{
private:
    std::vector<ParkingRecord> history;

public:
    void addRecord(const ParkingRecord& record);
    void printPlateHistory(const std::string& plate) const;
    void printAllHistory() const;
    void printDailyRevenue(const std::string& dateStr) const;
    int count() const
    {
        return static_cast<int>(history.size());
    }

    // ---- Persistence --------------------------------------------------------------------------------------------------------------------─
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif // HISTORYMANAGER_H
