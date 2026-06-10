# Kigali Smart Parking - Architecture Diagrams

## 1. Core Components and Relationships (Class Diagram)
This diagram illustrates the object-oriented structure and the relationships between the facade, the managers, and the data entities.

```mermaid
classDiagram
    class ParkingSystem {
        -SlotManager slotMgr
        -VehicleManager vehicleMgr
        -HistoryManager historyMgr
        -TariffManager tariffMgr
        +registerEntry()
        +registerExit()
        +configureSlot()
        +reportDailyRevenue()
    }

    class SlotManager {
        -unordered_map slots
        -map slotIndex
        +findAvailableSlot(VehicleType)
        +addSlot()
    }

    class VehicleManager {
        -unordered_map activeVehicles
        +parkVehicle()
        +removeVehicle()
    }

    class HistoryManager {
        -vector history
        +addRecord(ParkingRecord)
        +printPlateHistory(string)
    }

    class TariffManager {
        -map rates
        +calculateFee(VehicleType, time, time)
    }

    class ParkingSlot {
        -string slotId
        -VehicleType type
        -SlotStatus status
    }

    class Vehicle {
        -string plate
        -time_t entryTime
        -string slotId
    }

    class ParkingRecord {
        -string plate
        -double feeCharged
        -time_t exitTime
    }

    ParkingSystem *-- SlotManager
    ParkingSystem *-- VehicleManager
    ParkingSystem *-- HistoryManager
    ParkingSystem *-- TariffManager

    SlotManager "1" *-- "many" ParkingSlot
    VehicleManager "1" *-- "many" Vehicle
    HistoryManager "1" *-- "many" ParkingRecord
```

## 2. Vehicle Entry Data Flow
The sequence of interactions when a vehicle arrives at the parking facility.

```mermaid
sequenceDiagram
    participant U as User/Attendant
    participant PS as ParkingSystem
    participant SM as SlotManager
    participant VM as VehicleManager

    U->>PS: Register Entry (Plate, Type)
    PS->>VM: isParked(Plate)?
    VM-->>PS: No
    PS->>SM: findAvailableSlot(Type)
    SM-->>PS: ParkingSlot* (A1)
    PS->>SM: slot->occupy()
    PS->>VM: parkVehicle(Plate, Type, Time, A1)
    PS-->>U: Success (Slot A1 assigned)
```

## 3. Vehicle Exit and Payment Data Flow
The sequence of interactions when a vehicle leaves and the fee is processed.

```mermaid
sequenceDiagram
    participant U as User/Attendant
    participant PS as ParkingSystem
    participant VM as VehicleManager
    participant TM as TariffManager
    participant SM as SlotManager
    participant HM as HistoryManager

    U->>PS: Register Exit (Plate)
    PS->>VM: getVehicle(Plate)
    VM-->>PS: Vehicle Data (EntryTime, SlotId)
    PS->>TM: calculateFee(Type, Entry, Exit)
    TM-->>PS: Fee (e.g. 2000 RWF)
    PS->>SM: getSlot(SlotId)
    PS->>SM: slot->release()
    PS->>VM: removeVehicle(Plate)
    PS->>HM: addRecord(ParkingRecord)
    PS-->>U: Display Receipt & Fee
```
