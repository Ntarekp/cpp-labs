# Data Structure Justification Report

This document outlines the data structures chosen for the Kigali Smart Parking Management System and justifies their selection based on operational requirements.

## 1. SlotManager
**Primary Responsibility:** Inventory and allocation of parking slots.

| Data Structure | Type | Purpose |
| :--- | :--- | :--- |
| `std::unordered_map<string, ParkingSlot>` | Non-linear (Hash Table) | Primary store for slots, allowing $O(1)$ average lookup and update by Slot ID. |
| `std::map<VehicleType, std::vector<string>>` | Non-linear (Balanced Tree + Dynamic Array) | Secondary index to group slot IDs by the vehicle type they support. |

**Justification:**
- **Search:** Entry registration requires finding a slot compatible with the vehicle type. Without the index, this would be an $O(N)$ scan. With the `std::map` index, we immediately access the list of relevant slots, keeping allocation efficient even as total slots increase.
- **Uniqueness:** The hash map naturally enforces unique Slot IDs while providing the fastest possible access for slot status updates (occupy/release).

## 2. VehicleManager
**Primary Responsibility:** Tracking active parking sessions.

| Data Structure | Type | Purpose |
| :--- | :--- | :--- |
| `std::unordered_map<string, Vehicle>` | Non-linear (Hash Table) | Stores active vehicles using the plate number as the key. |

**Justification:**
- **Insert/Delete:** Frequent operations at the entrance and exit. $O(1)$ average complexity ensures no queues build up due to software processing time.
- **Lookup:** Required during entry to prevent duplicate parking of the same plate, and during exit to retrieve entry time. Hash tables are optimal for this key-based retrieval.

## 3. TariffManager
**Primary Responsibility:** Managing hourly rates and fee logic.

| Data Structure | Type | Purpose |
| :--- | :--- | :--- |
| `std::map<VehicleType, double>` | Non-linear (Balanced Tree) | Maps vehicle categories to their current hourly rates. |

**Justification:**
- **Size:** Since the number of vehicle types (Motorcycle, Car, Truck) is very small and static, the performance difference between a map and a hash map is negligible. A `std::map` provides ordered traversal if needed for reporting.

## 4. HistoryManager
**Primary Responsibility:** Archival of completed transactions for reporting and auditing.

| Data Structure | Type | Purpose |
| :--- | :--- | :--- |
| `std::vector<ParkingRecord>` | Linear (Dynamic Array) | Sequential storage of all past parking sessions. |

**Justification:**
- **Insertion:** $O(1)$ amortized append time. Records are added only when a vehicle exits.
- **Traversal:** Daily revenue reports and full history views require scanning the collection. A vector provides the best cache locality for full scans.
- **Trade-off:** Search by plate in history is currently $O(N)$. For a production system with millions of records, an additional hash-based index would be added, but for the current scope, the simplicity of a vector is preferred.

## 5. Summary of Design Principles
- **Efficiency:** O(1) or O(log N) operations were prioritized for real-time operations (entry/exit).
- **Encapsulation:** Data structures are hidden inside manager classes, exposing only high-level business methods (e.g., `parkVehicle`).
- **Memory Management:** In-memory STL containers were used to satisfy the "no database" requirement while ensuring scalability.
