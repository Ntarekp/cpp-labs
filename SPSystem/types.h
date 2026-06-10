// types.h
// Shared enumerations and constants used across the entire system.

#ifndef TYPES_H
#define TYPES_H

#include <string>

// ----------------------------------------------------------------------------------------─
// Vehicle type enumeration
// ----------------------------------------------------------------------------------------─
enum class VehicleType
{
    MOTORCYCLE,
    CAR,
    TRUCK
};

// ----------------------------------------------------------------------------------------─
// Slot status enumeration
// ----------------------------------------------------------------------------------------─
enum class SlotStatus
{
    AVAILABLE,
    OCCUPIED
};

// ----------------------------------------------------------------------------------------─
// Helper: convert VehicleType enum → string
// ----------------------------------------------------------------------------------------─
inline std::string vehicleTypeToString(VehicleType vt)
{
    switch (vt)
    {
    case VehicleType::MOTORCYCLE:
        return "Motorcycle";
    case VehicleType::CAR:
        return "Car";
    case VehicleType::TRUCK:
        return "Truck";
    default:
        return "Unknown";
    }
}

// ----------------------------------------------------------------------------------------─
// Helper: convert string → VehicleType enum
// Returns true on success, false on bad input
// ----------------------------------------------------------------------------------------─
inline bool stringToVehicleType(const std::string& s, VehicleType& out)
{
    if (s == "1" || s == "Motorcycle" || s == "motorcycle")
    {
        out = VehicleType::MOTORCYCLE;
        return true;
    }
    if (s == "2" || s == "Car" || s == "car")
    {
        out = VehicleType::CAR;
        return true;
    }
    if (s == "3" || s == "Truck" || s == "truck")
    {
        out = VehicleType::TRUCK;
        return true;
    }
    return false;
}

// ----------------------------------------------------------------------------------------─
// Helper: convert SlotStatus enum → string
// ----------------------------------------------------------------------------------------─
inline std::string slotStatusToString(SlotStatus ss)
{
    return (ss == SlotStatus::AVAILABLE) ? "Available" : "Occupied";
}

#endif // TYPES_H
