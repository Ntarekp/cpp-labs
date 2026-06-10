# SEC-01 Laboratory

> **No SPSystem in this topic.** Generic multi-file lab only.  
> SPSystem observation unlocks at **SEC-05**. SDC-01 unlocks at **SEC-05**.

## Lab SEC-01-L1 — Minimal two-module program

### Setup
Create empty folder `sec01_lab/` with:

**math.h**
```cpp
#pragma once
int add(int a, int b);
```

**math.cpp**
```cpp
#include "math.h"
int add(int a, int b) { return a + b; }
```

**main.cpp**
```cpp
#include <iostream>
#include "math.h"
int main() {
    std::cout << add(2, 3) << '\n';
    return 0;
}
```

### Tasks
1. Build with three explicit commands (`-c`, `-c`, link).
2. List every file on disk after each step.
3. Delete `math.o` and attempt link — record error.
4. Rebuild; run executable; note exit code (`echo $?` or `echo %ERRORLEVEL%`).

### Deliverable
One-page lab report: pipeline stages observed, errors classified.

## Lab SEC-01-L2 — Error diary

Cause **one error per stage** (preprocess, compile, link, runtime). Table:

| Stage | How caused | Message | Fix |

## Lab SEC-01-L3 — Design connection (SDC preview)

Without implementing a parking system: sketch on paper how **three .cpp files** might correspond to **three modules** in any management system (UI, logic, storage). Label which stages touch which files.

*Full system design: SDC-01 after SEC-05.*

## Laboratory rubric

| Criterion | Pass |
|-----------|------|
| Separate compile + link demonstrated | Yes |
| ≥3 errors classified correctly | Yes |
| Pipeline diagram in report | Hand-drawn OK |
| No copy-paste of solutions without explanation | Yes |
