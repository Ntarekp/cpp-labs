# SEC-01 Common Mistakes

| Mistake | Why wrong | Fix |
|---------|-----------|-----|
| "Compiler links files" | Linker is separate tool (often invoked by driver) | Say compile **then** link |
| Fixing linker errors by adding includes | Includes affect compile, not missing definitions | Add `.cpp` to build or define symbol |
| Headers compiled alone | Headers paste into TUs | Only `.cpp` compiles |
| Confusing preprocess and compile errors | `#include` failures are stage 1 | Read message prefix |
| Thinking `main` is OS entry | CRT runs first | Mention CRT in interviews |
| One giant rebuild always | Wastes time at scale | Use `-c` incremental mental model |
| Ignoring exit codes | Debugging starts with `$?` | Check after every run |
| `g++` = compiler only | `g++` is **driver** — preprocess, compile, link | Use explicit `-c` to see stages |

## Diagnostic habit

```
Error appears → Which stage? → Which file/TU? → Symbol or syntax?
```

## Student-specific (multi-file projects)

"I added the `.h` but build fails" — headers don't produce symbols unless included by a compiled `.cpp`, and **implementations** must be in linked TUs.
