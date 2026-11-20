# TRD expansion

The previous revision at `c7e53a2` used 25 pages including the cover. The six new listings and proof notes use the remaining print space. The shortlist comes from the [contest coverage audit](04-contest-coverage.md) and its [time and space comparisons](05-space-and-runtime.md).

## Selection

- **Monotone stack and deque.** Next strictly greater supports the overflow transitions in Flowing Fountain. A sliding minimum reuses the same amortization argument and stores only candidates that can still win. [NWERC 2024 solutions](https://2024.nwerc.eu/main/solutions.pdf#page=13)
- **Least prime factor sieve.** A table of least factors supports repeated factorization by division. It fits the prime exponent approach in It's a Kind of Magic. The segmented sieve remains a good choice when only the prime list is needed. [NWERC 2024 solutions](https://2024.nwerc.eu/main/solutions.pdf#page=28)
- **Binary trie and XOR basis.** The counted trie finds the best XOR with one stored key and supports duplicate insertion and deletion. The basis finds the best XOR over subsets and exposes rank and membership. Isaac's Queries uses the relation between common trie prefixes and the highest differing bit of two prefix XORs. [SWERC 2025 analysis](https://swerc.eu/2025/analysis.pdf#page=127)
- **Offline connectivity.** A segment tree on time puts each active interval on exactly one node of the path to each covered time. The listing reuses rollback DSU, and the appendix explains how to form lifetimes from updates and when reverse time suffices.
- **Meet-in-the-middle subset sums.** Sorting one half and enumerating the other gives `O((n+1) · 2^ceil(n/2))` time and `O(2^floor(n/2))` storage. Forty inputs require 8 MiB for the stored sums. Equal ranges count all index-distinct choices, including repeated sums.
- **Additional proof notes.** The appendix gives the zero and one common-bit cases behind the complement formula in Jewel Guards. It also covers the subset transform inverse, unordered full-OR pairs, XOR rank and multiplicities, and quadratic optimization along hull edges. [EUC 2026 solutions](https://euc.icpc.global/wp-content/uploads/2026/02/euc-2026-solutions.pdf#page=16)

## Verification

All six headers compiled together with the contest template under GNU C++17. The differential checks ran with the undefined-behavior sanitizer and a fixed seed.

| Listing or identity | Compared with |
|---|---|
| Offline connectivity | Per-time BFS on 1,800 timelines, including overlapping lifetimes, parallel edges, self-loops, and empty intervals. Checked component sizes and callback order. |
| Binary trie | Linear maximum-XOR scans across 128,000 mixed operations in 7-bit and 64-bit tries. Included duplicate insertions and removal of the last copy. |
| XOR basis | Exhaustive subset XORs on 1,100 inputs. Checked insertion, rank, membership, and biased maximum XOR, plus a basis of rank 64. |
| Least prime factor sieve | Trial division through 10,000 and the prime count through 1,000,000. |
| Monotone stack and deque | Linear next-greater scans and direct window minima on 2,000 arrays with ties. Checked all window sizes through two greater than the array length. |
| Meet-in-the-middle sums | Exhaustive subset counts on 900 signed inputs. Checked extreme signed operands and all `2^40` index subsets of 40 zeros. |
| Two common bits and full-OR pairs | Direct mask and pair counting over 400 random frequency tables. |

## Print layout

Both passes of `make kactl` produced **26 A4 landscape pages including the cover**. The PDF counters show 3,334 listing lines, up from 3,173. PDF text extraction confirmed all six listings and the complete Techniques appendix. The new listings are on physical pages 5–7, 10, and 25. The appendix fits on page 26.
