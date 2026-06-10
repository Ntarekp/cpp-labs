# SDC-01 — Parking Management System (Design Challenge)

> **Unlock:** SEC-05 mastered.  
> **Compare after submit:** SPSystem case study (not before).

## Functional requirements

1. Configure parking slots (ID, vehicle type, zone).
2. Register vehicle entry — assign available compatible slot.
3. Register vehicle exit — calculate fee, release slot, archive record.
4. Tariffs per vehicle type (hourly); partial hours bill as full hours.
5. Reports: parked vehicles, history by plate, daily revenue.

## Non-functional (design must address)

- Console-first; file persistence acceptable
- Entry/exit must be O(1) average for plate lookup (state target complexity)
- No duplicate active session per plate
- Data survives restart

## Design deliverables (submit before seeing sample)

1. Component diagram
2. Class/module responsibilities (one sentence each)
3. Data structure per module with operation complexities
4. Entry sequence diagram
5. Exit sequence diagram
6. Invariants (minimum 5)
7. Failure modes (3) + mitigations

## SEC concepts exercised

SEC-05 (linking modules), SEC-09 preview (entities), SEC-11 preview (maps), SEC-12 preview (complexity targets).
