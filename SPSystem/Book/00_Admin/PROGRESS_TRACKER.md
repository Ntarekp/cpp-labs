# Progress Tracker

> **Last updated:** Curriculum v2.0 — construction-first dual-track  
> **Current phase:** I — Construction (Track A)  
> **Next recommended topic:** **SEC-01** (Track A primary)

---

## Program Status

| Metric | Value |
|--------|-------|
| Enrollment date | 2026-06-10 |
| Curriculum version | 2.0 |
| Milestone | M0 `COMPLETE` |
| Active track | **A — Software Engineering Core** |
| Active topic | **SEC-01** — lesson package generated |
| Design track (22) | SDC-01 locked until SEC-05 |
| Parallel track B | CST-01 locked until SEC-03 |
| Total hours logged | 0 |

---

## Track A — Software Engineering Core (Phase A1)

| ID | Topic | Status |
|----|-------|--------|
| SEC-01 | Source code → running program | `READY` ← **start here** |
| SEC-02 | Build systems | `LOCKED` |
| SEC-03 | Headers & source files | `LOCKED` |
| SEC-04 | Translation units | `LOCKED` |
| SEC-05 | Linking | `LOCKED` |
| SEC-06 | Memory layout | `LOCKED` |
| SEC-07 | Variables & types | `LOCKED` |
| SEC-08 | Functions | `LOCKED` |
| SEC-09 | Classes | `LOCKED` |
| SEC-10 | Object lifetimes & RAII | `LOCKED` |
| SEC-11 | STL foundations | `LOCKED` |
| SEC-12 | Complexity analysis | `LOCKED` |

**Phase A1 exam:** FE-A1 `NOT_TAKEN`

---

## Track B — Computer Science Theory (Phase B1)

| ID | Topic | Status | Unlocks after |
|----|-------|--------|---------------|
| CST-01 | What is computation? | `LOCKED` | SEC-03 |
| CST-02 | Information & encoding | `LOCKED` | SEC-07 |
| CST-03 | Logic & invariants | `LOCKED` | SEC-09 |
| CST-04 | Abstraction theory | `LOCKED` | CST-03 |
| CST-05 | Induction & proofs | `LOCKED` | SEC-12 |
| CST-06 | Specification | `LOCKED` | CST-03 |
| CST-07 | Testing theory | `LOCKED` | DBG-01 |
| CST-08 | Security models | `LOCKED` | FS-02 |

**Phase B1 exam:** FE-B1 `NOT_TAKEN`

**Merge gate:** `LOCKED` (requires M1 + M1b)

---

## Section Progress (summary)

| Section | Track | Status |
|---------|-------|--------|
| 01 Foundations | B | `LOCKED` (CST after SEC-03) |
| 02 C++ Core | A | `IN_PROGRESS` (SEC-01 ready) |
| 03 DSA | Merged | `LOCKED` |
| 04–20 | Merged | `LOCKED` |

---

## Milestones

| ID | Title | Status |
|----|-------|--------|
| M0 | University enrolled | `COMPLETE` |
| M1 | Construction fundamentals | `NOT_STARTED` |
| M1b | Theory foundations | `NOT_STARTED` |
| M2 | Merge complete | `NOT_STARTED` |
| M3–M15 | See MILESTONES.md | `NOT_STARTED` |

---

## SPSystem Case Study

| Activity | Status | Unlock |
|----------|--------|--------|
| Build graph observation | `LOCKED` | SEC-05 |
| Class reading | `LOCKED` | SEC-09 |
| STL manager reading | `LOCKED` | SEC-11 |
| Full case study | `LOCKED` | DSA-05 |
| LAB-01 rebuild | `LOCKED` | Merge + lab prerequisites |

---

## Auto-Recommendation

**Primary:** `SEC-01 — Source code → running program`  
**Rationale:** Multi-file codebase requires build/load understanding first; theory enriches after SEC-03.

**Do not start:** CST-01, F-01, SPSystem deep dive, LAB-01.

---

*Update after every mastery gate attempt.*
