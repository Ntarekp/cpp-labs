/*
 * ═
 *  KIGALI SMART PARKING MANAGEMENT SYSTEM
 *  Language  : C++17
 *  Compile   : g++ -std=c++17 -o parking main.cpp
 *  Run       : ./parking
 * ═
 *
 *  SYSTEM ARCHITECTURE — 3 LAYERS
 *  ───────────────────────────────
 *  1. Presentation Layer : ConsoleUI class (all I/O, menus, prompts)
 *  2. Business Logic     : ParkingManager (coordinator/facade)
 *                          TariffManager  (pricing engine)
 *  3. Data Layer         : in-memory data structures (see below)
 *
 *  CORE COMPONENTS
 *  ───────────────
 *  ParkingSlot     — entity representing one physical parking space
 *  VehicleBase     — abstract base for vehicle type hierarchy
 *  Motorcycle/Car/Truck — concrete vehicle subclasses
 *  ActiveVehicle   — record of a currently-parked vehicle
 *  ParkingRecord   — immutable transaction snapshot (exit receipt)
 *  TariffManager   — manages hourly rates, calculates fees
 *  WaitlistEntry   — holds vehicles waiting for a free slot
 *  ParkingManager  — central controller, owns all data structures
 *  ConsoleUI       — all user interaction, fully separated from logic
 *
 *  DATA STRUCTURES & JUSTIFICATION
 *  ─────────────────────────────────
 *  unordered_map<string, ParkingSlot>         (slotMap)
 *    → Hash table: O(1) avg insert/lookup/delete by Slot ID
 *    → Best for "find slot by ID" at entry and exit
 *
 *  map<string, vector<string>>                (zoneSlotIndex)
 *    → BST (non-linear): O(log n) insert, ordered zone traversal
 *    → Ensures alphabetical zone order in availability reports
 *    → vector<string> inside = ordered list of slot IDs per zone
 *
 *  unordered_map<string, ActiveVehicle>       (activeVehicles)
 *    → Hash table: O(1) "is this plate already parked?" check
 *    → O(1) removal on vehicle exit
 *
 *  vector<ParkingRecord>                      (history)
 *    → Dynamic array (linear): O(1) amortised push_back
 *    → Sequential scan O(n) for reports — acceptable for history
 *    → Maintains insertion order (chronological)
 *
 *  map<VehicleType, queue<WaitlistEntry>>     (waitlistQueues)
 *    → queue (linear/FIFO): O(1) enqueue and dequeue
 *    → One queue per vehicle type — freed Car slot serves Car queue
 *    → map keyed by enum gives stable iteration
 *
 *  OOP PRINCIPLES APPLIED
 *  ───────────────────────
 *  Encapsulation  : All class data members are private; exposed only
 *                   through public getters/setters with validation
 *  Abstraction    : VehicleBase hides type details behind interface
 *                   ParkingManager hides all DSA from ConsoleUI
 *  Inheritance    : Motorcycle, Car, Truck extend VehicleBase
 *  Polymorphism   : virtual getTypeString() resolved at runtime
 *                   createVehicle() factory uses runtime dispatch
 *
 *  INPUT VALIDATION & ERROR HANDLING
 *  ────────────────────────────────────
 *  - Duplicate slot IDs rejected
 *  - Duplicate active plate rejected (same vehicle twice)
 *  - Empty strings rejected at all prompts
 *  - Non-numeric menu input cleared and re-prompted
 *  - Negative/zero tariff rejected
 *  - Exit of non-parked vehicle handled gracefully
 *  - No-slot-available → vehicle placed on typed waitlist
 * ═
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <queue>
#include <ctime>
#include <cmath>      // ceil()
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <limits>
#include <stdexcept>

using namespace std;

// ═
//  SECTION 1 — ENUMERATIONS & GLOBAL HELPERS
// ═

enum class VehicleType { MOTORCYCLE, CAR, TRUCK };
enum class SlotStatus  { AVAILABLE, OCCUPIED };

/*
 * vehicleTypeToStr()
 * Pure utility — converts enum to a human-readable label.
 * Used throughout all display methods.
 */
string vehicleTypeToStr(VehicleType vt)
{
    switch (vt)
    {
    case VehicleType::MOTORCYCLE:
        return "Motorcycle";
    case VehicleType::CAR:
        return "Car";
    case VehicleType::TRUCK:
        return "Truck";
    }
    return "Unknown";
}

/*
 * fmtTime()
 * Formats a time_t value into "YYYY-MM-DD HH:MM:SS".
 * Centralised here so ParkingRecord and ActiveVehicle share the same format.
 */
string fmtTime(time_t t)
{
    char buf[32];
    struct tm* tm_info = localtime(&t);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm_info);
    return string(buf);
}

// ═
//  SECTION 2 — TARIFF MANAGER  (Pricing Engine — Task 3)
//
//  Design decision: TariffManager is a standalone class, not embedded
//  in ParkingManager. This separates pricing concerns and makes it
//  easy to extend (e.g., peak-hour pricing) without touching the manager.
//
//  Price isolation guarantee:
//    setRate() only mutates the internal 'rates' map.
//    ParkingRecord stores its own snapshot of the rate used at exit,
//    so history is completely immune to future setRate() calls.
// ═

class TariffManager
{
private:
    // Non-linear data structure: unordered_map for O(1) rate lookup by type
    unordered_map<VehicleType, double> rates;

public:
    /*
     * Constructor sets default tariffs as specified in the brief:
     *   Motorcycle : 500  RWF/hr
     *   Car        : 1000 RWF/hr
     *   Truck      : 2000 RWF/hr  (reasonable default — not specified)
     */
    TariffManager()
    {
        rates[VehicleType::MOTORCYCLE] = 500.0;
        rates[VehicleType::CAR]        = 1000.0;
        rates[VehicleType::TRUCK]      = 2000.0;
    }

