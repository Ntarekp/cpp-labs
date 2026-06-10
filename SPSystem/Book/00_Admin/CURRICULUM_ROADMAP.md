# Complete Curriculum Roadmap (v2.0)

> **Outcome:** Practical software engineering mastery **combined with** deep CS understanding — design and implement professional software from first principles.

## Dual-Track Model

See [`LEARNING_TRACKS.md`](LEARNING_TRACKS.md) for full track specification.

| Track | Role | Phase 1 focus |
|-------|------|---------------|
| **A — Software Engineering Core** | **Primary path** | Software construction fundamentals (SEC-01–12) |
| **B — Computer Science Theory** | Enrichment (parallel) | Reasoning foundations (CST-01–08) |

**Merge** after Phase A1 + Phase B1 → unified progression.

## Program Structure (revised)

| Phase | Track | Sections | Theme | Duration (est.) |
|-------|-------|----------|-------|-----------------|
| **I — Construction** | **A** | 02 (SEC), 10 (DBG-01) | Source → program → memory → STL → complexity | 3–4 months |
| **I — Reasoning** | **B** (parallel) | 01 (CST) | Computation, logic, proof — *after* seeing real code | 3–5 months |
| **II — Merge** | A+B | 02 (adv), 03, 04, 08 | OOP, DSA implementation, algorithms | 8–12 months |
| **III — Structure** | A+B | 05, 06, 11, 13 | Patterns, architecture, persistence | 6–9 months |
| **IV — Systems** | A+B | 07, 12, 02 (adv) | OS, networking, low-level | 8–12 months |
| **V — Speed & Rigor** | A+B | 09, 17, 18 | CP, exams, interviews | Ongoing parallel |
| **VI — Synthesis** | A+B | 14, 15, 19, 20 | Labs, OSS, capstones, rebuild | 12–18 months |

**Total estimated duration:** 3–5 years at 15–20 hrs/week (see `STUDY_HOURS.md`).

---

## Track A Phase 1 — Software Construction Fundamentals

**Purpose:** Understand why your multi-file codebase compiles, links, loads, executes, and stores data — **before** abstract CS theory.

**Entry:** None. **Start here:** SEC-01.

| Order | ID | Title | Maps to | Per-topic layers |
|-------|-----|-------|---------|------------------|
| 1 | SEC-01 | Source code → running program | CPP-01 | Theory, Practice, Lab†, RFS, Exam, Interview, OSS‡ |
| 2 | SEC-02 | Build systems (CMake, targets) | CPP-14 | All layers |
| 3 | SEC-03 | Headers & source file discipline | CPP-02a | All layers |
| 4 | SEC-04 | Translation units | CPP-02b | All layers |
| 5 | SEC-05 | Linking & symbol resolution | CPP-02c | All layers |
| 6 | SEC-06 | Memory layout (stack, heap, segments) | CPP-04a | All layers |
| 7 | SEC-07 | Variables, types, representations | CPP-03 | All layers |
| 8 | SEC-08 | Functions & calling conventions | CPP-06 | All layers |
| 9 | SEC-09 | Classes & object model | CPP-07a | All layers |
| 10 | SEC-10 | Object lifetimes & RAII | CPP-04b | All layers |
| 11 | SEC-11 | STL foundations | CPP-09 | All layers, CP† |
| 12 | SEC-12 | Complexity analysis (practical) | DSA-01 | All layers, CP† |

† Lab = SPSystem observation exercises (not mastery). ‡ OSS = fmt, CMake examples. CP = implementation fluency drills.

**Phase A1 exit exam:** FE-A1 — supervised multi-file build + memory diagram + complexity justification.  
**Exit artifact:** CMake project (3+ TUs); SPSystem build graph explained from memory.

---

## Track B Phase 1 — Reasoning Foundations (parallel)

**Purpose:** Deepen understanding of what you are already building. Does **not** block Track A.

