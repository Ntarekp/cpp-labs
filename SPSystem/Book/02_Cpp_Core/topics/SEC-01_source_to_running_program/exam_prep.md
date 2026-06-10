# SEC-01 Examination Preparation

## FE-A1 alignment (SEC-01 portion)

This topic contributes ~15% of eventual FE-A1 (pipeline + link errors).

## Written questions

1. List the stages from `.cpp` to running process in order. One sentence each.
2. What is a translation unit? How is it produced?
3. Classify five error messages by stage (instructor provides mix).
4. Why can `g++ -c file.cpp` succeed when `file.cpp` calls undefined external functions?
5. What is the difference between an executable and a process?
6. Draw symbol resolution for `main` calling `helper` across two TUs.

## Practical exam-style task (45 min segment)

Given skeleton multi-file project with intentional link error:
- Identify stage
- Fix with minimal change
- Rebuild using separate compile + link
- Write 3-sentence explanation

## Oral exam-style

- Explain pipeline using publishing house mental model.
- "What happens when you type `./app`?" — trace through shell, loader, CRT, main.

## Grading rubric

| Score | Standard |
|-------|----------|
| 90%+ | Teaches peer without notes |
| 80%+ | Correct; minor terminology gaps |
| 70%+ | Stages correct; linker detail weak |
| <70% | Remedial — repeat SEC-01 |
