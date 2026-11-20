# Space and runtime decisions

## Measured space

The committed handbook and a fresh two-pass handbook build at `54ec932` both have 26 A4 landscape pages. The first is a cover. The reference uses three columns on each numbered page. The code font on page 25 is 7 pt and its listing rows are roughly 8 pt apart. I counted lines using the repository's actual listing preprocessor and counted active imports in the chapter order in `content/kclactl.tex`. The numbers include raw listings and blank lines that the preprocessor counts. They exclude descriptions, figures, chapter headings, and other LaTeX prose.

| Chapter | Numbered pages touched | Imported headers | Listing lines |
|---|---|---:|---:|
| Contest | 1 | 0 | 87 |
| Mathematics | 1–3 | 0 | 0 |
| Data structures | 3–5 | 14 | 384 |
| Numerical | 5–8 | 19 | 462 |
| Number theory | 8–10 | 15 | 208 |
| Combinatorial | 10–11 | 2 | 11 |
| Graph | 11–17 | 30 | 917 |
| Geometry | 17–21 | 35 | 679 |
| Strings | 21–23 | 9 | 267 |
| Various | 23–25 | 13 | 180 |
| Techniques | 25 | 0 | 159 |
| **Total** | **25 distinct numbered pages** | **137** | **3,354** |

Chapter page ranges overlap where material continues into the next column. There are 143 active listings, including six raw listings and several prose-only headers. The PDF extraction on page 25 places the appendix's 159 lines across 27 rows of column one, 69 of column two, and 63 of column three. That is about 2.3 columns of line height, plus its heading. The graph and geometry chapters together account for 1,596 listing lines, or 48% of the current total. Most listings already respect the 63-character convention. Code selection and repeated explanations are the main places to save area.

Eight C++ headers are in the repository only. `HashMap`, `Eratosthenes`, `FastFourierTransform`, `FastFourierTransformMod`, `FastSubsetTransform`, `Hashing-codeforces`, `SIMD`, and `Unrolling`. The difference between this list and the nine compile exemptions is intentional. See the [per-header data](07-header-inventory.md).

## Recommended print package

First address the correctness issues for snippets the team expects to use. Keep the current type size and rely on substitution. A default package can make room for short fundamentals without removing the specialized listings that show direct contest use.

| Move from the print copy | Listing lines available | Reason and dependency |
|---|---:|---|
| Replace the techniques checklist | 159 | Use the same appendix position for short decision rules and proofs. |
| Suffix tree | 50 | The included LCS example requires repair. Suffix array and LCP or suffix automaton cover the same common task. |
| Edmonds–Karp | 36 | Keep Dinic as the default, MCMF for weighted capacities, and a short residual-path explanation. Edmonds–Karp remains a compact training oracle. Push–relabel and Gomory–Hu can stay together until there is a reason to rework that dependency. |
| Polynomial roots | 23 | The basic API misses repeated roots and its numeric interval semantics need repair. Keep a stable quadratic recipe and Horner evaluation as needed. |
| Simplex | 68 | The reproduced cycling case warrants a print hold. Several contest reductions use matching or graph structure, and covered examples do not require a general LP solver. |
| **Total budget released** | **336** | Listing lines before accounting for descriptions and separation. |

| Add or clarify | Estimated line budget | What to fit |
|---|---:|---|
| Technique and proof appendix | 124 | Short proofs and recognition cues for greedy, DP, perturbation/geometry, strings, number theory, and amortization. |
| BFS, 0–1 BFS and sparse Dijkstra | 39 | One input convention, parent and multiple source notes, and a choice table. |
| Kruskal and DSU successor | 16 | Sorted edges plus a cut proof. Store semantic successors separately from DSU representatives. |
| Guided segment-tree search | 14 | First node with max above a threshold and k-th by nonnegative counts. |
| Bounds, dependencies, and contest input checks | 25 | Print critical limits and clarify output/range conventions in the existing descriptions. |
| Lookup headings or index reminders | 8 | Make the common choices findable under Graph, DP, and Techniques. |
| **Proposed total** | **226** | Leaves an arithmetic reserve of 110 listing lines for layout and correctness work. |