| Order | ID | Title | Maps to | Unlock after |
|-------|-----|-------|---------|--------------|
| 1 | CST-01 | What is computation? | F-01 | SEC-03 |
| 2 | CST-02 | Information & encoding | F-02 | SEC-07 |
| 3 | CST-03 | Logic, predicates, invariants | F-03 | SEC-09 |
| 4 | CST-04 | Abstraction & decomposition (theory) | F-04 | CST-03 |
| 5 | CST-05 | Induction & proof basics | F-03+ | SEC-12 |
| 6 | CST-06 | Requirements → specification | F-07 | CST-03 |
| 7 | CST-07 | Testing theory & oracles | F-08 | DBG-01 |
| 8 | CST-08 | Security & trust models | F-10 | FS-02 |

**Phase B1 exit exam:** FE-B1 — specification + invariants for a management domain.  
Topics F-05, F-06, F-09 fold into merge-phase modules and CST cross-links.

---

## Section 01 — Foundations (Track B)

Renamed operationally to **Computer Science Theory — Reasoning**.  
Topics F-01–F-10 map to CST-01–CST-08; see Track B table above.  
**No longer the program entry point.**

---

## Section 02 — C++ Core (Track A + post-merge)

**Phase A1:** SEC-01–SEC-11 (see above).  
**Post-merge completion:**

| Unit | Topic ID | Title |
|------|----------|-------|
| 02.05 | CPP-05 | Pointers, references, const correctness |
| 02.08 | CPP-08 | Templates (intro) & generic programming |
| 02.10 | CPP-10 | STL algorithms, functors, lambdas |
| 02.11 | CPP-11 | Streams, I/O, formatting |
| 02.12 | CPP-12 | Error handling: exceptions vs error codes |
| 02.13 | CPP-13 | Move semantics & value categories |
| 02.15 | CPP-15 | Undefined behavior & sanitizer tooling |

**Full section exit:** FE-02 (after merge + remaining CPP topics).

---

## Section 03 — Data Structures & Algorithm Analysis

**Purpose:** Select and justify structures for real systems.

| Unit | Topic ID | Title |
|------|----------|-------|
| 03.01 | DSA-01 | Asymptotic analysis & amortization |
| 03.02 | DSA-02 | Arrays, dynamic arrays, strings |
| 03.03 | DSA-03 | Linked lists & comparison to arrays |
| 03.04 | DSA-04 | Stacks, queues, deques |
| 03.05 | DSA-05 | Hash tables — design & collision |
| 03.06 | DSA-06 | Binary search trees |
| 03.07 | DSA-07 | Balanced trees (AVL, RB intro) |
| 03.08 | DSA-08 | Heaps & priority queues |
| 03.09 | DSA-09 | Graphs — representations |
| 03.10 | DSA-10 | Union-Find (DSU) |
| 03.11 | DSA-11 | Tries & string indexes |
| 03.12 | DSA-12 | Spatial & multi-level indexes |
| 03.13 | DSA-13 | Persistent & external memory structures |
| 03.14 | DSA-14 | Choosing structures for domain systems |

**Exit artifact:** Decision matrix: structure choice for 10 operations across 5 domain systems.

---

## Section 04 — Object-Oriented Design

| Unit | Topic ID | Title |
|------|----------|-------|
| 04.01 | OOP-01 | Objects, state, behavior, messages |
| 04.02 | OOP-02 | Encapsulation & invariants |
| 04.03 | OOP-03 | Composition vs inheritance |
| 04.04 | OOP-04 | Polymorphism & dynamic dispatch |
| 04.05 | OOP-05 | Abstract interfaces & pure virtual |
| 04.06 | OOP-06 | SOLID principles (applied) |
| 04.07 | OOP-07 | Domain modeling & ubiquitous language |
| 04.08 | OOP-08 | Aggregates, entities, value objects |
| 04.09 | OOP-09 | Anti-patterns & god objects |
| 04.10 | OOP-10 | OOP in embedded & resource limits |

---

## Section 05 — Design Patterns

| Unit | Topic ID | Title |
|------|----------|-------|
| 05.01 | PAT-01 | Pattern catalog mindset |
| 05.02 | PAT-02 | Strategy, State |
| 05.03 | PAT-03 | Observer, Mediator |
| 05.04 | PAT-04 | Factory Method, Abstract Factory |
| 05.05 | PAT-05 | Singleton (and why to avoid) |
| 05.06 | PAT-06 | Adapter, Facade, Decorator |
| 05.07 | PAT-07 | Command, Memento |
| 05.08 | PAT-08 | Template Method, Iterator |
| 05.09 | PAT-09 | Repository & Unit of Work |
| 05.10 | PAT-10 | When NOT to use patterns |

