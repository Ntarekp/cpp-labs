# SEC-01 Mental Models

## Model 1 — The publishing house

| Stage | Publishing | C++ build |
|-------|------------|-----------|
| Draft chapters | `.cpp` files | Source |
| Copy-edit merge includes | Preprocessor | `#include` |
| Typeset chapter | Compiler | Object file |
| Bind book + index | Linker | Executable |
| Reader opens book | Loader | Process |
| Read chapter 1 | `main()` | Program start |

## Model 2 — Phone directory

- **Compiler** = each person writes their own page (TU) listing names they **know** and names they **need**.
- **Linker** = central office matching "need John" to "John lives at address X".

## Model 3 — Jigsaw puzzle

- Each object file = one puzzle piece with **tabs and blanks** (symbols defined / undefined).
- Linker snaps pieces together into complete picture (executable).

## Model 4 — Local vs global knowledge

```
Compiler: "I see a call to foo(). Someone must provide foo(). Not my job."
Linker:   "I find foo() in helper.o. Patch call site. Done."
```

## Model 5 — Three clocks

| Clock | When |
|-------|------|
| **Compile time** | Types, templates, constexpr |
| **Link time** | Symbol resolution |
| **Run time** | `main()`, I/O, user input |

Put errors on the right clock — debugging starts with classification.

## Key sentences (memorize)

1. **One `.cpp` → one object file** (usually).
2. **Headers are not compiled alone** — they are pasted into TUs.
3. **Linker errors never fix with syntax changes** if the syntax was already valid.
4. **`main` is where your story starts, not where the OS starts.**
