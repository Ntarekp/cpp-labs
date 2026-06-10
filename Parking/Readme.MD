═══════════════════════════════════════════════════════
  KIGALI SMART PARKING MANAGEMENT SYSTEM — README
═══════════════════════════════════════════════════════

COMPILE & RUN
  g++ -std=c++17 -o parking main.cpp
  ./parking

DEFAULT TARIFFS
  Motorcycle : 500  RWF/hr
  Car        : 1000 RWF/hr
  Truck      : 2000 RWF/hr
  Partial hours billed as full hours (ceiling rule).
  e.g. 15 min = 1 hr billed, 1h 20m = 2 hrs billed.

DEMO SLOTS PRE-LOADED
  A01 A02 A03  → Car        Zone-A
  B01 B02 B03  → Motorcycle Zone-B
  C01 C02      → Truck      Zone-C
  D01 D02      → Car        Zone-D

MENU OPTIONS
  [1]  Add Parking Slot         — supply ID, type, zone
  [2]  Vehicle Entry            — plate is auto-uppercased
  [3]  Vehicle Exit & Payment   — prints fee receipt
  [4]  View / Update Tariffs    — change takes effect immediately
                                  history records are unaffected
  [5]  All Parking Slots        — full slot table by zone
  [6]  Available Slots          — free slots only
  [7]  Currently Parked         — live vehicles with entry time
  [8]  Transaction History      — all completed receipts
  [9]  Daily Revenue            — today's totals by type
  [10] Search by Plate          — past records for one vehicle
  [11] Waitlist Status          — queued vehicles per type
  [0]  Exit

ARCHITECTURE DIAGRAMS
  Paste diagram code blocks into https://mermaid.live
  to render layered architecture, class diagram,
  entry flowchart, exit flowchart, and DSA map.

PRICE UPDATE RULE
  setRate() only changes future fee calculations.
  Each ParkingRecord stores a locked snapshot of
  the rate that was active at the time of exit.
  The history vector is append-only — immutable.
═══════════════════════════════════════════════════════
