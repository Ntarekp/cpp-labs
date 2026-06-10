
// ============================================================
// ParkingRecord.h
// Declares ParkingRecord: an immutable completed transaction
// stored in history after a vehicle exits.
// ============================================================

#ifndef PARKINGRECORD_H
#define PARKINGRECORD_H

#include <string>
#include <ctime>
#include "VehicleType.h"

// ---------------------------------------------------------------
// ParkingRecord: Snapshot of a completed parking session.
// Stores entry/exit times, duration, fee, and the rates that
// were active at the time of exit. This ensures price updates
// do NOT retroactively change historical records.
// DSA note: these are stored in a std::vector for O(1) append
// and O(n) traversal during report generation.
// ---------------------------------------------------------------
class ParkingRecord {
private:
    std::string plate;          // Vehicle plate
    VehicleType type;           // Vehicle type
    std::string slotID;         // Slot that was used
    std::time_t entryTime;      // Entry timestamp
    std::time_t exitTime;       // Exit timestamp
    int         durationHours;  // Billed hours (partial → round up)
    double      rateUsed;       // Rate per hour at time of exit (RWF)
    double      totalFee;       // Total fee charged (RWF)

public:
    // Constructor: all fields supplied by ParkingManager at exit
    ParkingRecord(const std::string& plate,
                  VehicleType type,
                  const std::string& slotID,
                  std::time_t entryTime,
                  std::time_t exitTime,
                  int durationHours,
                  double rateUsed,
                  double totalFee);

    // --- Getters ---
    std::string getPlate()         const;
    VehicleType getType()          const;
    std::string getSlotID()        const;
    std::time_t getEntryTime()     const;
    std::time_t getExitTime()      const;
    int         getDurationHours() const;
    double      getRateUsed()      const;
    double      getTotalFee()      const;

    // Format timestamps as readable strings
    std::string getEntryTimeStr()  const;
    std::string getExitTimeStr()   const;

    // Display one record row to console
    void display() const;
};

#endif // PARKINGRECORD_H
