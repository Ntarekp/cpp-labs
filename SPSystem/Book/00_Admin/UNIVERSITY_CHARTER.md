# University Charter

## Mission

Produce a software engineer capable of sitting at a computer with **only a compiler and a problem statement** — without internet access — and designing, implementing, testing, and reasoning about **professional software from first principles**.

**Not a traditional CS degree.** Practical software engineering mastery **combined with** deep computer science understanding.

## Graduate Profile

A graduate of this curriculum can:

1. Decompose an unfamiliar problem into modules with clear responsibilities and invariants.
2. Select data structures and algorithms with justified complexity and memory tradeoffs.
3. Implement systems in C++ (primary language) with correct memory, I/O, and error semantics.
4. Design architectures for console apps, services, embedded constraints, and networked systems.
5. Debug systematically from symptoms to root cause.
6. Rebuild core subsystems from memory after studying them.
7. Pass technical interviews and formal examinations at senior-student / junior-professional depth.
8. Read and learn from open-source codebases without tutorial dependency.

## Pedagogical Contract

### Teaching Layers (every topic)

| Layer | Standard |
|-------|----------|
| Beginner | Intuition, analogy, problem-before-solution |
| Intermediate | Mechanisms, invariants, typical usage |
| Advanced | Edge cases, performance, failure modes |
| Professional | Team practice, operations, evolution, security |

### Mastery Gate (mandatory before advancement)

For each topic, the learner must demonstrate:

1. **Explain-back** — all four layers in own words
2. **Predict** — behavior without executing code
3. **Defend** — design choice under criticism (tradeoffs)
4. **Rebuild** — reconstruct artifact from memory (see `20_Rebuild_From_Scratch/`)
5. **Apply** — complete assigned exercises without copying solutions

Partial understanding triggers **remedial tracks** (see `WEAKNESS_REGISTRY.md`). No silent advancement.

### Dual-Track Model

| Track | Role |
|-------|------|
| **A — Software Engineering Core** | Primary path — construction, design, systems |
| **B — Computer Science Theory** | Enrichment — computation, proof, formal models |

Tracks merge after Phase A1 (SEC-01–12) + Phase B1 core (CST-01, 03, 05). See `LEARNING_TRACKS.md`.

**Program entry:** SEC-01 (not abstract foundations).

### Per-Topic Learning Layers (required)

| Layer | Required |
|-------|----------|
| Theory | Always |
| Practice | Always |
| Laboratory | When domain-applicable |
| Rebuild-from-memory | Always |
| Examination preparation | Always |
| Interview preparation | Always |
| Competitive programming relevance | If applicable |
| Open source relevance | If applicable |

### Per-Topic Deliverables (27 artifacts)

Every topic in the repository must eventually contain:

1. Lesson Notes
2. Deep Explanations
3. Diagrams
4. Mental Models
5. Beginner Exercises
6. Intermediate Exercises
7. Advanced Exercises
8. Assignments
9. Mini Projects
10. Capstone Projects
11. Interview Questions
12. Examination Questions
13. Flashcards
14. Research Topics
15. External References
16. Textbook References
17. Documentation References
18. Video Recommendations
19. Competitive Programming Problems
20. Open Source Code References
21. Industry Case Studies
22. Advanced Challenges
23. Rebuild-From-Memory Challenges
24. Alternative Implementations
25. Common Mistakes
26. Historical Context
27. Professional Industry Practices

Plus meta sections:

- Why this topic exists
- What problems it solves
- Historical evolution
- Professional usage
- Interview appearance
- Examination appearance
- Prerequisites (links to prior topics)
- Forward links (future topics that depend on this)

## Laboratory vs Curriculum

| Role | Description |
|------|-------------|
| **Curriculum** (`Book/01`–`13`, `17`–`20`) | Universal knowledge — applies to any future system |
| **Laboratory** (`Book/14_Project_Laboratories`) | Applied practice — domain-specific implementations |
| **SPSystem** | One laboratory project (parking management). Illustrates concepts; **does not prove mastery** of those concepts |

