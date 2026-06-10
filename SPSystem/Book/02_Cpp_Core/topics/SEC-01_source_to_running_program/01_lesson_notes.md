# SEC-01 Lesson Notes

## Learning objectives

After this topic you can:

1. Name and order the five stages: preprocess → compile → link → load → run
2. Distinguish compile-time vs link-time vs run-time errors
3. Explain why multi-file C++ needs a linker
4. Predict what `g++ -c file.cpp` produces vs `g++ -o app file.cpp`
5. Draw the pipeline from memory without notes

## Core vocabulary

| Term | Definition |
|------|------------|
| **Source file** | Human-written C++ (`.cpp`, headers) |
| **Translation unit** | One `.cpp` after `#include` expansion |
| **Object file** | Machine code + relocations + symbol table (`.o`, `.obj`) |
| **Symbol** | Named entity: function, global variable |
| **Linker** | Combines objects; resolves cross-file symbols |
| **Executable** | Linked program ready for OS loader |
| **Process** | Running instance of program in memory |
| **CRT** | C runtime startup code before `main()` |

## The five stages (detail)

### Stage 1 — Preprocessor
- Pure text: `#include`, `#define`, `#if`
- Not type-aware
- Output: single expanded TU fed to compiler

### Stage 2 — Compile (per TU)
- Input: one TU
- Output: object file
- Errors: syntax, types, undeclared identifiers in this TU

### Stage 3 — Link
- Input: all object files + libraries
- Output: executable
- Errors: undefined reference, multiple definition

### Stage 4 — Load (OS)
- Maps executable into address space
- Sets up stack, heap regions
- Jumps to entry point (not `main` directly — CRT first)

### Stage 5 — Run
- CRT initializes
- `main()` executes
- Process terminates with exit code

## Minimal commands (memorize)

```bash
# Preprocess only (inspect)
g++ -std=c++17 -E main.cpp -o main.i

# Compile to object (no link)
g++ -std=c++17 -c main.cpp -o main.o

# Link objects into executable
g++ -std=c++17 main.o other.o -o app

# Compile + link in one step (common)
g++ -std=c++17 main.cpp other.cpp -o app
```

## Syntax vs semantics vs execution (SEC-01 scope)

| | Meaning in SEC-01 |
|---|-------------------|
| **Syntax** | Valid C++ grammar — compiler stage |
| **Semantics** | Types, overload resolution — compiler stage |
| **Execution** | Machine instructions — after load, at runtime |

## Complexity (this topic)

Pipeline stages are **O(size of input)** per stage for one build. Incremental builds amortize to **O(changed TUs)** — why separate compilation exists.

## Memory (preview for SEC-06)

At load: code segment (read-only), data (initialized globals), BSS (zero-init), stack, heap — SEC-06 deepens this.
