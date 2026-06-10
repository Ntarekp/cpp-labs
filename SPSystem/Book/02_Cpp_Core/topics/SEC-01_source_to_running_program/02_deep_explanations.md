# SEC-01 Deep Explanations

## Execution trace: `g++ -std=c++17 -o app main.cpp helper.cpp`

### Step-by-step

1. **Driver invokes preprocessor** on `main.cpp` — pulls in headers textually.
2. **Compiler front-end** tokenizes, parses, builds AST for `main.cpp` TU.
3. **Semantic analysis** — types checked; `helper()` must be **declared** (from header).
4. **Code generation** — emits `main.o` with:
   - Machine code for `main`
   - **Undefined** symbol reference to `helper` (if defined in other TU)
   - Exported symbol `_main` or `main` per ABI
5. Repeat for `helper.cpp` → `helper.o` with definition of `helper`.
6. **Linker** reads `main.o`, `helper.o`, CRT startup (`crt0.o`, etc.), `libstdc++`.
7. Linker **resolves** `helper` reference in `main.o` to address in `helper.o`.
8. Linker writes `app` (ELF on Linux, PE on Windows).
9. You run `./app` — **shell asks OS** to create process.
10. **Loader** maps segments; **CRT** runs constructors, calls `main(argc, argv)`.

## What the object file contains

- **Machine code** for functions in this TU
- **Relocation entries** — "patch address of `helper` when linked"
- **Symbol table** — `T main`, `U helper` (T=text/defined, U=undefined)

Tools: `nm` (Unix), `dumpbin /symbols` (MSVC).

## Undefined reference — worked example

```cpp
// main.cpp
void foo();
int main() { foo(); return 0; }
```

Compile: `g++ -c main.cpp` → **success** (declaration enough for compile).

Link: `g++ main.o -o app` → **undefined reference to `foo()`** — linker stage.

## Why separate compilation scales

100 `.cpp` files: change one → recompile one TU + relink. Without separate compilation, entire program recompiled every edit.

## Runtime behavior of `return 0`

Exit code to OS (shell `$?`). CRT calls `exit()` which runs `atexit` handlers, flushes streams, terminates process.

## Security implication

Loader executes **your** machine code with process privileges. SEC-01 is the trust boundary: any compiled code runs.

## Performance implication

- **Compile time:** dominated by template-heavy headers (preview SEC-03)
- **Link time:** grows with symbol count — why forward declarations matter
- **Startup:** CRT + dynamic init before `main` — measurable in tiny programs