    // Getter — returns current rate; throws if unknown type
    double getRate(VehicleType vt) const
    {
        return rates.at(vt);   // throws std::out_of_range if missing
    }

    /*
     * setRate() — Task 3 requirement: controlled price update
     * Validates: rate must be strictly positive
     * Does NOT touch any historical ParkingRecord
     */
    void setRate(VehicleType vt, double newRate)
    {
        if (newRate <= 0)
            throw invalid_argument("Tariff must be a positive value.");
        rates[vt] = newRate;
    }

    /*
     * calculateFee() — Task 3: partial hours billed as full hours
     *
     * Algorithm:
     *   1. Compute raw seconds between entry and exit
     *   2. Convert to hours (floating point)
     *   3. Apply ceiling() → 15 min becomes 1 hr, 1h20m becomes 2 hr
     *   4. Minimum 1 hour always charged
     *   5. Multiply by current rate for this vehicle type
     *
     * Returns both fee and billedHours via output parameters so the
     * ParkingRecord can store them independently.
     */
    double calculateFee(VehicleType vt, time_t entryTime, time_t exitTime,
                        int& billedHoursOut) const
    {
        double seconds = difftime(exitTime, entryTime);
        if (seconds < 0) seconds = 0;

        double hours   = seconds / 3600.0;
        int    billed  = static_cast<int>(ceil(hours));
        if (billed < 1) billed = 1; // minimum 1 hour

        billedHoursOut = billed;
        return billed * rates.at(vt);
    }

    void displayRates() const
    {
        cout << "\n┌─────────────────────────────────┐\n";
        cout << "  │      Current Parking Tariffs    │\n";
        cout << "  ├─────────────────┬───────────────┤\n";
        cout << "  │ Vehicle Type    │ RWF / Hour    │\n";
        cout << "  ├─────────────────┼───────────────┤\n";
        cout << fixed << setprecision(2);
        cout << "  │ Motorcycle      │ "
             << setw(13) << left << rates.at(VehicleType::MOTORCYCLE) << "│\n";
        cout << "  │ Car             │ "
             << setw(13) << left << rates.at(VehicleType::CAR)        << "│\n";
        cout << "  │ Truck           │ "
             << setw(13) << left << rates.at(VehicleType::TRUCK)      << "│\n";
        cout << "  └─────────────────┴───────────────┘\n";
    }
};

// ═
//  SECTION 3 — PARKING SLOT  (Task 1 Entity)
//
//  Encapsulation: all members private, mutated only through
//  occupy() and release() to maintain invariants.
// ═

class ParkingSlot
{
private:
    string      slotId;           // unique identifier
    VehicleType supportedType;    // which vehicle class fits here
    string      zone;             // physical location label
    SlotStatus  status;           // AVAILABLE or OCCUPIED
    string      occupiedByPlate;  // plate of current vehicle ("" if free)

public:
    // Default constructor — needed so unordered_map can value-initialise
    ParkingSlot()
        : slotId(""), supportedType(VehicleType::CAR),
          zone(""), status(SlotStatus::AVAILABLE) {}

    ParkingSlot(const string& id, VehicleType type, const string& z)
        : slotId(id), supportedType(type),
          zone(z), status(SlotStatus::AVAILABLE) {}

    // ── Getters (read-only access for outside code) ──
    string      getSlotId()        const
    {
        return slotId;
    }
    VehicleType getSupportedType() const
    {
        return supportedType;
    }
    string      getZone()          const
    {
        return zone;
    }
    SlotStatus  getStatus()        const
    {
        return status;
    }
    string      getOccupiedBy()    const
    {
        return occupiedByPlate;
    }
    bool        isAvailable()      const
    {
        return status == SlotStatus::AVAILABLE;
    }

    /*
     * occupy() — marks slot as OCCUPIED
     * Called by ParkingManager during vehicle entry.
     * Pre-condition: slot must be AVAILABLE (enforced by ParkingManager).
     */
    void occupy(const string& plate)
    {
        status          = SlotStatus::OCCUPIED;
        occupiedByPlate = plate;
    }

    /*
     * release() — marks slot as AVAILABLE again
     * Called by ParkingManager during vehicle exit.
     */
    void release()
    {
        status          = SlotStatus::AVAILABLE;
        occupiedByPlate = "";
    }

    // Display one formatted row for reports
    void display() const
    {
        string statusStr = isAvailable()
                           ? "Available"
                           : "Occupied (" + occupiedByPlate + ")";

        cout << "  │ " << left
             << setw(8)  << slotId
             << "│ " << setw(12) << vehicleTypeToStr(supportedType)
             << "│ " << setw(10) << zone
             << "│ " << setw(22) << statusStr << "│\n";
    }
};

// ═
//  SECTION 4 — VEHICLE CLASS HIERARCHY
//
//  OOP: Abstraction via abstract base class VehicleBase
//       Inheritance: Motorcycle, Car, Truck
//       Polymorphism: virtual getTypeString() dispatched at runtime
//       Factory function: createVehicle() returns correct subtype
// ═

/*
 * VehicleBase — abstract base class
 * Cannot be instantiated directly.
 * Forces all subclasses to implement getTypeString().
 */
class VehicleBase
{
protected:
    string      plate;
    VehicleType type;

public:
    VehicleBase(const string& p, VehicleType t) : plate(p), type(t) {}
    virtual ~VehicleBase() {}   // virtual destructor — polymorphic delete safety

    // Getters
    string      getPlate() const
    {
        return plate;
    }
    VehicleType getType()  const
    {
        return type;
    }

