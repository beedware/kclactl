# Verification and build audit

Audited commit `54ec932`, 2026-11-19. The tracked PDF is 26 A4 landscape pages with a cover and numbered pages 1–25. The local environment is Darwin arm64, Homebrew GCC 16.1.0, TeX Live 2025, a default stack of 8,176 KiB, and `LDBL_MANT_DIG=53`. NWERC 2026 specifies Ubuntu 24.04.3, GNU C++20 with GCC 13.3.0, and a 2 GiB total judge memory budget. Linux judge reproduction remains outstanding. The local Docker client had no available daemon. [NWERC 2026 systems](https://2026.nwerc.eu/system)

## Checks and results

| Check | Result |
|---|---|
| `make test-compiles` under the repository's C++17 flags | 135/136 compiled. `SIMD.h` failed because its AVX2 target conflicts with ARM. This header is outside the PDF. Nine exclusions are listed below. |
| GNU C++20 standalone syntax check in scratch | 135/136 compiled with the same exclusions. `SIMD.h` is the sole failure. This used the local GCC and the unmodified contest template. |
| `make test` in the checkout | The runner could not raise its stack limit and remained on `Factor.cpp`. I interrupted the run and moved its temporary binary into scratch. |
| Existing stress tests in scratch, 90 seconds per case | 77 passed, 2 had compile errors, 2 asserted, 2 timed out, and 1 explicitly skipped. All 84 results are in the [test data](08-stress-results.md). |
| Focused reruns of the three environment failures | `2sat.cpp` passed its full unchanged body on a 128 MiB thread stack. Both Delaunay tests passed with the GNU trap helper replaced by a no-op in a forced-included scratch header. Thus 80 of 84 cases reached a passing outcome across configurations, with three of the 80 qualified by those changes. |
| `make fast` in scratch | Generated 26 pages in one pass. |
| Two LaTeX passes for the handbook in scratch, with `make -o test-session.pdf kactl` | Both passes emitted 26 pages. This exercised the complete handbook and resolved the TOC. Two underfull boxes were reported and the hash helper emitted compiler diagnostics. |
| `make kactl` in scratch with `test-session.pdf` absent | Failed at test-session page output because `\@teamname` is undefined. The committed artifact can mask this when make considers it current. |
| `make showexcluded` in scratch | Host `grep` rejected `-P` and the target still exited 0 with 149 candidate paths. The direct import count produced the actual eight unprinted headers in the [layout audit](05-space-and-runtime.md). |

The stress rerun copied the tracked `content/` and `stress-tests/` files to a temporary directory. It used the repository's `-Wall -Wfatal-errors -Wconversion -std=c++17 -O2` flags and precompiled template. Each case had its own executable, working directory, compile output, runtime output, and exit status. Four local jobs were used. The time limit measures wall time. The timings indicate the scale of the local checks and are sensitive to concurrency and hardware.

## Why the six stress exceptions and one skip occurred

| Case | Native result | Follow-up |
|---|---|---|
| `graph/2sat.cpp` | 90 s timeout | A trace reached the full unsatisfiable graph's solve call. The reduced test passed. Running the original test body on a 128 MiB pthread stack passed in 0.780 s. The test requests a 512 MiB shell stack in the repository runner. |
| `geometry/DelaunayTriangulation.cpp` | C++17 compile error | Darwin lacks `feenableexcept` used by the test. The original test code passed in 0.645 s with only the trap call stubbed through a scratch include, retaining its original `main`. |
| `geometry/FastDelaunay.cpp` | Same compile error | Passed in 7.585 s with the same stub and exact test entry point. The existing fixture substitutes an arena for `new`. The rerun exercises its comparisons without floating point traps. |
| `number-theory/MillerRabin.cpp` | Assertion at line 74 | For `754221686909783899` the library said composite and the test's wider oracle said prime. A separate deterministic oracle using 128-bit multiplication agreed that it is prime. |
| `number-theory/Factor.cpp` | 90 s timeout | The original runner also stalled here. A single call to `factor(754221686909783899)` timed out after 3 s. The documented floating point range on this host is crossed before the factorization starts. The test itself checks factor primality against the same library routine. |
| `number-theory/ModSum.cpp` | Assertion at line 71 | The exhaustive small comparisons finished. The failing random input was `to=134456, c=1129900996, k=6490600292, m=246235914`. The code and an independent widened floor sum both gave `16554116784994`. Its relative deviation from `m*to/2` was `1.01944624769e-5`, above the test's `1e-5` cutoff. Separately the large-residue probe below found an implementation bug. |
| `number-theory/ModMulLL.cpp` | Printed `Skipped.` and exited 0 | The test explicitly skips when `LDBL_MANT_DIG != 64`. The runner would normally count that exit as a pass. |

## Focused probes

These probes used unchanged headers unless the row explicitly says a trace was added in scratch. UBSan checks used `-fsanitize=undefined -fno-sanitize-recover=undefined`. The [code findings](02-code-findings.md) explain the fixes and provide further deductions from source.

| Probe | Observed result |
|---|---|
| Lazy segment tree on `[1,2]`, assign `1e9` to both elements, then query first | Full range `1e9`, first range `1`. A disjoint branch also masked a first element of `-1000000001` as `-1000000000`. |
| Global `new` called with sizes 16, 1, 16 | Address residues 8, 7, 7 modulo 16. |
| Heap construct suffix tree for `"a{a\|"`, the LCS separator scheme | UBSan reported index 26 outside `int[26]`. `sizeof(SuffixTree)=24001256`. |
| Suffix array of a single byte 128 with signed char | `-D_GLIBCXX_ASSERTIONS` stopped at a negative count-table index converted to an oversized unsigned index. |
| Polynomial roots of `-x²` and `x-10` on `[-1,1]` | No repeated root returned in the first case, and out-of-range root 10 returned in the second. |
| `modsum(6,5,m-1,m)` with `m=4000000000000000000` | Returned `3106511852580896783`. Direct residues sum to 15. |
| Printed fraction binary search call | Asserted at `f(hi)`. `approximate(3.5,4)` also disproved the continued fraction annotation's error bound. |
| Fast input for `2147483647` and an empty stream | UBSan caught signed overflow on the maximum `int`. The read at EOF timed out. |
| `multinomial({31,31})` and `angleDiff((50000,0),(50000,0))` | UBSan caught signed multiplication overflow in each. The multinomial's mathematically exact result fits in `ll`. |
| Existing `ModInverse.cpp` compiled with AddressSanitizer | Read 8 bytes before the allocated 8,000 byte region. Its configured `LIM` crosses the modulus, which makes `inv[mod % i]` read `inv[0]`. This case had exited successfully in the regular run. |
| Four-variable simplex example | Time limit on the unchanged solver. A scratch copy with a repeated-tableau check reported the same state after 12 pivots. |
| NTT as a standalone include | Compiler diagnosed two definitions of the fixed modulus. The maximum-length padding error follows directly from the power-of-two expression. |

Four supplementary checks included the exact library headers under GNU C++20. They all passed:

| Header | Independent oracle |
|---|---|
| `SuffixAutomaton.h` | All 8,191 binary strings of length up to 12. Compare the substring count with explicit substring sets and traverse every expected substring in the automaton. |
| `SweepLine.h` | 10,000 seeded sets of up to 17 small integer rectangles, checked by counting occupied unit cells. An additional rectangle spanning x from `-2e9` to `2e9` returned area `4e9` as expected. |
| `BellmanFord.h` | 12,000 seeded directed multigraphs, up to eight vertices, including negative edges and self-loops. Compare finite values against synchronous relaxation and negative-cycle flags against reachability from still-improvable edges. |
| `Tridiagonal.h` | 10,000 seeded strictly diagonally dominant systems with up to 40 rows and known integer solution vectors. Check every double output with absolute tolerance `1e-8`. These matrices exercise the common stable case. |

## Coverage and harness limitations

The repository checks 136 of 145 headers for standalone compilation. The nine exclusions were inspected:

| Header | Reason the isolated compile is different from normal use |
|---|---|
| `SolveLinear2.h` | Instructions and statement fragments to edit `SolveLinear`. The similarly named stress test uses a separate function. |
| `Unrolling.h` | A loop sketch with placeholders and surrounding locals. |
| `MinCostMaxFlow.h` | GNU PBDS include is enabled in the PDF, while the stress fixture brings the required dependency itself. |
| `DivideAndConquerDP.h` | Application supplies `dp` and `res`, plus a cost and bounds. |
| `ModInverse.h` | Statements expect local `mod` and `LIM`. The stress fixture includes the fragment but passes `LIM=1000` for smaller primes, exceeding the stated limit. On iteration `i=mod` it reads `inv[0]` outside the allocation, then checks only earlier entries. |
| `ModSqrt.h` | Needs the three argument modular power overload. The test supplies it. |
| `Hashing-codeforces.h` | Provides an example `main` that conflicts with the contest template's `main`. |
| `NumberTheoreticTransform.h` | The test deliberately separates the fixed moduli and supplies compatible modular power. |
| `MoQueries.h` | Placeholder bodies and variant macros require adaption. The test uses a copy with its own callbacks. |

A scan found 90 distinct header names directly included by the stress programs. That figure includes supporting imports and includes inside namespace or macro fixtures. It is not a count of independently verified algorithms. Nine stress files have no direct library header include. These cover locally copied variants or theorems, including `MoQueries`, `SolveLinear`, `SolveLinear2`, `SolveLinearBinary`, `IntDeterminant`, `Tridiagonal`, `FastInput`, matrix-tree, and Erdős–Gallai. The compile check tests each header in isolation. It leaves namespace conflicts between snippets and actual solution integration to a separate check. Historic unit tests are labelled broken in the README. [Compile runner](../doc/scripts/compile-all.sh) · [Stress runner](../doc/scripts/run-all.sh) · [README](../README.md#L56)

## PDF and print pipeline findings

- The test-session source sets `\university` without `\team`. The package uses `\@teamname` in both running headers. A full rebuild after deleting generated artifacts needs a default or an explicit team. [Test-session source](../content/test-session/test-session.tex#L5) · [Shared header](../content/tex/kactlpkg.sty#L83)
- The build hash and Vim hash preprocess different inputs. For the same sample `int f(int x) { return x + 1; }`, the local build helper gave `b3025b`, GNU preprocessing with built-ins gave `71c395`, and GNU `-fpreprocessed` gave `bc8d20`. Apple's `cpp` rejected `-fpreprocessed`. Using `cpp` on standard input also emitted GNU header errors for two printed imports. The shell pipeline returned the last command's success, while the Python script used the digest without checking preprocessing success. A shared hash command with defined input, language, compiler flags and error handling would make printed checksums reproducible. [Build hash](../content/contest/hash.sh) · [Vim command](../content/contest/.vimrc#L9) · [Preprocessor](../content/tex/preprocessor.py#L148)
- The Python preprocessor displays `Description`, `Usage`, `Time`, `Memory`, and dependencies. Limits placed only in `Details` disappear. Move constraints needed for correctness into a field that prints. [Preprocessor](../content/tex/preprocessor.py#L157)
- The GitHub workflow builds the handbook before starting compilation and stress checks. If the first step fails, the workflow can hide the results of the other checks. Make these independently reportable and pin a contest-like toolchain when verifying a print release. [Workflow](../.github/workflows/ccpp.yml)
- The 26 page result includes an identity cover, and both NWERC 2026 and EUC 2026 describe a 25 page cap on reference material. Plan to print numbered pages 1–25, with the cover handled according to the event's instructions. Check readability at actual scale against the stated half metre rule. [NWERC 2026 rules](https://2026.nwerc.eu/rules) · [EUC 2026 TRD instructions](https://euc.icpc.global/home-2026/trd-instructions/)
