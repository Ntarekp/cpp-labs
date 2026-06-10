# SEC-01 Open Source Relevance

## What to observe in any C++ repo (SEC-01 lens)

1. **Build entry** — `CMakeLists.txt`, `Makefile`, `meson.build`
2. **Artifact** — where `.o` / build dir lives
3. **Target graph** — libraries vs executables = link relationships
4. **CI compile step** — reproduces SEC-01 at scale

## Recommended OSS reading (after SEC-02)

| Repo | SEC-01 focus |
|------|--------------|
| [fmtlib/fmt](https://github.com/fmtlib/fmt) | Library target + test executable link |
| [catchorg/Catch2](https://github.com/catchorg/Catch2) | Header + implementation TU split |

## Exercise (post SEC-02)

Clone fmt. Answer without running:
- How many TUs compile for core library?
- What is the link step for `tests` target?

## Not yet

Do not study SPSystem build for SEC-01 mastery — generic lab sufficient. SPSystem build graph is **SEC-05** observation.
