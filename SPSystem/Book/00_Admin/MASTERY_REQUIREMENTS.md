# Mastery Requirements

> Every section has **entry requirements**, **per-topic gates**, **section exit exam**, and **mastery evidence**.

## Global Mastery Gate Template

For topic `<TOPIC_ID>`, the learner must pass **all** of:

| # | Requirement | Evidence |
|---|-------------|----------|
| G1 | Four-layer explain-back (Beginner → Professional) | Written or oral, instructor-graded |
| G2 | Prediction exercise (no execution) | ≥80% correct on 5 scenarios |
| G3 | Tradeoff defense | Survive 10-min Socratic challenge |
| G4 | Exercises complete | 100% beginner + intermediate; ≥70% advanced |
| G5 | Rebuild-from-memory | Section-specific challenge passed |
| G6 | Flashcard oral | ≥90% of topic deck |
| G7 | Common mistakes audit | Identify 3 mistakes in buggy code sample |

**Pass threshold:** All of G1–G3, G5–G6; G4 as stated; G7 ≥2/3.

**States:** `NOT_STARTED` → `IN_PROGRESS` → `REMEDIAL` → `MASTERED`

---

## Track A Phase 1 — Software Construction (SEC-01–12)

### Entry
None. **Program entry:** SEC-01.

### Per-Topic Minimum
- SEC-01: rebuild 5-stage pipeline diagram; fix a linker error.
- SEC-02: CMake project with 2+ targets.
- SEC-05: explain `undefined reference` vs compile error.
- SEC-06: stack frame diagram for 3-level call.
- SEC-10: RAII class from scratch; no leaks.
- SEC-11: use `vector`, `map`, `unordered_map` with justification.
- SEC-12: Big-O analysis of 3 SPSystem operations (observation).

### Phase Exit Exam (FE-A1)
| Component | Weight | Content |
|-----------|--------|---------|
| Written | 30% | Build pipeline, memory layout, linkage |
| Coding | 40% | 3-file CMake project from spec (3 hours) |
| Oral | 20% | Explain SPSystem build graph from memory |
| Analysis | 10% | Justify one STL container choice with Big-O |

**Pass:** ≥80% overall; coding ≥75%.

### Mastery Evidence
- CMake project in `02_Cpp_Core/artifacts/`
- RFS-A1: 3-file rebuild in ≤3 hours

---

## Track B Phase 1 — Reasoning Foundations (CST-01–08)

### Entry
CST-01 unlocks after SEC-03 mastered (not before).

### Per-Topic Minimum
- CST-03: write 5 invariants for a module you built in SEC phase.
- CST-05: induction proof of sum formula.
- CST-06: 2-page specification for a management domain.

### Phase Exit Exam (FE-B1)
| Component | Weight | Content |
|-----------|--------|---------|
| Written | 40% | Logic, invariants, specification reading |
| Oral | 30% | Computation model connected to real compile pipeline |
| Practical | 30% | Decompose novel problem into modules + invariants |

**Pass:** ≥75% overall; no component below 60%.

### Merge Gate
Requires **FE-A1 + FE-B1** + CST-01, CST-03, CST-05 mastered.

---

## Section 01 — Foundations (Track B)

Maps to CST-01–CST-08. **Not program entry.** See Track B above.

Legacy FE-01 replaced by **FE-B1**.

---

## Section 02 — C++ Core

### Entry
SEC-01–12 mastered (FE-A1 passed); DBG-01 mastered.

### Per-Topic Minimum
- CPP-01: rebuild build pipeline diagram; cause and fix link error.
- CPP-04: draw stack frame for nested calls; explain UB scenario.
- CPP-07: implement Rule-of-Five class from scratch.
- CPP-09: implement thin wrapper over `vector` with correct iterators.
- CPP-14: CMake project exporting a library.

### Section Exit Exam (FE-02)
| Component | Weight |
|-----------|--------|
| Written | 35% — types, linkage, ODR, memory |
| Coding | 45% — 3-hour supervised implementation |
| Oral | 20% — defend memory choices |

**Coding task:** Implement a generic `Stack<T>` + linked-list `Queue<T>` + unit tests. No internet. Allowed: standard headers only.

**Pass:** ≥80% overall; coding ≥75%.

---

## Section 03 — DSA

### Entry
FE-02 passed.

### Per-Topic Minimum
- DSA-01: prove O(log n) for binary search; amortized analysis of dynamic array.
- DSA-05: implement hash table with chaining from scratch.
- DSA-06: implement BST insert/search/delete.
- DSA-14: structure selection justification for 5 domains.

### Section Exit Exam (FE-03)
| Component | Weight |
|-----------|--------|
| Written | 40% |
| Implementation | 40% — hash map + BST from scratch |
| Oral complexity | 20% |