The [appendix draft](09-appendix-draft.md) is 122 lines, with a maximum width of 63 characters. I rendered two scratch versions using the existing type size, margins, and three columns. A LaTeX wrapper temporarily skipped the four listings above and substituted the draft. Two passes produced **25 PDF pages total** including the cover. I repeated the build with another **102 reserved rows**, distributed across the five planned additions at their target sections. The result was **26 PDF pages total**, or 25 numbered pages. The reserved rows measure packing for this outline. Real descriptions, formatting, and column breaks can change the final page count. Rebuild the finished candidate at actual size. [Expanded proof notes](06-proofs-and-tricks.md) · [NWERC 2026 TRD rules](https://2026.nwerc.eu/rules) · [EUC 2026 TRD instructions](https://euc.icpc.global/home-2026/trd-instructions/)

If a later edition needs substantially more room, review these decisions with the team:

| Candidate | Lines | Decision criterion |
|---|---:|---|
| Fast Delaunay, lifted Delaunay, 3D hull | 88 + 10 + 49 | Keep one Delaunay when the team can exercise it at full bounds. The lifted version depends on 3D hull and is quadratic. Fast Delaunay reduces asymptotic time and has a more demanding implementation. Keep `Point3D` as a separate primitive if moving the hull. |
| Link-cut tree and directed MST | 90 + 60 | Keep each when practice tasks require its capability and someone can type and adapt it. Static path queries can use LCA/HLD. A directed arborescence uses a different model from an ordinary MST. |
| Global min-cut, Gomory–Hu, second max-flow engine | 21 + 13 + 48 | Keep the one-pair, global, and all-pairs cut tasks distinct. Gomory–Hu currently uses push–relabel. Changing its engine requires checking the residual-side API. |
| KD tree | 63 | Keep for repeated geometric nearest-neighbor queries on a measured workload. For a single closest pair, use the existing deterministic `O(n log n)` sweep. |
| Bump allocator family | 8 + 10 + 14 | Retire it from the default copy after checking pointer-tree and HLD dependencies. Persistent segment tree already uses the more tractable index approach. |
| Separate numerical distributions and expansions | Prose | Keep expectation, first success, binomial, and hitting times. Trim formulas the team can derive or has seldom consulted. Put error and convergence conditions beside any formula retained. |

## Runtime choices worth putting in print

| Situation | Start with | Complexity and practical limit |
|---|---|---|
| Unweighted or constant positive cost reachability | BFS on actual state IDs | `O(V+E)`. Generate transitions on demand for grids, parity, and direction states. Count the expanded states first. |
| Costs exactly 0 or 1 | Deque shortest path | `O(V+E)`. A simple heap adds a logarithm. With integer weights in `[0,C]`, consider circular buckets with `O(E+CV)` time. |
| Sparse graph, nonnegative weights | Heap Dijkstra with stale labels skipped | `O(V+E log(1+E))` with a lazy heap and `O(E)` heap space in the worst case. For simple graphs the usual bound is `O((V+E) log V)`. Prefer `O(V²)` scanning on dense graphs that already use matrices. |
| DAG, negative edges, or APSP | Topological DP, Bellman–Ford, or Floyd–Warshall | `O(V+E)` on a DAG even with negative edges. Use Bellman–Ford when reachable negative cycles affect the answer. Floyd costs `O(V³)` time and `O(V²)` memory. |
| Edges sorted by arbitrary weights | Kruskal and DSU | `O(E log E + V)` overall with standard sorting and near-constant amortized unions. A dense implicit graph can favor `O(V²)` Prim without materializing all edges. |
| Counts, sums, or k-th by frequency | Prefix arrays for static queries, Fenwick for point updates, tree descent for mixed aggregates | Static preprocessing `O(n)` and queries `O(1)`. Fenwick is `O(log n)` and stores `n` sums. A guided tree descent is `O(log n)` rather than `O(log² n)` binary search over range queries. Order search requires nonnegative frequencies. |
| Static RMQ / online range updates / historical versions | Sparse table / lazy tree / persistent segment tree | Sparse table `O(n log n)` space, `O(1)` idempotent query. Lazy tree `O(log n)` per operation with valid tags. A persistent tree allocates up to `ceil(log₂ N)+1` nodes per update and grows its vector amortized. |
| Path or subtree work on a static tree | Euler order, binary lifting or LCA, then HLD if needed | Euler order makes a subtree contiguous. Binary lifting gives arbitrary upward jumps in `O(log n)`. HLD splits a path into `O(log n)` ranges, so a segment tree gives `O(log² n)` path work. Avoid the dynamic forest machinery for static edges. |
| Many removable candidates and offline queries | Monotone stack plus DSU / divide time and roll back | A stack pops each element at most once. An offline active interval is stored in `O(log Q)` time-tree nodes. Rollback has logarithmic finds and constant work per restored record. |
| Subset reachability, counting, or path states | Bitset, ordinary knapsack DP, or mask DP | Boolean 0–1 knapsack can do `O(n ceil(S/w))` word operations. Counting uses numeric entries and typically `O(nS)` time. A mask DP with an end vertex uses up to `n·2^n` storage entries. Use bitsets of possible end vertices when the state stores Boolean reachability. |
| Small vertex counts or large value range | Meet in the middle | Enumerate two halves and sort or hash the combined values. Basic subset-sum pairing takes `O(2^(n/2) log(2^(n/2)))` time and `O(2^(n/2))` memory. |
| Many objects with monotone or repeated transitions | Greedy exchange, prefix sums, grouped quotient jumps, or a shared DP state | Derive the common case and prove why an update can be batched. Divide-and-conquer DP needs monotone optima and Knuth needs two-sided bounds. Use slope monotonicity for a deque CHT when both insertion and query order allow it. |
| Exact pattern match or string lexicographic queries | KMP/Z / suffix array and LCP | KMP and Z are linear. The existing suffix array is `O(n log n)` with `O(n)` auxiliary space for fixed alphabet. Use suffix automaton for distinct substring counting and online extensions. Hashes need a collision policy. |
| Assignment, cover, or capacity | Greedy for ordered thresholds, Hopcroft–Karp for general bipartite cardinality, rectangular assignment for dense weighted matching, Dinic or MCMF for capacities and cost | Use `O(E√V)` matching where suitable. Dense assignment here takes `O(N²M)`. Standard Dinic has `O(V²E)` general time and tighter bounds on unit networks. Successive shortest path MCMF includes the number of augmentations and potential initialization. |
| Exact geometry | Sign of a wide cross product, squared distance, then float only for metric output | With coordinate magnitudes at most `C`, differences are at most `2C` and an orientation determinant is bounded in magnitude by `8C²`. Cast before subtracting and multiplying. Polygon area accumulation may need wider storage even when each determinant fits. |

The graph choices match the worked examples in [contest coverage](04-contest-coverage.md). The relevant implementations and distinctions are documented in [0–1 BFS](https://cp-algorithms.com/graph/01_bfs.html), [sparse Dijkstra](https://cp-algorithms.com/graph/dijkstra_sparse.html), [Kruskal](https://cp-algorithms.com/graph/mst_kruskal.html), and [Dinic](https://cp-algorithms.com/graph/dinic.html).

### Memory examples to keep beside complexity

- Half-open sums at `n=200,000` need roughly 1.6 MB for a Fenwick tree with 64-bit entries. A 64-bit iterative segment tree with `2n` slots uses roughly 3.2 MB.
- A persistent tree on 200,000 coordinates with 200,000 point updates can allocate up to 3.8 million nodes plus roots. At 16 bytes per node, reserve roughly 61 MB for nodes before vector capacity slack and other arrays.
- A full `24×2^24` table takes 1.5 GiB at four bytes per entry, or 3 GiB at eight bytes. One 32-bit end-mask per subset takes 64 MiB. This can enable `O(n2^n)` bitset path transitions when the state only needs reachability.
- A 3D hull table of pairs of 32-bit integers costs about `8n²` bytes before vector overhead. At `n=10,000` the table alone is about 800 MB. The printed suffix tree uses about 24 MB regardless of the input length.

## Future release checks

Build one actual candidate after the content choices are made. Count numbered pages, print single sided at 100%, verify headings and code line breaks, and check the contest rule about the cover. Compile the high-use paste combinations with the judge flags and compare the numeric edge cases with independent wide or brute force answers. Use largest valid inputs for stack, memory, and runtime. Moving a snippet out of the printed reference leaves it available in the code archive for practice.