    // Pure virtual — abstract interface, resolved at runtime
    virtual string getTypeString() const = 0;

    // Virtual display — can be overridden per subclass if needed
    virtual void display() const
    {
        cout << "  Vehicle: " << plate
             << "  Type: " << getTypeString() << "\n";
    }
};

class Motorcycle : public VehicleBase
{
public:
    explicit Motorcycle(const string& plate)
        : VehicleBase(plate, VehicleType::MOTORCYCLE) {}
    string getTypeString() const override
    {
        return "Motorcycle";
    }
};

class Car : public VehicleBase
{
public:
    explicit Car(const string& plate)
        : VehicleBase(plate, VehicleType::CAR) {}
    string getTypeString() const override
    {
        return "Car";
    }
};

class Truck : public VehicleBase
{
public:
    explicit Truck(const string& plate)
        : VehicleBase(plate, VehicleType::TRUCK) {}
    string getTypeString() const override
    {
        return "Truck";
    }
};

/*
 * createVehicle() — Factory function
 * Caller receives a heap-allocated vehicle pointer.
 * ParkingManager deletes it after extracting needed data.
 * Demonstrates runtime polymorphism: getTypeString() resolves correctly
 * regardless of which pointer type is stored.
 */
VehicleBase* createVehicle(const string& plate, VehicleType vt)
{
    switch (vt)
    {
    case VehicleType::MOTORCYCLE:
        return new Motorcycle(plate);
    case VehicleType::CAR:
        return new Car(plate);
    case VehicleType::TRUCK:
        return new Truck(plate);
    }
    return nullptr;
}

// ═
//  SECTION 5 — DATA RECORD STRUCTS
// ═

/*
 * ActiveVehicle — represents a vehicle currently inside the parking lot
 * Stored in the activeVehicles hash map.
 * Lightweight: only stores what's needed to process exit.
 */
struct ActiveVehicle
{
    string      plate;
    VehicleType type;
    string      slotId;
    time_t      entryTime;

    ActiveVehicle() : entryTime(0) {}
    ActiveVehicle(const string& p, VehicleType t,
                  const string& s, time_t e)
        : plate(p), type(t), slotId(s), entryTime(e) {}

    string entryTimeStr() const
    {
        return fmtTime(entryTime);
    }

    void display() const
    {
        cout << "  " << left
             << setw(14) << plate
             << setw(14) << vehicleTypeToStr(type)
             << setw(10) << slotId
             << entryTimeStr() << "\n";
    }
};

/*
 * ParkingRecord — IMMUTABLE transaction snapshot created at exit.
 *
 * CRITICAL DESIGN DECISION (Task 3 — price isolation):
 *   rateUsed is copied from TariffManager at the exact moment of exit.
 *   Once stored in the history vector, this struct is never modified.
 *   Subsequent calls to TariffManager::setRate() cannot alter past records
 *   because each record holds its own independent copy of the rate.
 *
 * The history vector itself is append-only: no element is ever updated
 * or removed, guaranteeing complete audit integrity.
 */
struct ParkingRecord
{
    string      plate;
    VehicleType type;
    string      slotId;
    string      zone;
    time_t      entryTime;
    time_t      exitTime;
    int         billedHours;  // ceiling-rounded hours charged
    double      rateUsed;     // SNAPSHOT of tariff at exit — immutable
    double      totalFee;     // billedHours × rateUsed — locked at exit

    double durationHours() const
    {
        return difftime(exitTime, entryTime) / 3600.0;
    }

    void displayReceipt() const
    {
        cout << "\n  \n";
        cout << "           PARKING RECEIPT              \n";
        cout << "  ═\n";
        cout << "   Plate      : " << left << setw(23) << plate        << "\n";
        cout << "   Type       : " << left << setw(23) << vehicleTypeToStr(type) << "\n";
        cout << "   Slot       : " << left << setw(23) << slotId       << "\n";
        cout << "   Zone       : " << left << setw(23) << zone         << "\n";
        cout << "   Entry      : " << left << setw(23) << fmtTime(entryTime) << "\n";
        cout << "   Exit       : " << left << setw(23) << fmtTime(exitTime)  << "\n";
        cout << fixed << setprecision(2);
        cout << "   Duration   : " << left << setw(23)
             << (to_string((int)durationHours()) + "h raw / "
                 + to_string(billedHours) + "h billed")  << "\n";
        cout << "   Rate Used  : " << left << setw(23)
             << (to_string((int)rateUsed) + " RWF/hr")   << "\n";
        cout << "   TOTAL FEE  : " << left << setw(23)
             << (to_string((int)totalFee) + " RWF")      << "\n";
        cout << "  \n";
    }
};

/*
 * WaitlistEntry — holds a vehicle that arrived when no slot was free.
 * Stored in the queue inside waitlistQueues map.
 */
struct WaitlistEntry
{
    string      plate;
    VehicleType type;
    time_t      arrivalTime;

    WaitlistEntry(const string& p, VehicleType t, time_t a)
        : plate(p), type(t), arrivalTime(a) {}
};

// ═
//  SECTION 6 — PARKING MANAGER  (Business Logic Layer)
//
//  Acts as a Facade: ConsoleUI calls only ParkingManager methods
//  and never touches data structures directly.
//
//  DSA operations covered:
//    Insertion  : addSlot(), vehicleEntry()
//    Deletion   : vehicleExit() removes from activeVehicles
//    Update     : occupy()/release() updates slot status
//    Traversal  : all report methods iterate data structures
// ═

class ParkingManager
{
private:

