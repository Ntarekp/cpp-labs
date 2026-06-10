# Graduation Requirements

> **Graduate definition:** Can sit at a computer with only a compiler and problem statement, without internet, and design + implement professional software from first principles.

---

## Requirement Categories

| Category | ID | Requirement |
|----------|-----|-------------|
| Examinations | GR-E | All foundation exit exams passed |
| Laboratories | GR-L | Laboratory portfolio complete |
| Systems | GR-S | Systems & networking exams passed |
| Synthesis | GR-C | Capstone portfolio complete |
| Speed | GR-P | Competitive programming minimum |
| Memory | GR-R | Rebuild tier minimum |
| Industry | GR-I | Interview & OSS minimum |
| Final | GR-F | Graduation oral + 48-hour challenge |

---

## GR-E — Foundation Exit Examinations

All must be passed with scores meeting `MASTERY_REQUIREMENTS.md`:

| Exam | Section | Minimum Score |
|------|---------|---------------|
| FE-A1 | Construction (Track A Phase 1) | 80% |
| FE-B1 | Theory (Track B Phase 1) | 75% |
| FE-02 | C++ Core | 80% |
| FE-03 | DSA | 80% |
| FE-04 | OOP | 75% |
| FE-05 | Design Patterns | 75% |
| FE-06 | Architecture | 80% |
| FE-07 | Operating Systems | 80% |
| FE-08 | Algorithms | 75% (4/6 problems) |
| FE-10 | Debugging | 100% (3/3 bugs) |
| FE-11 | File Systems | 75% |
| FE-12 | Networking | 75% |
| FE-13 | Databases | 75% |

**Status:** Track in `PROGRESS_TRACKER.md`

---

## GR-L — Laboratory Portfolio

### Minimum: 6 laboratories **mastered** (not "built once")

| Requirement | Detail |
|-------------|--------|
| Core labs | ≥3 from LAB-01 through LAB-04 |
| Advanced labs | ≥1 from LAB-05 through LAB-08 |
| Systems lab | LAB-09 (OS Utilities) **or** LAB-08 (Network Mgmt) |
| Rebuild | Each lab: timed rebuild passed |
| SPSystem | May count toward LAB-01 **only** if LAB-01 rebuild gate passed independently |

### Laboratory evidence per lab

- [ ] Design document (pre-code)
- [ ] Implementation
- [ ] Test plan executed
- [ ] Rebuild-from-memory attempt (logged)
- [ ] 15-min oral change-request defense
- [ ] Retrospective (tradeoffs)

---

## GR-S — Systems Depth

Demonstrate **all**:

1. Multi-threaded program with shared state (no data races)
2. Client-server program over TCP
3. Program using file persistence with crash recovery
4. Program using SQL (SQLite minimum)
5. One OS utility matching LAB-09 quality

---

## GR-C — Capstone Portfolio

| Capstone | Required |
|----------|----------|
| CAP-01 Multi-domain monolith | Yes |
| CAP-02 Networked service + DB | Yes |
| CAP-03 **or** CAP-04 | One of: embedded system **or** student enterprise design |
| CAP-05 48-hour from-scratch | Yes (final) |

### CAP-05 — Final Graduation Challenge

**Conditions:**
- Sealed problem statement (instructor-assigned domain)
- 48 consecutive hours
- Machine: compiler, standard library, offline standard docs only
- No internet, no AI, no prior project code
- Deliverables: working binary, design doc, test evidence

**Domains may include:** Parking, inventory, hospital scheduling, library, banking, school admin — or composite.

**Pass:**
- Functional requirements ≥90%
- Oral defense of every architectural choice
- No critical security flaws
- Memory clean (instructor runs ASan/Valgrind)

---

## GR-P — Competitive Programming Minimum

| Metric | Minimum |
|--------|---------|
| Total logged solves | 200 |
| CP tier | CP-T5 passed |
| Virtual contest | Top 50% Div 2 equivalent |
| Contest formats | ≥2 of: DP, graphs, greedy, data structures |

---

## GR-R — Rebuild From Scratch Minimum

| Tier | Challenge | Required |
|------|-----------|----------|
| RFS-T1 | `vector` + `hash map` | Yes |
| RFS-T2 | Serialization framework | Yes |
| RFS-T3 | Thread pool **or** custom allocator | Yes |
| RFS-T4 | HTTP subset **or** mini-DB layer | Yes |
| RFS-T5 | Full management system | CAP-05 |

---

## GR-I — Industry Readiness

| Requirement | Minimum |
|-------------|---------|
| Mock technical interviews | 10 (≥7 pass) |
| OSS studies with reports | 5 |
| Research deliverable | 1 literature review |
| Debugging exam | FE-10 passed |

---

## GR-F — Graduation Oral

**Duration:** 90 minutes

| Segment | Time | Content |
|---------|------|---------|
| Theory | 30 min | Cross-section questions (no notes) |
| Design | 30 min | Whiteboard novel system from prompt |
| Code reading | 15 min | Explain provided OSS snippet |
| Ethics & security | 15 min | Scenario-based |

**Panel:** Instructor roles rotate (professor, architect, interviewer).

**Pass:** Unanimous "professional readiness" or majority with remedial plan (max one remedial area).

---

## Graduation Checklist

```
[ ] GR-E  — All 12 foundation exams passed
[ ] GR-L  — 6 labs mastered with evidence
[ ] GR-S  — 5 systems demonstrations
[ ] GR-C  — CAP-01, CAP-02, CAP-03/04, CAP-05
[ ] GR-P  — 200 solves, CP-T5, virtual contest
[ ] GR-R  — RFS-T1 through T4
[ ] GR-I  — 10 mocks, 5 OSS, 1 research
[ ] GR-F  — Oral passed
```

Upon completion: entry in `MASTERY_LOG.md` with date and summary.

---

## Honors Distinction (optional)

| Criterion | Threshold |
|-----------|-----------|
| All FE exams | ≥90% average |
| Labs mastered | 8+ |
| CP solves | 500+ |
| CP-T7 passed | Yes |
| CAP-04 (self-designed enterprise) | Yes |
| OSS kernel or DB internals study | 1 |

---

## Failure & Appeal

- CAP-05 fail: 90-day remediation, one retry
- Oral fail: 30-day remediation, one retry
- Maximum program duration: none (self-paced)
- Recommended re-enrollment in section if FE exam failed 3×

---

*Graduation requirements version: 1.0*
