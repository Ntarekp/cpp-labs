# SEC-01 Historical Context

## Before compilers
1940s–50s: machine code, assembly — one monolithic program, no link stage.

## Separate compilation (1960s–70s)
Unix and PL/I introduced **compile modules separately, link later** — enabled large teams and libraries.

## Static linking era
1980s: all code in one executable — simple deployment, large binaries.

## Shared libraries (1980s+)
`.so` / `.dll` — link at load or run; dynamic linker participates (extension of SEC-01 load stage).

## C++ complexity (1990s+)
Templates in headers → compile time explosion — same pipeline, new bottleneck.

## Modern (2000s+)
- **Clang/LLVM** — modular compiler architecture
- **LTO** — optimizer sees whole program at link time
- **C++ modules** — reduce textual `#include` (SEC-03 forward)

## Lesson
Pipeline shape is **stable for 50 years**; flags and tools evolve. Master stages, not one vendor's flags.
