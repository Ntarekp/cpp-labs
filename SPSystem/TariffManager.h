
// TariffManager.h
// Manages current parking tariffs per vehicle type.
// Provides fee calculation using ceiling-rounded hours.
// Price updates only affect future exits, never historical records.
//
// DSA Choice:
//   - std::map<VehicleType, double> → Efficient lookup of rates by type.
//     Since the number of vehicle types is small, this is highly performant.
//
#ifndef TARIFFMANAGER_H
#define TARIFFMANAGER_H

#include <map>
#include <ctime>
#include <cmath>
#include "types.h"

class TariffManager {
private:
    // Maps each vehicle type to its current hourly rate in RWF
    std::map<VehicleType, double> rates;

public:
    // ── Constructor: sets default tariffs per specification ───────────────────
    TariffManager() {
        rates[VehicleType::MOTORCYCLE] = 500.0;   // 500 RWF / hour
        rates[VehicleType::CAR]        = 1000.0;  // 1000 RWF / hour
        rates[VehicleType::TRUCK]      = 2000.0;  // 2000 RWF / hour (reasonable default)
    }

    // ── Get current rate for a vehicle type ───────────────────────────────────
    double getRate(VehicleType vt) const {
        auto it = rates.find(vt);
        return (it != rates.end()) ? it->second : 0.0;
    }

    // ── Update rate (only affects future calculations) ────────────────────────
    void setRate(VehicleType vt, double newRate) {
        rates[vt] = newRate;
    }

    // ── Calculate duration in ceiling-rounded hours ───────────────────────────
    // Spec: partial hours are always rounded UP (15 min → 1 hr, 1h20m → 2 hr)
    static int calculateHours(std::time_t entryTime, std::time_t exitTime) {
        double seconds  = std::difftime(exitTime, entryTime);
        double hours    = seconds / 3600.0;
        return static_cast<int>(std::ceil(hours));
    }

    // ── Calculate fee using current active rates ──────────────────────────────
    double calculateFee(VehicleType vt, std::time_t entryTime, std::time_t exitTime) const {
        int hours = calculateHours(entryTime, exitTime);
        return hours * getRate(vt);
    }

    // ── Display all current rates ─────────────────────────────────────────────
    void printRates() const;

    // ── Persistence ───────────────────────────────────────────────────────────
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif // TARIFFMANAGER_H
