# SEC-01 — Source Code → Running Program

| Field | Value |
|-------|-------|
| **Track** | A — Software Engineering Core |
| **Section** | 02 C++ Core |
| **Maps to** | CPP-01 |
| **Status** | `IN_PROGRESS` |
| **Prerequisites** | None (program entry) |
| **Unlocks** | SEC-02, DBG-01 (soft) |
| **SDC** | SDC-01 unlocks after SEC-05 (not this topic) |
| **SPSystem** | No reference in this topic |

---

## Meta

### Why this topic exists
Humans write text; CPUs execute machine code. SEC-01 bridges that gap so multi-file projects are **predictable**, not magical.

### What problems it solves
- "It compiles on my machine" without understanding stages
- Linker errors that look like compiler errors
- Inability to reason about what `main()` running actually means

### Historical evolution
Assembly → compilers → separate compilation (1970s Unix) → linkers → modern toolchains (GCC, Clang, MSVC).

### Professional usage
CI pipelines, incremental builds, debug vs release, reproducible builds — all are SEC-01 at scale.

### Interview appearance
"Explain compile vs link," "What is a translation unit," "What happens when you run `./a.out`"

### Examination appearance
List pipeline stages; classify errors by stage; draw memory at program start.

### Prerequisites
None.

### Forward links
SEC-02 (build systems), SEC-03–05 (headers/TUs/linking detail), SEC-06 (memory layout at load), OS-01 (process model).

---

## Lesson index

| Layer / Artifact | File |
|------------------|------|
| Theory | [theory.md](theory.md) |
| Practice | [practice.md](practice.md) |
| Laboratory | [laboratory.md](laboratory.md) |
| Rebuild | [rebuild_challenge.md](rebuild_challenge.md) |
| Exam prep | [exam_prep.md](exam_prep.md) |
| Interview prep | [interview_prep.md](interview_prep.md) |
| CP | [cp_relevance.md](cp_relevance.md) |
| OSS | [oss_relevance.md](oss_relevance.md) |
| Lesson notes | [01_lesson_notes.md](01_lesson_notes.md) |
| Deep explanations | [02_deep_explanations.md](02_deep_explanations.md) |
| Diagrams | [03_diagrams.md](03_diagrams.md) |
| Mental models | [04_mental_models.md](04_mental_models.md) |
| Flashcards | [11_flashcards.md](11_flashcards.md) |
| References | [13_references.md](13_references.md) |
| Common mistakes | [20_common_mistakes.md](20_common_mistakes.md) |
| Mastery gate | [mastery_gate.md](mastery_gate.md) |

---

## Mastery gate (summary)

Pass all before SEC-02: see [mastery_gate.md](mastery_gate.md).