    // ── DATA STRUCTURE 1: HASH MAP — Slot Storage ──────────────────
    // unordered_map<slotId, ParkingSlot>
    // Justification: O(1) average insert/lookup/delete by slot ID.
    // Entry: addSlot() inserts.
    // Lookup: findAvailableSlot() reads, vehicleExit() reads.
    // Update: occupy()/release() called on the stored value.
    unordered_map<string, ParkingSlot> slotMap;

    // ── DATA STRUCTURE 2: BST MAP — Zone Index ─────────────────────
    // map<zoneName, vector<slotIds>>
    // Justification:
    //   map (Red-Black BST): O(log n) insert, guaranteed ordered keys
    //   → zones printed alphabetically in reports
    //   vector inside: O(1) push_back when adding slots to a zone
    //   → ordered list of slot IDs within each zone
    // This is a secondary index — primary data lives in slotMap.
    map<string, vector<string>> zoneSlotIndex;

    // ── DATA STRUCTURE 3: HASH MAP — Active Vehicles ───────────────
    // unordered_map<plate, ActiveVehicle>
    // Justification: O(1) duplicate-entry detection (guard in vehicleEntry).
    //   O(1) lookup at exit time.
    //   O(1) erase at exit time.
    unordered_map<string, ActiveVehicle> activeVehicles;

    // ── DATA STRUCTURE 4: VECTOR — Transaction History ─────────────
    // vector<ParkingRecord>
    // Justification:
    //   O(1) amortised push_back at each vehicle exit.
    //   Maintains insertion (chronological) order.
    //   O(n) sequential scan for reports — acceptable since history
    //   is read infrequently compared to entry/exit operations.
    //   Random access O(1) if indexed lookup is needed later.
    vector<ParkingRecord> history;

    // ── DATA STRUCTURE 5: QUEUE MAP — Waitlists ────────────────────
    // map<VehicleType, queue<WaitlistEntry>>
    // Justification:
    //   queue: FIFO — first vehicle to arrive gets the first freed slot.
    //   Separate queue per VehicleType: a freed Motorcycle slot serves
    //   only the Motorcycle queue, not the Car queue.
    //   map keyed by enum: stable iteration over all types in reports.
    map<VehicleType, queue<WaitlistEntry>> waitlistQueues;

    // ── COMPONENT: TariffManager ────────────────────────────────────
    TariffManager tariff;

    // ── PRIVATE HELPER: find first available slot for a vehicle type ─
    /*
     * Algorithm: iterate zoneSlotIndex (BST, alphabetical zones).
     * For each zone, scan its vector of slot IDs.
     * Check slotMap for availability AND type match.
     * Returns the first matching slot ID, or "" if none found.
     *
     * Time complexity: O(S) worst case where S = total number of slots.
     * This is unavoidable without a more complex secondary index,
     * which is not warranted for the scale of a city parking lot.
     */
    string findAvailableSlot(VehicleType vt)
    {
        for (auto& [zone, ids] : zoneSlotIndex)           // BST traversal
        {
            for (const string& id : ids)                   // vector scan
            {
                ParkingSlot& s = slotMap[id];              // O(1) hash lookup
                if (s.isAvailable() && s.getSupportedType() == vt)
                    return id;
            }
        }
        return "";
    }

    // ── PRIVATE HELPER: assign a vehicle to a specific slot ──────────
    void assignToSlot(const string& plate, VehicleType vt,
                      const string& slotId, time_t entryTime)
    {
        slotMap[slotId].occupy(plate);                     // UPDATE operation
        activeVehicles[plate] =                            // INSERT operation
            ActiveVehicle(plate, vt, slotId, entryTime);
        cout << "\n  Vehicle [" << plate << "] assigned to slot ["
             << slotId << "] — Zone: " << slotMap[slotId].getZone() << "\n";
    }

public:
    // Constructor — initialises all three waitlist queues
    ParkingManager()
    {
        waitlistQueues[VehicleType::MOTORCYCLE]; // default-construct queues
        waitlistQueues[VehicleType::CAR];
        waitlistQueues[VehicleType::TRUCK];
    }

    //
    //  TASK 1 — Add Parking Slot
    //  DSA: INSERT into slotMap (hash) and zoneSlotIndex (BST + vector)
    //
    bool addSlot(const string& slotId, VehicleType vt, const string& zone)
    {
        // Validation 1: slot ID must not already exist
        if (slotMap.count(slotId))
        {
            cout << "  Slot ID [" << slotId << "] already exists.\n";
            return false;
        }
        // Validation 2: zone must not be empty
        if (zone.empty())
        {
            cout << "  Zone name cannot be empty.\n";
            return false;
        }
        // INSERT into primary hash map — O(1)
        slotMap[slotId] = ParkingSlot(slotId, vt, zone);
        // INSERT slot ID into zone index vector — O(log n) for map lookup
        zoneSlotIndex[zone].push_back(slotId);

        cout << "  Slot added → ID: " << slotId
             << "  Type: " << vehicleTypeToStr(vt)
             << "  Zone: " << zone << "\n";
        return true;
    }

