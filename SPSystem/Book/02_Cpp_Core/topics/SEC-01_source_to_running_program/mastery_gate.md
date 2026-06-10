# SEC-01 Mastery Gate

**Status:** `OPEN` — submit evidence to instructor for grading.

## Requirements (all required)

| ID | Requirement | Evidence |
|----|-------------|----------|
| G1 | Explain-back B→I→A→P | Written or oral recording |
| G2 | Predict: 5 scenarios | ≥4/5 correct without running |
| G3 | Defend: "Why separate compilation?" | 5-min oral |
| G4 | Exercises | 100% beginner + intermediate; ≥1 advanced |
| G5 | RFS-SEC-01 rebuild | [rebuild_challenge.md](rebuild_challenge.md) |
| G6 | Flashcards oral | ≥13/15 from [11_flashcards.md](11_flashcards.md) |
| G7 | Common mistakes | Identify 2/3 in [20_common_mistakes.md](20_common_mistakes.md) quiz |

## G2 prediction scenarios

1. `g++ -c main.cpp` when `main` calls external `foo()` — success or fail? Stage?
2. `undefined reference to 'bar'` — compile or link?
3. Missing `#include <vector>` — which stage fails?
4. Executable runs, prints garbage — which stage is blame?
5. Two `.cpp` define same non-inline `int x` — which stage fails?

<details>
<summary>Instructor answers (do not open before attempt)</summary>

1. Compile succeeds; link fails if `foo` undefined
2. Link
3. Compile
4. Run-time (logic) — compile/link succeeded
5. Link (multiple definition)
</details>

## G4 minimum labs

- Complete [laboratory.md](laboratory.md) SEC-01-L1 and L2

## Pass → unlock

- **SEC-02** Build systems
- **DBG-01** soft parallel
- Progress logged in `00_Admin/MASTERY_LOG.md`

## Fail → remedial

Tags: `W-COMPILE`, `W-LINK` — see `WEAKNESS_REGISTRY.md`
