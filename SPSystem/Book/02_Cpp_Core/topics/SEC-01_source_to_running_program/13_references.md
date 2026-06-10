# SEC-01 References

## External

- [cppreference: Translation phases](https://en.cppreference.com/w/cpp/language/translation_phases)
- [GCC Overall Options](https://gcc.gnu.org/onlinedocs/gcc/Overall-Options.html) — `-E`, `-c`, `-o`
- [Microsoft: Linker](https://learn.microsoft.com/en-us/cpp/build/reference/linking) (MSVC toolchain)
- [ELF format intro](https://en.wikipedia.org/wiki/Executable_and_Linkable_Format) — load stage

## Textbooks

| Book | Chapters |
|------|----------|
| *C++ Primer* (Lippman) | Ch. 2 (variables), Ch. 6 (functions) — compile context |
| *Computer Systems: A Programmer's Perspective* (Bryant & O'Hallaron) | **Ch. 7 Linking** — essential |
| *Effective C++* (Meyers) | Items 26–27 — compile/link cost |

## Documentation

- `g++(1)` man page: `-std=c++17`, `-c`, `-E`, `-o`
- C++ standard: `[basic.start.main]`, `[lex.phases]`

## Video

- **The Cherno** — C++ series (compilation/linking episodes)
- **Computerphile** — "How does compiling work?"
- **CppCon** — search "link time" / "ODR" (preview SEC-05)

## Research topics

1. COFF vs ELF vs Mach-O executable formats
2. Link-time optimization (LTO) — compiler+linker fusion
3. `lld` vs `gold` vs `bfd` linkers

## Industry case studies

- **Google hermetic builds** — SEC-01 reproducibility at scale
- **LLVM monorepo** — incremental compilation infrastructure
- **Gentoo/Chrome** — link-time dominates large C++ builds

## Assignments

**A1** — Error diary (see practice.md)  
**A2** — Build cartography for `sec01_lab` three-file project  
**A3** — Write 500-word essay: "Compilation is local; linking is global" with example

## Mini projects

**MP-1** — `build_explorer` CLI: commands `preprocess`, `compile`, `link`, `run` wrapping `g++`

## Capstone links

CAP-05 48-hour challenge assumes SEC-01 internalized — multi-file build without confusion.

## Advanced challenges

1. Link program without `main` — identify which component enforces entry point
2. Compare `-O0` vs `-O2` object disassembly (`objdump -d`) — same pipeline, different code
3. Measure link time vs compile time on 10-file synthetic project

## Alternative implementations

| Toolchain | Notes |
|-----------|-------|
| GCC + GNU ld | Linux/MinGW default |
| Clang + lld | Faster link, same stages |
| MSVC `cl.exe` + `link.exe` | Windows native |
| `zig c++` | Cross-compile same model |

## Historical context

See [21_historical_context.md](21_historical_context.md)

## Professional practices

See [22_professional_practices.md](22_professional_practices.md)

## Common mistakes

See [20_common_mistakes.md](20_common_mistakes.md)

## Alternative build models

| Model | Tradeoff |
|-------|----------|
| Single TU unity build | Faster compile opt, slower full rebuild |
| Separate TUs | Industry default — scales teams |
| Modules (C++20) | Different include model — SEC-03+ |