    //
    //  TASK 2 — Vehicle Entry
    //  DSA: LOOKUP in activeVehicles (O(1)), findAvailableSlot (O(S)),
    //       INSERT into activeVehicles, UPDATE slot status
    //       or ENQUEUE into waitlist
    //
    void vehicleEntry(const string& plate, VehicleType vt)
    {
        // Validation: plate not empty
        if (plate.empty())
        {
            cout << "  Plate number cannot be empty.\n";
            return;
        }
        // Duplicate check — O(1) hash lookup
        if (activeVehicles.count(plate))
        {
            cout << "  [" << plate << "] is already parked in slot ["
                 << activeVehicles[plate].slotId << "]. Cannot enter twice.\n";
            return;
        }

        // Use factory + polymorphism to confirm type (demonstrates OOP)
        VehicleBase* v = createVehicle(plate, vt);
        cout << "  Vehicle identified: " << v->getTypeString()
             << " — Plate: " << v->getPlate() << "\n";
        delete v; // factory object served its purpose

        time_t now = time(nullptr);
        string slotId = findAvailableSlot(vt);

        if (slotId.empty())
        {
            // Graceful handling: no slot → ENQUEUE on waitlist — O(1)
            waitlistQueues[vt].push(WaitlistEntry(plate, vt, now));
            cout << "   No available slot for "
                 << vehicleTypeToStr(vt) << ".\n"
                 << "  [" << plate << "] added to waitlist. "
                 << "Position: " << waitlistQueues[vt].size() << "\n";
            return;
        }
        // Slot found: assign vehicle — O(1) operations
        assignToSlot(plate, vt, slotId, now);
    }

    //
    //  TASK 3 & 4 — Vehicle Exit
    //  DSA: LOOKUP activeVehicles O(1), fee calculation,
    //       APPEND to history vector O(1),
    //       DELETE from activeVehicles O(1),
    //       UPDATE slot status O(1),
    //       DEQUEUE from waitlist O(1)
    //
    void vehicleExit(const string& plate)
    {
        // Validation: vehicle must be actively parked
        if (!activeVehicles.count(plate))
        {
            cout << "  Vehicle [" << plate
                 << "] is not currently parked in the system.\n";
            return;
        }

        // Retrieve active record — O(1) hash lookup
        ActiveVehicle& av = activeVehicles[plate];
        time_t exitTime   = time(nullptr);
        string slotId     = av.slotId;
        ParkingSlot& slot = slotMap[slotId];  // O(1)

        // ── Fee calculation (Task 3) ─────────────────────────────
        // calculateFee() uses CURRENT tariff rates at this exact moment.
        // The rate is immediately copied into ParkingRecord.rateUsed —
        // future calls to setRate() will NOT affect this stored value.
        int billedHours = 0;
        double fee = tariff.calculateFee(av.type, av.entryTime,
                                         exitTime, billedHours);
        double rateSnapshot = tariff.getRate(av.type); // snapshot for record

        // ── Build immutable ParkingRecord (price isolation) ──────
        ParkingRecord rec;
        rec.plate       = plate;
        rec.type        = av.type;
        rec.slotId      = slotId;
        rec.zone        = slot.getZone();
        rec.entryTime   = av.entryTime;
        rec.exitTime    = exitTime;
        rec.billedHours = billedHours;
        rec.rateUsed    = rateSnapshot;  // immutable copy
        rec.totalFee    = fee;

        // APPEND to history — O(1) amortised (vector push_back)
        history.push_back(rec);
        rec.displayReceipt();

        // ── Release slot (Task 4: UPDATE) ─────────────────────────
        slot.release();                         // UPDATE: OCCUPIED → AVAILABLE
        activeVehicles.erase(plate);            // DELETE from active hash map

        // ── Serve waitlist (DEQUEUE + re-assign) ─────────────────
        // Check if any vehicle of the same type is waiting
        auto& wq = waitlistQueues[av.type];
        if (!wq.empty())
        {
            WaitlistEntry next = wq.front();    // O(1) front access
            wq.pop();                           // O(1) dequeue
            cout << "\n   Slot freed. Assigning to waitlisted vehicle ["
                 << next.plate << "].\n";
            assignToSlot(next.plate, next.type, slotId, time(nullptr));
        }
    }

    //
    //  TASK 3 — Tariff Update
    //
    void updateTariff(VehicleType vt, double newRate)
    {
        try
        {
            tariff.setRate(vt, newRate);
            cout << "  Tariff for " << vehicleTypeToStr(vt)
                 << " updated to " << fixed << setprecision(2)
                 << newRate << " RWF/hr\n";
            cout << "   Note: This affects only future vehicle exits.\n"
                 << "    All completed records in history remain unchanged.\n";
        }
        catch (const invalid_argument& e)
        {
            cout << "  " << e.what() << "\n";
        }
    }

    void displayTariffs()
    {
        tariff.displayRates();
    }

    //
    //  REPORTS — All use TRAVERSAL operations on data structures
    //

    /*
     * reportAllSlots()
     * DSA: Traversal of zoneSlotIndex (BST map, ordered by zone)
     *      and slotMap (hash map, accessed by key)
     */
    void reportAllSlots() const
    {
        cout << "\n  \n";
        cout << "                    ALL PARKING SLOTS                  \n";
        cout << "  \n";
        cout << "  Slot ID      Vehicle Type Zone     Status      \n";
        cout << "  \n";

        if (slotMap.empty())
        {
            cout << "         No parking slots configured yet.             \n";
        }
        else
        {
            // BST traversal — zones appear alphabetically
            for (auto& [zone, ids] : zoneSlotIndex)
            {
                for (const string& id : ids)
                {
                    slotMap.at(id).display(); // hash lookup O(1)
                }
            }
        }
        cout << "  \n";
        cout << "  Total slots: " << slotMap.size() << "\n";
    }

    /*
     * reportAvailableSlots()
     * DSA: Traversal — same as above, filtered by isAvailable()
     */
    void reportAvailableSlots() const
    {
        cout << "\n \n";
        cout << "                AVAILABLE PARKING SLOTS                \n";
        cout << "  \n";
        cout << "  Slot ID      Vehicle Type Zone     Status      \n";
        cout << "  \n";

        int count = 0;
        for (auto& [zone, ids] : zoneSlotIndex)
        {
            for (const string& id : ids)
            {
                const ParkingSlot& s = slotMap.at(id);
                if (s.isAvailable())
                {
                    s.display();
                    count++;
                }
            }
        }
        if (count == 0)
            cout << "         No available slots at this time.             \n";
        cout << "  \n";
        cout << "  Available: " << count << " / " << slotMap.size() << "\n";
    }

