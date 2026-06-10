# SEC-01 Practice

## Beginner exercises

### B1 — Stage naming
List the five stages from source to running program in order.

### B2 — Command mapping
What does each command produce?
```bash
g++ -E file.cpp
g++ -c file.cpp
g++ file.cpp -o app
```

### B3 — Error classification
Classify each as compile, link, or runtime:
- `expected ';' before '}'`
- `undefined reference to 'compute()'`
- `segmentation fault`

### B4 — Draw from memory
Draw the pipeline diagram (boxes + arrows only).

### B5 — Vocabulary
Define: translation unit, object file, symbol, linker.

## Intermediate exercises

### I1 — Two-file link
Create `main.cpp` calling `int add(int,int)` and `add.cpp` defining it. Build with separate `-c` and link steps. Document each artifact.

### I2 — Deliberate linker error
Compile both files but link only `main.o`. Capture and explain the error message word-by-word.

### I3 — Preprocessor inspection
Run `g++ -E` on a file with two `#include` lines. Count how many lines the output grew.

### I4 — Symbol table
After `g++ -c`, use `nm main.o` (or equivalent). Identify one defined (T/t) and one undefined (U) symbol if present.

### I5 — Prediction
```cpp
// a.cpp
int f();
int main() { return f(); }
```
Does `g++ -c a.cpp` succeed? Why? What fails at link if `f` is never defined?

## Advanced exercises

### A1 — Startup order
Research: what runs before `main()` in your toolchain? List global constructor phase (preview SEC-10).

### A2 — Static linking vs dynamic
Link once statically (`-static` where supported), once dynamically. Compare executable size with `ls -l`.

### A3 — Build without `main`
Create valid object file with no `main`. Link to executable — what error? Who requires `main` — compiler or linker?

### A4 — Cross-TU constexpr
Explain whether `constexpr` function in header affects compile vs link stage.

### A5 — Pipeline timing
Time `g++ -c` vs full link on a 3-file project. Report ratio — justify with SEC-01 model.

## Self-check answers (attempt first)

<details>
<summary>B2 answers</summary>

- `-E` → preprocessed text (stdout/file)
- `-c` → object file `.o`
- `-o app` → compile all sources + link → executable `app`
</details>

<details>
<summary>B3 answers</summary>

Compile, Link, Runtime
</details>

<details>
<summary>I5 answers</summary>

Compile succeeds — `f()` only needs declaration. Link fails — undefined reference to `f()`.
</details>