---

## Section 06 — Software Architecture

| Unit | Topic ID | Title |
|------|----------|-------|
| 06.01 | ARCH-01 | Architecture vs design |
| 06.02 | ARCH-02 | Layered & hexagonal architecture |
| 06.03 | ARCH-03 | MVC, MVP, MVVM for console/GUI |
| 06.04 | ARCH-04 | Modular monolith |
| 06.05 | ARCH-05 | Microservices & bounded contexts |
| 06.06 | ARCH-06 | Event-driven & message queues |
| 06.07 | ARCH-07 | CQRS & read models |
| 06.08 | ARCH-08 | API design principles |
| 06.09 | ARCH-09 | Scalability, availability, CAP intro |
| 06.10 | ARCH-10 | Architecture documentation (C4, ADRs) |

---

## Section 07 — Operating Systems

| Unit | Topic ID | Title |
|------|----------|-------|
| 07.01 | OS-01 | OS role & system call interface |
| 07.02 | OS-02 | Processes vs threads |
| 07.03 | OS-03 | Scheduling |
| 07.04 | OS-04 | Virtual memory & paging |
| 07.05 | OS-05 | Synchronization: mutex, semaphore, CV |
| 07.06 | OS-06 | Deadlock & starvation |
| 07.07 | OS-07 | IPC: pipes, shared memory, sockets |
| 07.08 | OS-08 | File descriptors & I/O model |
| 07.09 | OS-09 | Signals & process lifecycle |
| 07.10 | OS-10 | Writing OS utilities (clone of wc, cat, shell) |

---

## Section 08 — Algorithms

| Unit | Topic ID | Title |
|------|----------|-------|
| 08.01 | ALG-01 | Sorting families & stability |
| 08.02 | ALG-02 | Binary search & variants |
| 08.03 | ALG-03 | Divide & conquer |
| 08.04 | ALG-04 | Greedy & exchange arguments |
| 08.05 | ALG-05 | Dynamic programming |
| 08.06 | ALG-06 | Graph traversal (BFS, DFS) |
| 08.07 | ALG-07 | Shortest paths |
| 08.08 | ALG-08 | Minimum spanning trees |
| 08.09 | ALG-09 | Topological sort |
| 08.10 | ALG-10 | String algorithms (KMP, hashing) |
| 08.11 | ALG-11 | Computational geometry intro |
| 08.12 | ALG-12 | NP-completeness intuition |

---

## Section 09 — Competitive Programming

Parallel track — see `09_Competitive_Programming/ROADMAP.md`.

---

## Section 10 — Debugging

| Unit | Topic ID | Title |
|------|----------|-------|
| 10.01 | DBG-01 | Scientific debugging method |
| 10.02 | DBG-02 | GDB / LLDB / Visual Studio debugger |
| 10.03 | DBG-03 | Memory debuggers (ASan, Valgrind) |
| 10.04 | DBG-04 | Logging & tracing |
| 10.05 | DBG-05 | Regression tests as debug artifacts |
| 10.06 | DBG-06 | Debugging concurrent code |
| 10.07 | DBG-07 | Postmortem & core dump analysis |

---

## Section 11 — File Systems & Persistence

| Unit | Topic ID | Title |
|------|----------|-------|
| 11.01 | FS-01 | Files, paths, permissions |
| 11.02 | FS-02 | Serialization formats (text, binary) |
| 11.03 | FS-03 | Schema evolution & migration |
| 11.04 | FS-04 | Journaling & crash recovery |
| 11.05 | FS-05 | Memory-mapped I/O |
| 11.06 | FS-06 | Embedded persistence constraints |
| 11.07 | FS-07 | Log-structured storage intro |

---

## Section 12 — Networking

| Unit | Topic ID | Title |
|------|----------|-------|
| 12.01 | NET-01 | OSI/TCP-IP mental model |
| 12.02 | NET-02 | Sockets API |
| 12.03 | NET-03 | TCP vs UDP |
| 12.04 | NET-04 | HTTP/REST client-server |
| 12.05 | NET-05 | Serialization over wire (JSON, Protobuf) |
| 12.06 | NET-06 | Concurrency models for servers |
| 12.07 | NET-07 | Network management systems architecture |
| 12.08 | NET-08 | Security: TLS intro, threat model |