    /*
     * reportParkedVehicles()
     * DSA: Traversal of activeVehicles hash map (unordered)
     *      plus hash lookup into slotMap for zone info
     */
    void reportParkedVehicles() const
    {
        cout << "\n  \n";
        cout << "                 CURRENTLY PARKED VEHICLES                  \n";
        cout << " \n";
        cout << "  Plate        Type         Slot     Entry Time       \n";
        cout << "  \n";

        if (activeVehicles.empty())
        {
            cout << "           No vehicles currently parked.                   \n";
        }
        else
        {
            for (auto& [plate, av] : activeVehicles)
            {
                cout << "  " << left
                     << setw(13) << av.plate
                     << "" << setw(13) << vehicleTypeToStr(av.type)
                     << "" << setw(9)  << av.slotId
                     << "" << setw(17) << av.entryTimeStr() << "\n";
            }
        }
        cout << "  \n";
        cout << "  Total parked: " << activeVehicles.size() << "\n";
    }

    /*
     * reportHistory()
     * DSA: Sequential traversal of history vector — O(n)
     * Records in chronological order of insertion
     */
    void reportHistory() const
    {
        cout << "\n   COMPLETED TRANSACTION HISTORY ("
             << history.size() << " records) \n";
        if (history.empty())
        {
            cout << "  No completed transactions yet.\n";
            return;
        }
        for (size_t i = 0; i < history.size(); i++)
        {
            cout << "\n  Record #" << (i + 1);
            history[i].displayReceipt();
        }
    }

    /*
     * reportDailyRevenue()
     * DSA: Sequential traversal of history vector
     *      Uses unordered_map<VehicleType, double> for per-type breakdown
     */
    void reportDailyRevenue() const
    {
        time_t now = time(nullptr);
        struct tm* today = localtime(&now);

        double total = 0;
        int txCount  = 0;
        unordered_map<VehicleType, double> byType;
        byType[VehicleType::MOTORCYCLE] = 0;
        byType[VehicleType::CAR]        = 0;
        byType[VehicleType::TRUCK]      = 0;

        for (const ParkingRecord& r : history)
        {
            struct tm* recDay = localtime(&r.exitTime);
            if (recDay->tm_year == today->tm_year &&
                    recDay->tm_yday == today->tm_yday)
            {
                total += r.totalFee;
                byType[r.type] += r.totalFee;
                txCount++;
            }
        }

        char dateBuf[12];
        strftime(dateBuf, sizeof(dateBuf), "%Y-%m-%d", today);

        cout << "\n  \n";
        cout << "         DAILY REVENUE REPORT       \n";
        cout << "  \n";
        cout << "   Date         : " << left << setw(17) << dateBuf << "\n";
        cout << "   Transactions : " << left << setw(17) << txCount  << "\n";
        cout << "  \n";
        cout << fixed << setprecision(2);
        cout << "   Motorcycle   : "
             << left << setw(14) << byType[VehicleType::MOTORCYCLE]
             << " RWF \n";
        cout << "   Car          : "
             << left << setw(14) << byType[VehicleType::CAR]
             << " RWF \n";
        cout << "   Truck        : "
             << left << setw(14) << byType[VehicleType::TRUCK]
             << " RWF \n";
        cout << "  \n";
        cout << "   TOTAL        : "
             << left << setw(14) << total << " RWF \n";
        cout << "  \n";
    }

    /*
     * searchVehicleHistory()
     * DSA: Linear search (traversal) of history vector — O(n)
     * Appropriate because history search is infrequent; a hash map
     * index could be added if search frequency increases.
     */
    void searchVehicleHistory(const string& plate) const
    {
        cout << "\n   History for Plate: " << plate << " \n";
        bool found = false;
        for (const ParkingRecord& r : history)
        {
            if (r.plate == plate)
            {
                r.displayReceipt();
                found = true;
            }
        }
        if (!found)
            cout << "  No past records found for [" << plate << "].\n";
    }

    /*
     * reportWaitlist()
     * DSA: Traversal of waitlistQueues map (ordered by VehicleType enum)
     * Note: queue does not support iteration — only size() is shown
     * to preserve FIFO integrity (no peeking mid-queue)
     */
    void reportWaitlist() const
    {
        cout << "\n   WAITLIST STATUS \n";
        bool any = false;
        for (auto& [vt, q] : waitlistQueues)
        {
            if (!q.empty())
            {
                cout << "  " << vehicleTypeToStr(vt) << " : "
                     << q.size() << " vehicle(s) waiting\n";
                any = true;
            }
        }
        if (!any) cout << "  No vehicles on any waitlist.\n";
    }

    // Accessor for demo purposes
    int totalSlots() const
    {
        return (int)slotMap.size();
    }
};

// ═
//  SECTION 7 — CONSOLE UI  (Presentation Layer)
//
//  All user I/O is isolated here.
//  ParkingManager knows nothing about cin/cout formatting.
//  This separation means the business logic can be reused with a
//  different UI (GUI, REST API, etc.) without any changes.
// ═

class ConsoleUI
{
public:
    // Read a non-empty trimmed string
    static string readString(const string& prompt)
    {
        string val;
        while (true)
        {
            cout << prompt;
            if (!getline(cin, val))
            {
                val = "";
                continue;
            }
            // Trim whitespace
            size_t a = val.find_first_not_of(" \t\r\n");
            size_t b = val.find_last_not_of(" \t\r\n");
            if (a == string::npos)
            {
                cout << "  Input cannot be empty. Try again.\n";
                continue;
            }
            return val.substr(a, b - a + 1);
        }
    }

