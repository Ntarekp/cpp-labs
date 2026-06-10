# SEC-01 Flashcards

| # | Front | Back |
|---|--------|------|
| 1 | Five pipeline stages? | Preprocess → Compile → Link → Load → Run |
| 2 | Translation unit? | One `.cpp` after `#include` expansion |
| 3 | Object file? | Machine code + symbols + relocations for one TU |
| 4 | Compiler scope? | Single TU — local |
| 5 | Linker scope? | All objects — global |
| 6 | `g++ -c` produces? | Object file, no executable |
| 7 | `undefined reference`? | Linker error — missing symbol definition |
| 8 | `expected ';'`? | Compiler syntax error |
| 9 | Who calls `main()`? | C runtime after OS loader |
| 10 | Process vs executable? | EXE = file on disk; process = running instance |
| 11 | Symbol? | Named function/global with linkage |
| 12 | Why separate compilation? | Recompile only changed TUs |
| 13 | Preprocessor type-aware? | No — text only |
| 14 | CRT role? | Startup before `main`, teardown after |
| 15 | `return 0` meaning? | Exit code to OS — success convention |

## Oral drill

Shuffle cards. 90% correct in 10 minutes → G6 pass for SEC-01.
