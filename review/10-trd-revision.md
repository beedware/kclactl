# TRD revision

The revised [contest reference PDF](../kclactl.pdf) is **25 A4 landscape pages**, including the cover. It uses the existing three-column layout and type sizes. I used the [eight contest sets](04-contest-coverage.md) and the [space audit](05-space-and-runtime.md) to choose the additions and cuts.

## Print decisions

| Step | Result |
|---|---|
| Add common graph routines | BFS, 0–1 BFS, heap Dijkstra with parents, and Kruskal appear together on PDF page 12. The shortest-path listings explain the weight assumptions and unreachable values. |
| Add search and deletion routines | The max segment tree finds the first index above a value threshold in `O(log n)`. Fenwick order search works for the constructed tree size. The successor set beside union-find handles permanent deletion in amortized `O(α(n))` per operation. |
| Print proofs and reductions | The Techniques appendix covers state graphs, greedy exchange, tree cuts and parity, low links, amortized deletion, subset DP, exact geometry, and string periodicity. The printed appendix is 127 listing lines and fits on the last page. [Full proof notes](06-proofs-and-tricks.md) |
| Reclaim space | Omitted suffix tree, polynomial roots, simplex, Edmonds–Karp, hill climbing, fast input, and the three allocator-related listings from print. Suffix array and LCP cover the common exact string lookup, and Dinic covers single-source/sink max flow. The omitted sources are available in [content](../content/). |
| Check the layout | The intermediate 26-page build put nine appendix lines on a separate sheet. Removing hill climbing from print brought the appendix together. The active C++ header count went from 137 to 133. The line counters extracted from the PDFs went from 3,353 to 3,173 listing lines. |

## Implementation repairs

- Lazy segment tree and HLD use an explicit assignment flag, a valid maximum identity, and owned nodes. The implicit tree starts at zero. This fixes the assignment and negative-value edge cases and removes the dependency on the allocator.
- Modular multiplication uses unsigned 128-bit intermediates. Miller–Rabin and factorization share it. Modular sums widen their quotient numerator, Tonelli–Shanks shares exact multiplication, and modular inverses use ordinary array indexing.
- The NTT pads to the least sufficient power of two. It handles a full `2^23`-element result modulo 998244353 and reuses one transformed buffer for the result. It shares the three-argument modular exponentiation helper.
- Dinic enforces the same capacity threshold in BFS and DFS and starts from the highest residual capacity bit. Suffix array ranks bytes as unsigned. Multinomial and divide-and-conquer DP preserve wide intermediates and costs.
- Corrected the printed Faulhaber sum, Stirling row, Eulerian definition, Fermat condition, Markov-chain orientation, and rational-search example. Added contracts and complexity notes beside the affected listings.
- The build and editor fingerprints use the same GNU preprocessor flags. The test-session source declares the team field needed by its build target.

## Verification

| Check | Result |
|---|---|
| Two-pass PDF build | Both LaTeX passes from `make kactl` produced 25 pages. `pdfinfo` confirmed A4 landscape and the page count. PDF text extraction confirmed the new listings, omissions, and the final appendix line. |
| Existing stress programs | 15 selected programs passed with GNU C++17 on the local machine. Coverage included Fenwick and segment trees, HLD, max flow and Gomory–Hu, modular arithmetic and factorization, rational search, NTT, and suffix array. |
| Independent graph comparisons | Checked 1,500 directed graphs against Floyd–Warshall, 1,000 forests against Prim, and 1,000 flow cases against exhaustive minimum cuts. Also checked continued flow after adding an edge and distances and capacities near `LLONG_MAX`. |
| Independent data-structure comparisons | Checked 34,000 successor and guided-search cases against an ordered set and a linear scan, including empty arrays and repeated deletions. |
| Boundary cases | Checked an actual convolution of length `2^23`, signed-char suffix input, the wide multinomial example, empty virtual tree input, and 64-bit divide-and-conquer DP costs. |
| Source diff | `git diff --check` passed. |