    // Read an integer in [lo, hi] — handles non-numeric input
    static int readInt(const string& prompt, int lo, int hi)
    {
        int val;
        while (true)
        {
            cout << prompt;
            if (cin >> val)
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (val >= lo && val <= hi) return val;
            }
            else
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "  Enter a number between " << lo
                 << " and " << hi << ".\n";
        }
    }

    // Read a strictly positive double
    static double readPositiveDouble(const string& prompt)
    {
        double val;
        while (true)
        {
            cout << prompt;
            if (cin >> val && val > 0)
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return val;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  Please enter a positive number.\n";
        }
    }

    // Display vehicle type sub-menu and return selection
    static VehicleType readVehicleType()
    {
        cout << "  Vehicle type:\n"
             << "    1 = Motorcycle\n"
             << "    2 = Car\n"
             << "    3 = Truck\n";
        int c = readInt("  Choice: ", 1, 3);
        switch (c)
        {
        case 1:
            return VehicleType::MOTORCYCLE;
        case 2:
            return VehicleType::CAR;
        default:
            return VehicleType::TRUCK;
        }
    }

    // Convert plate to uppercase for consistency
    static string normalisePlate(const string& plate)
    {
        string p = plate;
        transform(p.begin(), p.end(), p.begin(), ::toupper);
        return p;
    }

    static void printMenu()
    {
        cout << "\n";
        cout << "  \n";
        cout << "    KIGALI SMART PARKING MANAGEMENT SYSTEM     \n";
        cout << " \n";
        cout << "   OPERATIONS                                  \n";
        cout << "   [1]  Add Parking Slot                       \n";
        cout << "   [2]  Vehicle Entry                          \n";
        cout << "   [3]  Vehicle Exit & Payment                 \n";
        cout << "   [4]  View / Update Tariffs                  \n";
        cout << "  \n";
        cout << "   REPORTS                                     \n";
        cout << "   [5]  All Parking Slots                      \n";
        cout << "   [6]  Available Slots Only                   \n";
        cout << "   [7]  Currently Parked Vehicles              \n";
        cout << "   [8]  Full Transaction History               \n";
        cout << "   [9]  Daily Revenue Report                   \n";
        cout << "   [10] Search History by Plate Number         \n";
        cout << "   [11] View Waitlist                          \n";
        cout << "  \n";
        cout << "   [0]  Exit System                            \n";
        cout << "  \n";
        cout << "  Your choice: ";
    }
};

// ═
//  SECTION 8 — DEMO DATA LOADER
//
//  Pre-populates the system with realistic slots so all features
//  can be demonstrated immediately without manual slot creation.
//  Also runs a scripted test sequence to show all functionalities.
// ═

void loadDemoSlots(ParkingManager& pm)
{
    cout << "\n  \n";
    cout << "    Loading demo parking slot configuration\n";
    cout << "  \n";

    // Zone A — Cars (3 slots)
    pm.addSlot("A01", VehicleType::CAR,        "Zone-A");
    pm.addSlot("A02", VehicleType::CAR,        "Zone-A");
    pm.addSlot("A03", VehicleType::CAR,        "Zone-A");

    // Zone B — Motorcycles (3 slots)
    pm.addSlot("B01", VehicleType::MOTORCYCLE, "Zone-B");
    pm.addSlot("B02", VehicleType::MOTORCYCLE, "Zone-B");
    pm.addSlot("B03", VehicleType::MOTORCYCLE, "Zone-B");

    // Zone C — Trucks (2 slots)
    pm.addSlot("C01", VehicleType::TRUCK,      "Zone-C");
    pm.addSlot("C02", VehicleType::TRUCK,      "Zone-C");

    // Zone D — Mixed (extra cars)
    pm.addSlot("D01", VehicleType::CAR,        "Zone-D");
    pm.addSlot("D02", VehicleType::CAR,        "Zone-D");

    cout << "  \n";
    cout << "    10 slots configured across 4 zones.\n";
    cout << "  \n\n";
}

/*
 * runDemoTest()
 * Demonstrates all system functionalities with test inputs.
 * This satisfies the requirement:
 *   "test inputs must be provided to demonstrate all system functionalities"
 *
 * The demo is separate from the interactive menu so users can
 * run it once at startup and then use the menu normally.
 */
