// ParkingSystem.cpp
// FIX: Added #include <iomanip> to resolve std::setw / std::setprecision errors.

#include "ParkingSystem.h"
#include "ParkingRecord.h"    // ← explicit include so ParkingRecord is visible here
#include <iostream>
#include <iomanip>            // ← was MISSING: needed for std::setw, std::setprecision, std::fixed
#include <string>
#include <limits>
#include <ctime>
#include <algorithm>          // std::transform
#include <fstream>
#include <cctype>             // std::toupper

// ---- Utility: read a clean trimmed line --------------------------------------------------------------------------------
static std::string readLine(const std::string& prompt)
{
    std::cout << "  " << prompt;
    std::string line;
    std::getline(std::cin >> std::ws, line);
    return line;
}

// ---- Utility: convert string to uppercase ----------------------------------------------------------------------------
static std::string toUpper(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}

// ---- Constructor ----------------------------------------------------------------------------------------------------------------------------─
ParkingSystem::ParkingSystem()
{
    seedDefaultSlots();
}

// ---- Seed default slots ----------------------------------------------------------------------------------------------------------------
void ParkingSystem::seedDefaultSlots()
{
    // Zone A — Cars
    slotMgr.addSlot("A1", VehicleType::CAR,        "Zone-A");
    slotMgr.addSlot("A2", VehicleType::CAR,        "Zone-A");
    slotMgr.addSlot("A3", VehicleType::CAR,        "Zone-A");
    slotMgr.addSlot("A4", VehicleType::CAR,        "Zone-A");

    // Zone B — Motorcycles
    slotMgr.addSlot("B1", VehicleType::MOTORCYCLE, "Zone-B");
    slotMgr.addSlot("B2", VehicleType::MOTORCYCLE, "Zone-B");
    slotMgr.addSlot("B3", VehicleType::MOTORCYCLE, "Zone-B");

    // Zone C — Trucks
    slotMgr.addSlot("C1", VehicleType::TRUCK,      "Zone-C");
    slotMgr.addSlot("C2", VehicleType::TRUCK,      "Zone-C");
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------─
// TASK 1 – SLOT CONFIGURATION
// --------------------------------------------------------------------------------------------------------------------------------------------------------─

void ParkingSystem::configureSlot()
{
    std::cout << "\n  ---- Add New Parking Slot ----\n";

    std::string slotId = toUpper(readLine("Enter Slot ID (e.g. D5): "));
    if (slotId.empty())
    {
        std::cout << "  [!] Slot ID cannot be empty.\n";
        return;
    }
    if (slotMgr.slotExists(slotId))
    {
        std::cout << "  [!] Slot ID '" << slotId << "' already exists.\n";
        return;
    }

    std::cout << "  Vehicle type: 1=Motorcycle  2=Car  3=Truck\n";
    std::string typeInput = readLine("Choose (1/2/3): ");
    VehicleType vtype;
    if (!stringToVehicleType(typeInput, vtype))
    {
        std::cout << "  [!] Invalid vehicle type.\n";
        return;
    }

    std::string zone = readLine("Enter Zone label (e.g. Zone-D): ");
    if (zone.empty()) zone = "Zone-X";

    if (slotMgr.addSlot(slotId, vtype, zone))
    {
        std::cout << "  [✓] Slot '" << slotId << "' added successfully.\n";
    }
    else
    {
        std::cout << "  [!] Failed to add slot.\n";
    }
}

void ParkingSystem::viewAllSlots() const
{
    std::cout << "\n  ---- All Configured Slots ----\n";
    slotMgr.printAllSlots();
    std::cout << "  Total: " << slotMgr.totalSlots() << " slot(s)\n";
}

void ParkingSystem::viewAvailableSlots() const
{
    std::cout << "\n  ---- Available Slots ----\n";
    slotMgr.printAvailableSlots();
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------─
// TASK 2 – VEHICLE ENTRY
// --------------------------------------------------------------------------------------------------------------------------------------------------------─

void ParkingSystem::registerEntry()
{
    std::cout << "\n  ---- Vehicle Entry Registration ----\n";

    std::string plate = toUpper(readLine("Enter vehicle plate number: "));
    if (plate.empty())
    {
        std::cout << "  [!] Plate cannot be empty.\n";
        return;
    }

    // A vehicle cannot be parked more than once at the same time
    if (vehicleMgr.isParked(plate))
    {
        std::cout << "  [!] Vehicle '" << plate
                  << "' is already parked in the system.\n";
        return;
    }

    std::cout << "  Vehicle type: 1=Motorcycle  2=Car  3=Truck\n";
    std::string typeInput = readLine("Choose (1/2/3): ");
    VehicleType vtype;
    if (!stringToVehicleType(typeInput, vtype))
    {
        std::cout << "  [!] Invalid vehicle type.\n";
        return;
    }

    // Graceful handling when no suitable slot is available
    ParkingSlot* slot = slotMgr.findAvailableSlot(vtype);
    if (!slot)
    {
        std::cout << "  [!] No available "
                  << vehicleTypeToString(vtype)
                  << " slots at this time. Please try again later.\n";
        return;
    }

    std::time_t now = std::time(nullptr);
    slot->occupy();
    vehicleMgr.parkVehicle(plate, vtype, now, slot->getSlotId());

    char buf[32];
    std::tm* tm_info = std::localtime(&now);
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm_info);

    std::cout << "\n  [✓] Entry Registered\n"
              << "      Plate   : " << plate << "\n"
              << "      Type    : " << vehicleTypeToString(vtype) << "\n"
              << "      Slot    : " << slot->getSlotId()
              << "  (" << slot->getZone() << ")\n"
              << "      Time    : " << buf << "\n";
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------─
// TASK 3 – TARIFF MANAGEMENT
// --------------------------------------------------------------------------------------------------------------------------------------------------------─

void ParkingSystem::viewTariffs() const
{
    tariffMgr.printRates();
}

void ParkingSystem::updateTariff()
{
    std::cout << "\n  ---- Update Parking Rate ----\n";
    tariffMgr.printRates();

    std::cout << "  Vehicle type: 1=Motorcycle  2=Car  3=Truck\n";
    std::string typeInput = readLine("Choose (1/2/3): ");
    VehicleType vtype;
    if (!stringToVehicleType(typeInput, vtype))
    {
        std::cout << "  [!] Invalid vehicle type.\n";
        return;
    }

    std::string rateStr = readLine("Enter new hourly rate (RWF): ");
    double newRate = 0.0;
    try
    {
        newRate = std::stod(rateStr);
    }
    catch (...)
    {
        std::cout << "  [!] Invalid rate value.\n";
        return;
    }
    if (newRate <= 0)
    {
        std::cout << "  [!] Rate must be positive.\n";
        return;
    }

    tariffMgr.setRate(vtype, newRate);

    // std::setprecision now resolves because <iomanip> is included
    std::cout << "  [✓] Rate for " << vehicleTypeToString(vtype)
              << " updated to "
              << std::fixed << std::setprecision(0) << newRate
              << " RWF/hr\n";
    std::cout << "  [i] Previously completed transactions are unaffected.\n";
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------─
// TASK 4 – VEHICLE EXIT
// --------------------------------------------------------------------------------------------------------------------------------------------------------─

void ParkingSystem::registerExit()
{
    std::cout << "\n  ---- Vehicle Exit Processing ----\n";

    std::string plate = toUpper(readLine("Enter vehicle plate number: "));
    if (plate.empty())
    {
        std::cout << "  [!] Plate cannot be empty.\n";
        return;
    }

    const Vehicle* vehicle = vehicleMgr.getVehicle(plate);
    if (!vehicle)
    {
        std::cout << "  [!] Vehicle '" << plate
                  << "' is not currently parked.\n";
        return;
    }

    ParkingSlot* slot      = slotMgr.getSlot(vehicle->getSlotId());
    std::time_t  exitTime  = std::time(nullptr);
    std::time_t  entryTime = vehicle->getEntryTime();
    VehicleType  vtype     = vehicle->getVehicleType();
    std::string  slotId    = vehicle->getSlotId();
    std::string  zone      = slot ? slot->getZone() : "Unknown";

    int    hours = TariffManager::calculateHours(entryTime, exitTime);
    double fee   = tariffMgr.calculateFee(vtype, entryTime, exitTime);

    char entryBuf[32], exitBuf[32];
    std::tm* t1 = std::localtime(&entryTime);
    std::strftime(entryBuf, sizeof(entryBuf), "%Y-%m-%d %H:%M:%S", t1);
    std::tm* t2 = std::localtime(&exitTime);
    std::strftime(exitBuf, sizeof(exitBuf), "%Y-%m-%d %H:%M:%S", t2);

    // Receipt - using standard ASCII for compatibility
    std::cout << "\n  +-----------------------------------------+\n";
    std::cout << "  |           PARKING RECEIPT               |\n";
    std::cout << "  +-----------------------------------------+\n";
    std::cout << "  |  Plate      : " << std::left << std::setw(27) << plate                            << "|\n";
    std::cout << "  |  Type       : " << std::left << std::setw(27) << vehicleTypeToString(vtype)       << "|\n";
    std::cout << "  |  Slot       : " << std::left << std::setw(27) << slotId                           << "|\n";
    std::cout << "  |  Zone       : " << std::left << std::setw(27) << zone                             << "|\n";
    std::cout << "  |  Entry      : " << std::left << std::setw(27) << entryBuf                         << "|\n";
    std::cout << "  |  Exit       : " << std::left << std::setw(27) << exitBuf                          << "|\n";
    std::cout << "  |  Duration   : " << std::left << std::setw(23) << hours << " hour(s)"              << "|\n";
    std::cout << "  |  Rate       : " << std::left << std::setw(17)
              << tariffMgr.getRate(vtype) << " RWF/hr          |\n";
    std::cout << "  |  Total Fee  : " << std::left << std::setw(23)
              << (std::to_string((int)fee) + " RWF")                                                    << "|\n";
    std::cout << "  +-----------------------------------------+\n";

    // 1. Release slot
    if (slot) slot->release();

    // 2. Remove from active vehicle map
    vehicleMgr.removeVehicle(plate);

    // 3. Store immutable record — fee is frozen at this moment
    //    ParkingRecord now resolves because ParkingRecord.h is included via HistoryManager.h
    historyMgr.addRecord(
        ParkingRecord(plate, vtype, slotId, zone,
                      entryTime, exitTime, hours, fee)
    );

    std::cout << "  [✓] Slot " << slotId << " is now available.\n";
    std::cout << "  [✓] Transaction recorded in history.\n";
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------─
// TASK 5 – REPORTS
// --------------------------------------------------------------------------------------------------------------------------------------------------------─

void ParkingSystem::reportParkedVehicles() const
{
    std::cout << "\n  ---- Currently Parked Vehicles ----\n";
    vehicleMgr.printParkedVehicles();
    std::cout << "  Active sessions: " << vehicleMgr.count() << "\n";
}

void ParkingSystem::reportVehicleHistory() const
{
    std::cout << "\n  ---- Vehicle Parking History Lookup ----\n";
    std::string plate = toUpper(readLine("Enter plate number: "));
    historyMgr.printPlateHistory(plate);    // historyMgr now resolves
}

void ParkingSystem::reportFullHistory() const
{
    std::cout << "\n  ---- Full Parking History ----\n";
    historyMgr.printAllHistory();           // historyMgr now resolves
    std::cout << "  Total records: " << historyMgr.count() << "\n";
}

void ParkingSystem::reportDailyRevenue() const
{
    std::cout << "\n  ---- Daily Revenue Report ----\n";

    std::time_t now = std::time(nullptr);
    char buf[16];
    std::tm* tm_info = std::localtime(&now);
    std::strftime(buf, sizeof(buf), "%Y-%m-%d", tm_info);

    std::cout << "  Press ENTER for today (" << buf
              << ") or type a date (YYYY-MM-DD): ";
    std::string input;
    
    // Fix: Using std::getline(std::cin, input) instead of cin >> ws to avoid endless loops/beeps
    // if the previous input left whitespace or if the stream is in a weird state.
    if (std::cin.peek() == '\n') std::cin.ignore();
    std::getline(std::cin, input);
    
    if (input.empty()) input = std::string(buf);

    historyMgr.printDailyRevenue(input);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------─
// TASK 6 – PERSISTENCE
// --------------------------------------------------------------------------------------------------------------------------------------------------------─

void ParkingSystem::saveAllData()
{
    std::cout << "\n  [i] Saving system data...\n";
    tariffMgr.saveToFile("tariffs.txt");
    slotMgr.saveToFile("slots.txt");
    vehicleMgr.saveToFile("active_vehicles.txt");
    historyMgr.saveToFile("history.txt");
    std::cout << "  [✓] All data saved successfully.\n";
}

void ParkingSystem::loadAllData()
{
    // Check if files exist before trying to load
    // If slots.txt doesn't exist, we keep default seeds
    std::ifstream f("slots.txt");
    if (f.good())
    {
        std::cout << "\n  [i] Loading existing data...\n";
        tariffMgr.loadFromFile("tariffs.txt");
        slotMgr.loadFromFile("slots.txt");
        vehicleMgr.loadFromFile("active_vehicles.txt");
        historyMgr.loadFromFile("history.txt");
        std::cout << "  [✓] Data loaded successfully.\n";
    }
    else
    {
        std::cout << "\n  [i] No saved data found. Using system defaults.\n";
    }
}
