# Case Study — SPSystem (Kigali Smart Parking)

> **Classification:** Laboratory case study for LAB-01  
> **Not curriculum evidence** — studying this file does not prove mastery of any topic.

---

## When to use this case study

| Prerequisite mastered | Study activity |
|----------------------|----------------|
| SEC-05 (Linking) | Read README `g++` line — draw link graph |
| SEC-09 (Classes) | Read `Vehicle`, `ParkingSlot` — memory sketch |
| SEC-11 (STL) | Observe managers — **not** proof of hash table mastery |
| PAT-06 (Facade) | Compare `ParkingSystem` to Facade pattern definition |
| DSA-05 (Hash tables) | Analyze `SlotManager` — after implementing hash table yourself |
| DSA-14 (Domain selection) | Critique two-layer index design |
| FS-02 (Serialization) | Review `*.txt` persistence — list invariants |
| ARCH-02 (Layers) | Map managers to layers |

**First unlock:** SEC-05 (build graph only).  
**Full case study:** After DSA-05 mastered.  
**LAB-01 gate:** Independent rebuild — no SPSystem source open.

---

## System summary

| Attribute | Value |
|-----------|-------|
| Domain | Public parking management |
| Language | C++17 |
| UI | Console menu |
| Persistence | Text files (`slots.txt`, `history.txt`, etc.) |
| Architecture | Facade + 4 managers |

## Components (for directed reading)

| Component | File(s) | Curriculum topics illustrated |
|-----------|---------|------------------------------|
| Types & enums | `types.h` | CPP-03, OOP-07 |
| Facade | `ParkingSystem.*` | PAT-06, ARCH-02 |
| Slot inventory | `SlotManager.*` | DSA-05, DSA-14, B-04 secondary index |
| Active sessions | `VehicleManager.*` | DSA-05 |
| Tariffs | `TariffManager.*` | DSA-06 vs map tradeoff |
| History | `HistoryManager.*` | DSA-02, DSA-14 (O(n) search tradeoff) |
| Entry point | `main.cpp` | CPP-01, DBG-02 |

## Diagrams

See project root `diagrams.md` — study after ARCH-02.

## Analysis questions (submit written answers)

1. What invariants must hold between `SlotManager` and `VehicleManager`?
2. Why both `unordered_map` and `map`+`vector` index in `SlotManager`?
3. What fails first under concurrent entry (two threads)? Which OS topic answers this?
4. How would you add SQLite without violating Facade boundaries?
5. What is **not** production-ready in this design? (security, scale, audit)

## Comparison exercises

After your LAB-01 rebuild attempt:

| Compare | Question |
|---------|----------|
| Your code vs SPSystem | Where did you diverge? Was divergence justified? |
| SPSystem vs Redis | Active vehicle map vs in-memory dict design |
| SPSystem vs SQLite | File persistence vs transactional store |

## Forbidden uses

- ❌ Proof of C++ mastery
- ❌ Proof of hash table understanding
- ❌ Copy-paste for LAB-01 rebuild gate
- ❌ Substitute for FE-02, FE-03, or LAB-01 oral

---

*Case study v1.0 — illustrative only*
