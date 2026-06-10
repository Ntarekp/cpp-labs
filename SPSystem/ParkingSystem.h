// ParkingSystem.h
// Top-level facade that coordinates all subsystem managers.
// FIX: Added missing #include directives for HistoryManager and ParkingRecord.

#ifndef PARKINGSYSTEM_H
#define PARKINGSYSTEM_H

#include "SlotManager.h"      // SlotManager + ParkingSlot
#include "VehicleManager.h"   // VehicleManager + Vehicle
#include "HistoryManager.h"   // HistoryManager + ParkingRecord  ← was MISSING
#include "TariffManager.h"    // TariffManager

class ParkingSystem
{
private:
    SlotManager    slotMgr;
    VehicleManager vehicleMgr;
    HistoryManager historyMgr;   // ← now resolves because HistoryManager.h is included
    TariffManager  tariffMgr;

    void seedDefaultSlots();

public:
    ParkingSystem();

    // Task 1 – Slot Configuration
    void configureSlot();
    void viewAllSlots()       const;
    void viewAvailableSlots() const;

    // Task 2 – Vehicle Entry
    void registerEntry();

    // Task 3 – Tariff Management
    void viewTariffs()  const;
    void updateTariff();

    // Task 4 – Vehicle Exit
    void registerExit();

    // Task 5 – Reports
    void reportParkedVehicles() const;
    void reportVehicleHistory() const;
    void reportFullHistory()    const;
    void reportDailyRevenue()   const;

    // Task 6 – Persistence
    void saveAllData();
    void loadAllData();
};

#endif // PARKINGSYSTEM_H
