// main.cpp
// Entry point for the Kigali Smart Parking Management System.
// Provides a menu-driven console interface for all operations.
//
// Compile:  g++ -std=c++17 -o parking main.cpp ParkingSlot.cpp Vehicle.cpp
//                ParkingRecord.cpp TariffManager.cpp SlotManager.cpp
//                VehicleManager.cpp HistoryManager.cpp ParkingSystem.cpp
// Run:      ./parking          (Linux/macOS)
//           parking.exe        (Windows)

#include <iostream>
#include <string>
#include <limits>
#include "ParkingSystem.h"

// ── Draw the main menu ────────────────────────────────────────────────────────
static void printMenu() {
    std::cout << R"(
  +------------------------------------------------+
  |    KIGALI SMART PARKING MANAGEMENT SYSTEM      |
  +------------------------------------------------+
  |  SLOT CONFIGURATION                            |
  |   1. Add new parking slot                      |
  |   2. View all slots                            |
  |   3. View available slots                      |
  +------------------------------------------------+
  |  VEHICLE OPERATIONS                            |
  |   4. Register vehicle entry                    |
  |   5. Register vehicle exit & pay               |
  +------------------------------------------------+
  |  TARIFF MANAGEMENT                             |
  |   6. View current parking rates                |
  |   7. Update a parking rate                     |
  +------------------------------------------------+
  |  REPORTS                                       |
  |   8. Currently parked vehicles                 |
  |   9. Vehicle parking history (by plate)        |
  |  10. Full parking history                      |
  |  11. Daily revenue report                      |
  +------------------------------------------------+
  |  DATA MANAGEMENT                               |
  |  12. Save system data                          |
  +------------------------------------------------+
  |   0. Exit                                      |
  +------------------------------------------------+
  Choice: )";
}

int main() {
    ParkingSystem system;   // Initialises with 9 default slots
    system.loadAllData();   // Attempt to load previously saved data

    std::cout << "\n  Welcome to Kigali Smart Parking Management System\n";
    std::cout << "  System loaded with 9 default slots (4 Car, 3 Motorcycle, 2 Truck)\n";

    int choice = -1;
    while (true) {
        printMenu();

        // Robust integer read — rejects non-numeric input
        std::string input;
        std::getline(std::cin >> std::ws, input);
        try {
            choice = std::stoi(input);
        } catch (...) {
            choice = -1;
        }

        std::cout << "\n";

        switch (choice) {
            // ── Slot configuration ─────────────────────────────────────────
            case 1:  system.configureSlot();       break;
            case 2:  system.viewAllSlots();        break;
            case 3:  system.viewAvailableSlots();  break;

            // ── Vehicle operations ─────────────────────────────────────────
            case 4:  system.registerEntry();       break;
            case 5:  system.registerExit();        break;

            // ── Tariff management ──────────────────────────────────────────
            case 6:  system.viewTariffs();         break;
            case 7:  system.updateTariff();        break;

            // ── Reports ────────────────────────────────────────────────────
            case 8:  system.reportParkedVehicles(); break;
            case 9:  system.reportVehicleHistory(); break;
            case 10: system.reportFullHistory();    break;
            case 11: system.reportDailyRevenue();   break;

            // ── Data Management ────────────────────────────────────────────
            case 12: system.saveAllData();          break;

            // ── Exit ───────────────────────────────────────────────────────
            case 0:
                system.saveAllData(); // Auto-save on exit
                std::cout << "  Goodbye. Thank you for using Kigali Smart Parking.\n\n";
                return 0;

            default:
                std::cout << "  [!] Invalid option. Please choose 0–12.\n";
        }

        // Pause before redrawing menu
        std::cout << "\n  Press ENTER to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return 0;
}
