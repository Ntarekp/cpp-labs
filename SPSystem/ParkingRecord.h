
// ParkingRecord.h
// Immutable record of a completed parking transaction.
// Stored in history after a vehicle exits. Price updates do NOT affect these.

#ifndef PARKINGRECORD_H
#define PARKINGRECORD_H

#include <string>
#include <ctime>
#include "types.h"

class ParkingRecord
{
private:
    std::string plate;
    VehicleType vehicleType;
    std::string slotId;
    std::string zone;
    std::time_t entryTime;
    std::time_t exitTime;
    int         durationHours;  // Ceiling-rounded hours
    double      feeCharged;     // Fee at time of exit (frozen)

public:
    // ---- Constructor --------------------------------------------------------------------------------------------------------------------─
    ParkingRecord(const std::string& plate,
                  VehicleType        vtype,
                  const std::string& slotId,
                  const std::string& zone,
                  std::time_t        entry,
                  std::time_t        exit,
                  int                hours,
                  double             fee)
        : plate(plate), vehicleType(vtype), slotId(slotId), zone(zone),
          entryTime(entry), exitTime(exit),
          durationHours(hours), feeCharged(fee)
    {}

    // ---- Getters ----------------------------------------------------------------------------------------------------------------------------─
    const std::string& getPlate()        const
    {
        return plate;
    }
    VehicleType        getVehicleType()  const
    {
        return vehicleType;
    }
    const std::string& getSlotId()       const
    {
        return slotId;
    }
    const std::string& getZone()         const
    {
        return zone;
    }
    std::time_t        getEntryTime()    const
    {
        return entryTime;
    }
    std::time_t        getExitTime()     const
    {
        return exitTime;
    }
    int                getDurationHours()const
    {
        return durationHours;
    }
    double             getFeeCharged()   const
    {
        return feeCharged;
    }

    // ---- Display helper ----------------------------------------------------------------------------------------------------------------
    void print() const;
};

#endif // PARKINGRECORD_H
