# SEC-01 Theory

## Beginner

You write **source code** (`.cpp` files). The computer runs **machine code** (bytes the CPU understands). Between them is a **pipeline** of tools:

1. **Preprocessor** — text manipulation (`#include`)
2. **Compiler** — C++ → object file per source file
3. **Linker** — object files → one executable
4. **Loader** (OS) — executable → process in memory
5. **Runtime** — calls `main()`, your program runs

**Analogy:** Recipe (source) → printed chapters (object files) → bound book (executable) → reader opens book (loader) → story begins (`main`).

## Intermediate

Each `.cpp` file is a **translation unit (TU)** after preprocessing. The compiler processes TUs **independently** — it emits **object code** and a **symbol table** (names of functions/variables this TU defines or needs).

The **linker** is global: it resolves symbols across TUs ("`registerEntry` is defined in `ParkingSystem.cpp`") and produces a single **executable**.

**Key invariant:** Compilation is **local**; linking is **global**.

## Advanced

**Translation phases** (C++ standard, simplified): source → preprocessing → tokens → parsing → semantic analysis → code generation → linking.

**Symbols** have linkage: internal, external, no linkage. **Undefined reference** = linker cannot find definition. **Multiple definition** = ODR violation.

**Load:** ELF/PE loader maps segments (code, data, BSS) into virtual address space, sets up stack/heap, transfers control to `_start` → CRT → `main`.

## Professional

- **Incremental builds:** Only changed TUs recompile; linker always runs.
- **CI:** Hermetic builds pin compiler version; SEC-01 errors become merge blockers.
- **Debug vs release:** Same pipeline; different flags (`-g`, `-O2`) change object code, not pipeline shape.
- **Cross-compilation:** Same stages; different target triple.

## Why not start with "computation"?
Because you already have multi-file projects. Pipeline knowledge **unblocks daily work** immediately. Theory (Track B CST-01) connects later when you have seen real TUs.
