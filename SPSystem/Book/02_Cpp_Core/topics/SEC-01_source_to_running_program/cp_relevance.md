# SEC-01 Competitive Programming Relevance

**Level:** Low direct — CP is run-time algorithmic.  
**Connection:** Build pipeline = **dependency resolution** mindset.

## CP problems (dependency / ordering)

| Platform | Problem | Skill trained |
|----------|---------|---------------|
| LeetCode | 207. Course Schedule | DAG = compile dependency graph |
| LeetCode | 210. Course Schedule II | Topological order = build order |
| CSES | — | N/A for SEC-01 |
| Custom | Given module deps, output valid compile order or detect cycle | Direct SEC-01 metaphor |

## Contest implementation note

CP solutions are usually **single-file** — one TU, one compile+link. SEC-01 still applies: you invoke compiler+linker even for one file.

## Speed tip

`g++ -std=c++17 -O2 -pipe` — know what `-c` vs full build does when testing locally.

## When SEC-01 matters in contests

- Multi-file templates (some ICPC team setups)
- Understanding TLE vs compile error vs WA
- Fast incremental local testing

## Practice (optional)

Solve LC 207. Draw parallel: courses = TUs, prerequisites = "must link after."