---

## Section 13 — Databases

| Unit | Topic ID | Title |
|------|----------|-------|
| 13.01 | DB-01 | Relational model & algebra |
| 13.02 | DB-02 | SQL CRUD & joins |
| 13.03 | DB-03 | Indexes & B-trees |
| 13.04 | DB-04 | Transactions & ACID |
| 13.05 | DB-05 | Normalization |
| 13.06 | DB-06 | Query planning intuition |
| 13.07 | DB-07 | Embedded DB (SQLite) |
| 13.08 | DB-08 | Building a KV store (project tie-in) |

---

## Section 14 — Project Laboratories

Applied domain practice — see `14_Project_Laboratories/LABORATORY_ROADMAP.md`.

| Lab ID | Domain | Curriculum prerequisites |
|--------|--------|--------------------------|
| LAB-01 | Parking Management | 02, 03, 04, 05 (Facade), 11 |
| LAB-02 | Inventory Management | + 03.14, 13 |
| LAB-03 | Library Management | + 08 (search/sort) |
| LAB-04 | School Management | + 06, 13 |
| LAB-05 | Hospital Management | + 07 (scheduling), 12 |
| LAB-06 | Banking System | + 13 (transactions), 12 (security) |
| LAB-07 | Embedded Sensor Monitor | + 07, 11.06 |
| LAB-08 | Network Monitor | + 12, 07 |
| LAB-09 | OS Utility Suite | + 07.10 |
| LAB-10 | Custom Domain (student choice) | Advisor approval |

**SPSystem** maps to **LAB-01** only.

---

## Section 15 — Open Source Studies

See `15_Open_Source_Studies/ROADMAP.md`.

---

## Section 16 — Research

| Unit | Topic ID | Title |
|------|----------|-------|
| 16.01 | RES-01 | Reading CS papers |
| 16.02 | RES-02 | C++ standard & ABI papers |
| 16.03 | RES-03 | Classic systems papers (Unix, LSM) |
| 16.04 | RES-04 | Writing technical reports |

---

## Section 17 — Interview Preparation

Consolidated banks — populated as topics complete. Mock oral exams scheduled at milestones.

---

## Section 18 — Examinations

Formal written & oral exams per phase — see `MASTERY_REQUIREMENTS.md`.

---

## Section 19 — Capstones

| Capstone | Description | Prerequisites |
|----------|-------------|---------------|
| CAP-01 | Multi-domain management platform (monolith) | Phases I–III |
| CAP-02 | Networked service with DB & auth | Phase IV |
| CAP-03 | Embedded + host tooling system | 07, 11.06, LAB-07 |
| CAP-04 | Student-designed enterprise system | All core sections |
| CAP-05 | 48-hour from-scratch challenge | Graduation prep |

---

## Section 20 — Rebuild From Scratch

Memory reconstruction challenges — see `20_Rebuild_From_Scratch/ROADMAP.md`.

---

## Recommended Study Order (first year, revised)

```
Track A (primary):
  SEC-01 → SEC-02 → … → SEC-12
  DBG-01 (parallel week 6+)
  → [Merge gate]
  → CPP-05,10,11,12,13,15 → OOP-01–06 → DSA-02–06
  → PAT-01–06 → FS-01–03 → LAB-01 gate

Track B (parallel, 3–5 hrs/week):
  [after SEC-03] CST-01 → [after SEC-07] CST-02
  → [after SEC-09] CST-03, CST-04 → [after SEC-12] CST-05, CST-06
  → [after DBG-01] CST-07

CP: unlocks CP-T0 after SEC-12 (3 hrs/week)

SPSystem: observation exercises SEC-05+; case study DSA-05+; LAB-01 rebuild gate only
```

## Topic Folder Convention

Each topic lives at:

```
Book/<Section>/topics/<TOPIC_ID>_<slug>/
├── README.md              # Index + mastery gate status
├── 01_lesson_notes.md
├── 02_deep_explanations.md
├── ... (27 artifact files or grouped)
└── mastery_gate.md
```

*Lessons are generated on demand after gates — folder stubs created progressively.*

---

*Roadmap version: 1.0*
