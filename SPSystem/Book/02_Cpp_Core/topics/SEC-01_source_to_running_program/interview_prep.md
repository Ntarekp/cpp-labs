# SEC-01 Interview Preparation

## Phone screen level

1. Walk me through what happens when you compile a C++ program.
2. Compile error vs linker error — examples?
3. What is `main()`? Who calls it?

## Onsite level

4. You have 50 `.cpp` files. How does the build pipeline scale? What gets recompiled on one file change?
5. Static vs dynamic linking — deployment implications?
6. What runs before `main()`?

## System design tie-in

7. "Your service is a single binary" — what does SEC-01 imply for deployment artifacts?

## How to answer (structure)

**Use CEL:**
- **Context** — multi-file C++ project
- **Stages** — preprocess, compile, link, load, run
- **Link** — tie to their follow-up (CI, debugging, etc.)

## Red flags interviewers hear

- "Compiler links files" (wrong — linker)
- "Headers are compiled separately" (wrong)
- Cannot explain undefined reference

## Mock answer (60 seconds)

"When I build C++, each `.cpp` is preprocessed and compiled independently into an object file with machine code and a symbol table. The linker combines those objects, resolves cross-file references like function calls, and produces an executable. When I run it, the OS loader maps that into memory, the C runtime initializes, then calls `main`. Compile errors are per translation unit; linker errors mean a symbol was declared but not defined anywhere."

## Practice

Record yourself answering Q1 in <90 seconds. Replay — count filler words; aim for zero stage omissions.