Domain laboratories include (non-exhaustive): Parking, Inventory, Hospital, Library, Banking, School, Embedded, Network Management, OS Utilities.

## Roles of the Instructor

| Role | Responsibility |
|------|----------------|
| University Professor | Structure, rigor, examinations, prerequisites |
| Software Architect | System decomposition, scalability, evolution |
| Senior C++ Engineer | Language, memory, build, idioms |
| DSA Instructor | Structures, complexity, correctness |
| Competitive Programming Coach | Contest techniques, speed, proof |
| Technical Interviewer | Oral defense, design questions |
| Systems Programming Mentor | OS, networking, low-level behavior |
| Research Supervisor | Papers, standards, primary sources |

## Repository Layout

```
Book/
├── 00_Admin/           Governance, tracking, roadmaps
├── 01_Foundations/     Computation & reasoning
├── 02_Cpp_Core/        C++ language & toolchain
├── 03_DSA/             Data structures & algorithmic analysis
├── 04_OOP/             Object-oriented design
├── 05_Design_Patterns/ Reusable collaboration structures
├── 06_Software_Architecture/ Large-scale structure
├── 07_Operating_Systems/ Processes, memory, syscalls
├── 08_Algorithms/      Classic algorithm families (deep)
├── 09_Competitive_Programming/ Contest preparation
├── 10_Debugging/       Methodology & tools
├── 11_File_Systems/    Persistence & formats
├── 12_Networking/      Protocols & distributed communication
├── 13_Databases/       Storage engines & query logic
├── 14_Project_Laboratories/ Domain projects
├── 15_Open_Source_Studies/ Codebase reading curriculum
├── 16_Research/        Papers & standards
├── 17_Interview_Preparation/ Consolidated interview bank
├── 18_Examinations/    Formal exam banks
├── 19_Capstones/       Integrative mega-projects
├── 20_Rebuild_From_Scratch/ Memory reconstruction challenges
└── 22_System_Design_Challenges/ Parallel design track (SEC reinforcement)
```

**Curriculum architecture:** Frozen at v2.0 + Section 22. No further structural changes unless explicitly requested.

## Document Index (foundational)

| Document | Path |
|----------|------|
| Curriculum Roadmap | `00_Admin/CURRICULUM_ROADMAP.md` |
| Learning Tracks | `00_Admin/LEARNING_TRACKS.md` |
| Dependency Graph | `00_Admin/DEPENDENCY_GRAPH.md` |
| Topic Template | `00_Admin/TOPIC_TEMPLATE.md` |
| Mastery Requirements | `00_Admin/MASTERY_REQUIREMENTS.md` |
| Study Hours | `00_Admin/STUDY_HOURS.md` |
| Milestones | `00_Admin/MILESTONES.md` |
| Graduation Requirements | `00_Admin/GRADUATION_REQUIREMENTS.md` |
| Progress Tracker | `00_Admin/PROGRESS_TRACKER.md` |
| Mastery Log | `00_Admin/MASTERY_LOG.md` |
| Weakness Registry | `00_Admin/WEAKNESS_REGISTRY.md` |
| Laboratory Roadmap | `14_Project_Laboratories/LABORATORY_ROADMAP.md` |
| Open Source Roadmap | `15_Open_Source_Studies/ROADMAP.md` |
| Competitive Programming Roadmap | `09_Competitive_Programming/ROADMAP.md` |
| Rebuild Roadmap | `20_Rebuild_From_Scratch/ROADMAP.md` |

## Operating Mode

1. Foundational documents are approved and versioned in `00_Admin/`.
2. Lessons are generated **topic-by-topic** only after mastery gates.
3. The instructor continuously updates trackers after each gate attempt.
4. SPSystem is referenced only when it **illuminates** a universal concept.

---

*Charter version: 2.0 — Dual-track, construction-first.*
