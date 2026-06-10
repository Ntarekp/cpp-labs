# Kigali Smart Parking Management System

## Overview
The Kigali Smart Parking Management System is a console-based C++ application designed to manage public parking areas in Kigali. It handles parking slot allocation, vehicle entry and exit registration, fee calculation, and operational reporting.

## Features
- **Slot Configuration**: Add and manage parking slots for different vehicle types (Car, Motorcycle, Truck).
- **Vehicle Entry**: Register vehicle entry and automatically allocate available slots.
- **Vehicle Exit**: Process vehicle exit, calculate fees based on duration, and release slots.
- **Tariff Management**: View and update parking rates per vehicle type.
- **Reporting**:
  - View currently parked vehicles.
  - View parking history for a specific plate.
  - View full parking history.
  - Generate daily revenue reports.

## Default Parking Rates
- **Motorcycle**: 500 RWF per hour
- **Car**: 1,000 RWF per hour
- **Truck**: 2,000 RWF per hour

*Note: Partial hours are charged as full hours (e.g., 1 hour 15 minutes is billed as 2 hours).*

## How to Compile and Run
### Requirements
- A C++ compiler supporting C++17 (e.g., GCC/MinGW).
- Code::Blocks or any standard terminal.

### Compiling via Command Line
Run the following command in the project root:
```bash
g++ -std=c++17 -o parking.exe HistoryManager.cpp ParkingRecord.cpp ParkingSlot.cpp ParkingSystem.cpp SlotManager.cpp TariffManager.cpp Vehicle.cpp VehicleManager.cpp main.cpp
```

### Running
Execute the compiled binary:
```bash
./parking.exe
```

## How to Use
1. **Main Menu**: Upon launching, you will see a categorized menu.
2. **Operations**:
   - Use options **1-3** to manage parking slots.
   - Use options **4-5** for vehicle entry and exit.
   - Use options **6-7** to check or update pricing.
   - Use options **8-11** to view various reports.
   - Use option **12** to manually save the current system state.
3. **Data Persistence**: Data is automatically loaded on startup and saved on exit to `.txt` files (e.g., `slots.txt`, `history.txt`). This allows you to verify that data is stored for future reference.