**Pass:** ≥80%.

---

## Section 04 — OOP

### Entry
FE-03 passed; CPP-07 mastered.

### Section Exit Exam (FE-04)
Design + implement a polymorphic shape system **and** a domain model (e.g., `Account` hierarchy) with documented invariants. 4-hour exam.

**Pass:** ≥75%; must demonstrate Liskov compliance in oral.

---

## Section 05 — Design Patterns

### Entry
FE-04 passed.

### Section Exit Exam (FE-05)
Refactor a provided 500-line monolith into named patterns. Document which patterns were **not** used and why.

**Pass:** ≥75%; oral defense of over-engineering risks.

---

## Section 06 — Software Architecture

### Entry
FE-05 passed.

### Section Exit Exam (FE-06)
Produce C4 diagrams + ADR set for a multi-module school management system. 48-hour take-home; oral defense.

**Pass:** ≥80%.

---

## Section 07 — Operating Systems

### Entry
FE-02 passed; CPP-04, CPP-05 mastered.

### Section Exit Exam (FE-07)
| Component | Content |
|-----------|---------|
| Written | Virtual memory, scheduling, synchronization |
| Coding | `mini-shell` + `producer-consumer` with pthreads/threads |
| Oral | Deadlock four conditions |

**Pass:** ≥80%; coding must be race-free under instructor review.

---

## Section 08 — Algorithms

### Entry
FE-03 passed.

### Section Exit Exam (FE-08)
6 problems spanning DP, graphs, greedy — 5 hours. ≥4/6 correct for pass.

---

## Section 09 — Competitive Programming

### Entry
DSA-01–06; ALG-01–03.

### Tier Gates
See `09_Competitive_Programming/ROADMAP.md` — each tier requires rating-equivalent solve counts.

### Section Exit
**200 problems** logged; **virtual contest** top 50% in Div 2 equivalent.

---

## Section 10 — Debugging

### Entry
F-08 passed.

### Section Exit Exam (FE-10)
Debug 3 seeded buggy programs (memory, logic, concurrency) within time limits.

**Pass:** Root cause + fix + regression test for all 3.

---

## Section 11 — File Systems

### Entry
CPP-11; OS-08 recommended.

### Section Exit Exam (FE-11)
Design serialization format with schema versioning; implement save/load with corruption detection.

---

## Section 12 — Networking

### Entry
FE-07 passed; OS-07 mastered.

### Section Exit Exam (FE-12)
Implement TCP echo server + threaded HTTP GET handler (static files).

---

## Section 13 — Databases

### Entry
DSA-06–07; FS-02.

### Section Exit Exam (FE-13)
Schema design for banking (3NF); implement SQLite layer; explain a query plan.

---

## Section 14 — Project Laboratories

### Per-Lab Mastery (not "completed project")

| Criterion | Required |
|-----------|----------|
| Rebuild core module from memory | Yes |
| Explain every DS choice with complexity | Yes |
| Oral "change request" defense | 15-min |
| Written retrospective | Tradeoffs doc |
| **No copy-paste from prior code** | Rebuild attempt timed |

### Laboratory Portfolio Exit
**6 labs mastered** (including at least 2 advanced: LAB-05/06/07/08).

---

## Section 15 — Open Source Studies

### Exit
**5 codebases** studied with written reports (see OSS roadmap). Oral on one: trace a feature across 5+ files.

---

## Section 16 — Research

### Exit
One literature review (8+ papers) + one standards deep-read (C++ section or RFC).

---

## Section 17 — Interview Preparation

### Exit
**10 mock interviews** recorded; ≥7 pass instructor rubric.

---

## Section 18 — Examinations

Cumulative finals at phase boundaries — see `GRADUATION_REQUIREMENTS.md`.

---

## Section 19 — Capstones

### Per-Capstone
- Design document approved **before** code.
- Implementation oral (code walk without IDE navigation hints).
- Operations doc: deploy, monitor, failure modes.

---

## Section 20 — Rebuild From Scratch

### Tier Gates
Each tier challenge passed under exam conditions (see RFS roadmap).

**RFS Master:** CAP-05 equivalent — full system in 48 hours.

---

## Grading Rubric (Universal)

| Score | Meaning |
|-------|---------|
| 90–100 | Professional — could ship with review |
| 80–89 | Solid — minor gaps |
| 70–79 | Pass — remedial on weak dimension |
| 60–69 | Fail — full remedial track |
| <60 | Fail — repeat section foundations |

---

## Remedial Policy

- Max 3 attempts per section exit exam.
- After 2 failures: mandatory weakness registry review + 20-hour remedial block.
- No capstone until all FE exams for Phases I–IV passed.

---

*Mastery requirements version: 1.0*