void runDemoTest(ParkingManager& pm)
{
    cout << "\n";
    cout << "  \n";
    cout << "             AUTOMATED DEMO — ALL FEATURES              \n";
    cout << "  \n";

    // ── DEMO 1: Duplicate slot ID rejection ──────────────────────
    cout << "\n  [DEMO 1] Duplicate Slot ID rejection:\n";
    pm.addSlot("A01", VehicleType::CAR, "Zone-A"); // should fail

    // ── DEMO 2: Normal vehicle entries ────────────────────────────
    cout << "\n  [DEMO 2] Vehicle entries:\n";
    pm.vehicleEntry("RAC001A", VehicleType::CAR);
    pm.vehicleEntry("RAC002B", VehicleType::CAR);
    pm.vehicleEntry("RAM001C", VehicleType::MOTORCYCLE);
    pm.vehicleEntry("RAT001D", VehicleType::TRUCK);

    // ── DEMO 3: Duplicate plate rejection ─────────────────────────
    cout << "\n  [DEMO 3] Duplicate plate rejection:\n";
    pm.vehicleEntry("RAC001A", VehicleType::CAR); // already parked

    // ── DEMO 4: View currently parked ────────────────────────────
    cout << "\n  [DEMO 4] Currently parked vehicles:\n";
    pm.reportParkedVehicles();

    // ── DEMO 5: Tariff update + price isolation proof ─────────────
    cout << "\n  [DEMO 5] Tariff update demonstration:\n";
    pm.displayTariffs();
    cout << "\n  Updating Car tariff from 1000 → 1500 RWF/hr...\n";
    pm.updateTariff(VehicleType::CAR, 1500.0);
    pm.displayTariffs();

    // ── DEMO 6: Vehicle exits (fee uses NEW tariff for cars) ──────
    cout << "\n  [DEMO 6] Vehicle exits — receipt printed:\n";
    // RAC001A exits AFTER the price change → billed at 1500
    pm.vehicleExit("RAC001A");
    // RAM001C exits — motorcycle, unchanged rate
    pm.vehicleExit("RAM001C");
    // RAT001D exits — truck rate
    pm.vehicleExit("RAT001D");

    // ── DEMO 7: Waitlist demonstration ────────────────────────────
    cout << "\n  [DEMO 7] Waitlist — fill all car slots then add another:\n";
    pm.vehicleEntry("RAC003E", VehicleType::CAR);
    pm.vehicleEntry("RAC004F", VehicleType::CAR);
    pm.vehicleEntry("RAC005G", VehicleType::CAR);
    pm.vehicleEntry("RAC006H", VehicleType::CAR); // this goes to waitlist
    pm.reportWaitlist();

    // ── DEMO 8: Exit frees slot → waitlisted vehicle auto-assigned ─
    cout << "\n  [DEMO 8] Exiting RAC002B frees a slot for waitlisted RAC006H:\n";
    pm.vehicleExit("RAC002B");
    pm.reportParkedVehicles();

    // ── DEMO 9: Transaction history ───────────────────────────────
    cout << "\n  [DEMO 9] Full transaction history:\n";
    pm.reportHistory();

    // ── DEMO 10: Search by plate ──────────────────────────────────
    cout << "\n  [DEMO 10] Search history for RAC001A:\n";
    pm.searchVehicleHistory("RAC001A");

    // ── DEMO 11: Daily revenue ────────────────────────────────────
    cout << "\n  [DEMO 11] Daily revenue report:\n";
    pm.reportDailyRevenue();

    // ── DEMO 12: Available slots report ──────────────────────────
    cout << "\n  [DEMO 12] Available slots:\n";
    pm.reportAvailableSlots();

    // ── DEMO 13: Invalid tariff update ───────────────────────────
    cout << "\n  [DEMO 13] Invalid tariff (negative value) rejection:\n";
    pm.updateTariff(VehicleType::MOTORCYCLE, -100.0);

    cout << "\n  ══ Demo complete. Entering interactive menu. ══\n";
}

// ═
//  SECTION 9 — MAIN  (Wires layers together)
// ═

int main()
{
    ParkingManager pm;
    ConsoleUI      ui;

    // Step 1: Load demo slot configuration
    loadDemoSlots(pm);

    // Step 2: Ask user whether to run full demo first
    cout << "  Run automated demo to see all features? (1=Yes / 0=No): ";
    int runDemo;
    if (!(cin >> runDemo))
    {
        runDemo = 0;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (runDemo == 1) runDemoTest(pm);

    // Step 3: Interactive menu loop
    while (true)
    {
        ConsoleUI::printMenu();

        int choice;
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  Please enter a valid number.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\n";

        switch (choice)
        {

        // ── TASK 1: Add slot ──────────────────────────────────────
        case 1:
        {
            cout << "  ── Add New Parking Slot ──\n";
            string id   = ConsoleUI::readString("  Slot ID     : ");
            VehicleType vt = ConsoleUI::readVehicleType();
            string zone = ConsoleUI::readString("  Zone name   : ");
            pm.addSlot(id, vt, zone);
            break;
        }

        // ── TASK 2: Vehicle entry ─────────────────────────────────
        case 2:
        {
            cout << "  ── Vehicle Entry ──\n";
            string plate = ConsoleUI::normalisePlate(
                               ConsoleUI::readString("  Plate number: "));
            VehicleType vt = ConsoleUI::readVehicleType();
            pm.vehicleEntry(plate, vt);
            break;
        }

        // ── TASK 4: Vehicle exit ──────────────────────────────────
        case 3:
        {
            cout << "  ── Vehicle Exit ──\n";
            string plate = ConsoleUI::normalisePlate(
                               ConsoleUI::readString("  Plate number: "));
            pm.vehicleExit(plate);
            break;
        }

        // ── TASK 3: Tariff management ─────────────────────────────
        case 4:
        {
            pm.displayTariffs();
            cout << "\n  Update a tariff? (1=Yes / 0=No): ";
            int ans = ConsoleUI::readInt("", 0, 1);
            if (ans == 1)
            {
                VehicleType vt  = ConsoleUI::readVehicleType();
                double newRate  = ConsoleUI::readPositiveDouble(
                                      "  New rate (RWF/hr): ");
                pm.updateTariff(vt, newRate);
            }
            break;
        }

        // ── REPORTS ──────────────────────────────────────────────
        case 5:
            pm.reportAllSlots();
            break;
        case 6:
            pm.reportAvailableSlots();
            break;
        case 7:
            pm.reportParkedVehicles();
            break;
        case 8:
            pm.reportHistory();
            break;
        case 9:
            pm.reportDailyRevenue();
            break;

        case 10:
        {
            string plate = ConsoleUI::normalisePlate(
                               ConsoleUI::readString("  Plate to search: "));
            pm.searchVehicleHistory(plate);
            break;
        }

        case 11:
            pm.reportWaitlist();
            break;

        case 0:
            cout << "  System shutting down. Goodbye.\n";
            return 0;

        default:
            cout << "  Invalid choice. Enter 0–11.\n";
        }
    }
}
