
// ============================================================
// VehicleType.h
// Defines the VehicleType enum used across all system modules.
// Using an enum ensures type safety and prevents invalid types.
// ============================================================

#ifndef VEHICLETYPE_H
#define VEHICLETYPE_H

#include <string>

// Enum class for vehicle types (scoped enum to avoid naming conflicts)
enum class VehicleType {
    MOTORCYCLE,
    CAR,
    TRUCK
};

// Utility: Convert VehicleType enum to human-readable string
inline std::string vehicleTypeToString(VehicleType type) {
    switch (type) {
        case VehicleType::MOTORCYCLE: return "Motorcycle";
        case VehicleType::CAR:        return "Car";
        case VehicleType::TRUCK:      return "Truck";
        default:                      return "Unknown";
    }
}

// Utility: Convert string (case-insensitive) to VehicleType enum
// Returns true if conversion succeeded, false otherwise
inline bool stringToVehicleType(const std::string& str, VehicleType& out) {
    if (str == "motorcycle" || str == "Motorcycle" || str == "MOTORCYCLE") {
        out = VehicleType::MOTORCYCLE; return true;
    }
    if (str == "car" || str == "Car" || str == "CAR") {
        out = VehicleType::CAR; return true;
    }
    if (str == "truck" || str == "Truck" || str == "TRUCK") {
        out = VehicleType::TRUCK; return true;
    }
    return false; // invalid input
}

#endif // VEHICLETYPE_H
