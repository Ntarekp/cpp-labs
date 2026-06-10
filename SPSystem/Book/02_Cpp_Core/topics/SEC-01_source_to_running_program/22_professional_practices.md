# SEC-01 Professional Industry Practices

## Daily engineering

| Practice | SEC-01 basis |
|----------|--------------|
| Incremental builds | Per-TU compilation |
| Clean rebuild on weird errors | Stale object mismatch |
| CI compile on every PR | Same pipeline, hermetic env |
| Pin compiler version | Reproducible object code |
| `-Werror` in CI | Fail at compile, not production |

## Build configurations

- **Debug:** `-g` — symbols for debugger (load/run observability)
- **Release:** `-O2 -DNDEBUG` — same pipeline, optimized objects
- **ASan/UBSan:** Instrument at compile — different object, same stages

## Deployment artifact

Ship **executable** or **shared libs** — know what linker produced. Container images often copy single binary (Go/Rust/C++ static).

## On-call relevance

"Service won't start" — not SEC-01 if binary missing; "undefined symbol" at **dynamic load** — extended SEC-01 (shared lib).

## Team communication

"I fixed the link" vs "I fixed the compile" — precise language prevents confusion.

## Code review

Reviewer asks: "New `.cpp` added — CMake/target updated?" — SEC-02 preview.
