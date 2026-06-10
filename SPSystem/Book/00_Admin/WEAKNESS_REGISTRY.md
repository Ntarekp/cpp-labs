# Weakness Registry

> Active and resolved weakness tags. Drives remedial exercise generation.

---

## Weakness Taxonomy

| Tag | Domain | Example signal |
|-----|--------|----------------|
| `W-LOGIC` | Foundations | Cannot write invariants |
| `W-PROOF` | Foundations | Induction errors |
| `W-SPEC` | Foundations | Vague requirements |
| `W-COMPILE` | C++ | Confuses compile vs link errors |
| `W-LINK` | C++ | ODR violations |
| `W-MEMORY` | C++ | Stack/heap confusion, leaks |
| `W-POINTER` | C++ | Dangling references |
| `W-CONST` | C++ | const-correctness gaps |
| `W-MOVE` | C++ | Copy when move intended |
| `W-STL` | C++ | Iterator invalidation |
| `W-COMPLEX` | DSA | Wrong Big-O classification |
| `W-PROOF-DS` | DSA | Cannot prove amortized bounds |
| `W-HASH` | DSA | Collision handling gaps |
| `W-TREE` | DSA | BST delete cases |
| `W-GRAPH` | DSA | BFS/DFS state errors |
| `W-OOP-ENCAP` | OOP | Leaky abstractions |
| `W-OOP-LSP` | OOP | Liskov violations |
| `W-PATTERN` | Patterns | Pattern over-application |
| `W-ARCH` | Architecture | God modules |
| `W-OS-PROC` | OS | fork/exec confusion |
| `W-OS-SYNC` | OS | Race conditions |
| `W-OS-VM` | OS | Virtual memory model gaps |
| `W-NET` | Networking | TCP state machine |
| `W-DB` | Databases | Normalization errors |
| `W-FS` | File systems | Schema migration |
| `W-DEBUG` | Debugging | Random-change debugging |
| `W-CP-EDGE` | CP | Missing edge cases |
| `W-CP-TLE` | CP | Complexity underestimation |
| `W-ORAL` | Meta | Cannot explain under pressure |
| `W-REBUILD` | Meta | Cannot reconstruct from memory |

---

## Active Weaknesses

| Tag | Detected | Source | Severity | Remedial track | Status |
|-----|----------|--------|----------|----------------|--------|
| — | — | — | — | — | — |

*No weaknesses detected yet — baseline assessment pending.*

---

## Resolved Weaknesses

| Tag | Resolved | Evidence |
|-----|----------|----------|
| — | — | — |

---

## Remedial Track Templates

### W-MEMORY
1. Draw stack frames for 3 nested function calls
2. Identify leak in provided snippet; fix with RAII
3. Valgrind/ASan on personal exercise
4. Oral: explain object lifetime of local `std::vector`

### W-HASH
1. Implement chaining hash map from scratch
2. Explain birthday paradox relevance
3. Choose hash for `std::string` keys — defend

### W-COMPILE + W-LINK
1. Cause 3 errors (preprocess, compile, link); document
2. Rebuild build pipeline diagram from memory
3. Fix ODR violation in seed project

### W-LOGIC
1. Write 5 invariants for chosen domain
2. Find invariant violation in buggy spec
3. F-03 induction exercises (set of 5)

### W-REBUILD
1. Daily 15-min micro-rebuild drills
2. Reduce reference time on RFS-T1a by 25%
3. Paper-only design before code

---

## Severity Levels

| Level | Action |
|-------|--------|
| L1 — Minor | 3 remedial exercises; retry gate |
| L2 — Moderate | 10-hour remedial block; topic freeze |
| L3 — Critical | Section review; instructor conference |

---

## Review Schedule

- After every failed gate: add/update tags
- Monthly: review active weaknesses
- After FE exam: comprehensive audit

---

*Weakness registry version: 1.0*
