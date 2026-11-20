# Draft proofs and contest tricks

Put the core cards alongside the relevant algorithms or in the proposed techniques appendix. This is draft reference material for a future print revision. The suggested line cap for the appendix is 124. Shorten explanations where the team can reconstruct them, while retaining each condition and invariant. The shortlist below follows the [contest evidence](04-contest-coverage.md) and [space budget](05-space-and-runtime.md).

## Core cards for the printed reference

### 1. Search a monotone predicate

For first true, maintain `lo` impossible and `hi` possible. Check whether either boundary outcome needs separate handling. Each midpoint replaces the endpoint with the same truth value. Once adjacent, `hi` is the first feasible integer. Prove the predicate before coding the loop. For “maximum feasible,” reverse the truth convention or search the first infeasible value.

```cpp
// Invariant: lo < hi, !ok(lo), ok(hi). GCC C++20.
while (lo + 1 < hi) {
    auto m = std::midpoint(lo, hi);
    if (ok(m)) hi = m;
    else lo = m;
}
```

Cost is predicate time times `O(log range)`. Build sentinels so the search never calls the predicate outside its domain. For real output use a fixed iteration count chosen from range and accuracy. Ternary or golden-section search needs a unimodal objective. Floor and ceiling terms can break unimodality even when a continuous relaxation is convex. [NWERC 2024 Limited Library](https://2024.nwerc.eu/main/solutions.pdf) · [SWERC 2025 Adjusting Drones](https://swerc.eu/2025/analysis.pdf)

### 2. Sorted greedy by exchange

When each item fits a suffix of the sorted resources, assign it to the smallest available resource that fits. Take a feasible assignment in which this item gets a larger resource. Swap its resource with the one greedy picks. If another item used the smaller resource, it can also use the larger one. Repeat while fixing the choices already made. If the greedy choice fails after those swaps, no original feasible assignment existed.

For interval cover, prove that the next selected interval may extend to the furthest right among intervals covering the first uncovered point. Replacing the corresponding choice in any optimal cover cannot reduce coverage of the remaining line. Use a progressing endpoint, and remember that touching endpoints cover a continuous half-open range. [NWERC 2024 Limited Library](https://2024.nwerc.eu/main/solutions.pdf) · [EUC 2025 Ads](https://euc.icpc.global/wp-content/uploads/2025/03/solutions.pdf)

### 3. Count, compress, sweep

- Prefix: `P[0]=0; P[i+1]=P[i]+a[i]`. Sum on `[l,r)` is `P[r]-P[l]`. A 2D box uses four prefix corners. To add `v` to a range, update its difference array at `l` and `r`, then accumulate.
- Compression: sort and unique the coordinates, use ranks for order, and retain coordinates for lengths. A slab between ranks `i` and `i+1` has width `x[i+1]-x[i]`.
- Sweep: group equal coordinates. Account for the previous active state over the interval before applying this coordinate's events. For point queries at the event itself, choose tie order based on the intended open or closed endpoints.
- Two pointers: state what makes the left/right boundary move only forward. Each boundary traverses the array once. A sum window with arbitrary signed increments may lack monotonicity.
- Constant quotient blocks: for `q=n/l>0`, the last `r` with the same `floor(n/i)` is `n/q`. Group `[l,r]` and advance `l=r+1`. At most `O(√n)` groups, since either `i≤√n` or the quotient is small. [EUC 2024 Damage per Second](https://euc.icpc.global/wp-content/uploads/2024/03/EUC-Solutions.pdf)

### 4. Choose the shortest path algorithm after defining the state

Represent all history that affects future moves. State examples are `(cell,last move type)`, `(vertex,parity)`, and `(cell,direction)`. Generate edges on demand. Count states times branching before allocating arrays. Start all sources with distance zero for multi-source search. Store the predecessor on each improvement, or the first discovery in ordinary BFS.

| Edge model | Algorithm and invariant |
|---|---|
| Unit cost | Queue BFS. Vertices are first discovered by the earliest possible layer because every edge advances one layer. Distances are `O(V+E)` to compute. |
| Costs 0 or 1 | 0–1 BFS. Relax strictly and push a 0-edge improvement to the front, a 1-edge to the back. Current labels stay in two consecutive distance layers in the deque. Skip stale entries when storing labels alongside vertices. `O(V+E)`. |
| Nonnegative costs | Dijkstra. Extract the smallest current distance. If a shorter path to that vertex existed, its first unfinalized vertex would already have a smaller label via the finalized predecessor, since no later edge can lower the path cost. |
| DAG | Relax in topological order. All incoming distances are ready when processing a vertex. This also handles negative edges in `O(V+E)`. |
| Negative edges, possible cycles | Bellman–Ford. After `k` rounds, all optima among paths using at most `k` edges have been considered. After `V-1`, remaining improvements indicate reachable negative cycles. Mark all their reachable vertices. |

For heap Dijkstra with a min-heap of `(dist,v)`, pop, skip if the key differs from `dist[v]`, and push a new pair whenever relaxing. Bound `dist+weight` before adding. Early exit is sound when the target is extracted with its current label. [Sparse Dijkstra](https://cp-algorithms.com/graph/dijkstra_sparse.html) · [0–1 BFS proof](https://cp-algorithms.com/graph/01_bfs.html) · [EUC 2025 Pinball](https://euc.icpc.global/wp-content/uploads/2025/03/solutions.pdf)

### 5. Monotone stack, DSU successor, and doubling

For next **strictly** greater to the right, process left to right. While `a[stack.back()] < a[i]`, assign its answer to `i` and pop. Unresolved positions stay in nonincreasing value order. An earlier greater value would already have popped the position. Each index pushes and pops once, so the scan is linear.

For permanent deletions or fills, maintain a skip to the next live item, or to the next live ancestor on a fixed successor chain. Each deleted item need be processed only once. With union by size and path compression, store the surviving successor as root metadata after merging the sets. The representative itself is chosen by size, so it need not be the physical successor.

Without compression, each time union by size increases a vertex's depth its component at least doubles. This proves `O(log n)` worst case for rollback finds. Path compression plus union by size has a stronger, amortized `O(α(n))` bound. For small-to-large merges, a moved record enters a container with at least twice its previous mass, giving `O(log n)` moves per record and `O(n log² n)` if each move uses an ordered-tree insertion. Count records or underlying elements when duplicate suppression changes the number of distinct keys. [DSU and successor metadata](https://cp-algorithms.com/data_structures/disjoint_set_union.html) · [NWERC 2024 Flowing Fountain](https://2024.nwerc.eu/main/solutions.pdf) · [EUC 2025 Porto Vs. Benfica](https://euc.icpc.global/wp-content/uploads/2025/03/solutions.pdf)

### 6. Use segment tree descent directly

For k-th by counts, check `1<=k<=total`. Descend left if the left sum is at least `k`. Otherwise subtract the left sum and descend right. Counts must be nonnegative, which makes prefix counts monotone. For first greater than `x` in a range, visit left child first, pruning disjoint nodes and nodes with `max<=x`. These searches each work in `O(log n)` on an ordered segment tree.

Use a power-of-two leaf base or explicit node intervals for this descent. An unpadded `2n` iterative layout need not put leaves in original order under a root descent. When just doing range aggregation, the existing two-accumulator query preserves order. [EUC 2026 Deque Sort](https://euc.icpc.global/wp-content/uploads/2026/02/euc-2026-solutions.pdf)

### 7. Derive the DP, then count cells and transitions

Write what a cell means, base cases and impossible states. Prove that histories represented by one cell have the same possible continuations. Count cells times transition cost and the actual bytes. Reconstruct via saved choices or by taking an edge that satisfies the recurrence. Roll rows if only the prior layer is needed and reconstruction can be recovered.

- 0–1 knapsack by sum: each item's transition reads the old layer. Scan sums down when updating in place. Read upward for unbounded use with a positive weight. Boolean version `reach |= reach << w` applies the same rule in word parallel. Start with bit 0 set. Counting uses sums of ways instead of reachability.
- Subset path DP: `dp[mask][v]` describes a path using exactly `mask` and ending at `v`. Delete the last vertex to justify the recurrence over incoming neighbors. Generic cost `O(n²2^n)` time and `O(n2^n)` entries. For Boolean existence, one word `end[mask]` can encode possible last vertices for small `n`. Set bit `v` if `end[mask without v] & inMask[v]` is nonzero.
- Interval DP: identify the first/last split, prove independence of the parts, then fill by length. The cubic table is often sufficient. Apply Knuth or divide-and-conquer optimization only after proving the appropriate argmin property.
- Merge equivalent states: if objects are exchangeable, try counts instead of identity masks. If each transition only needs a sum or maximum over a range, try maintaining that aggregate directly. [NWERC 2023 Jogging Tour](https://2023.nwerc.eu/main/solutions.pdf) · [NWERC 2025 Erratic Lights](https://2025.nwerc.eu/solutions.pdf) · [EUC 2026 Evaluation](https://euc.icpc.global/wp-content/uploads/2026/02/euc-2026-solutions.pdf)

### 8. Tree cuts, SCC, 2-SAT, and flow

- **MST.** A lightest edge crossing a cut that respects chosen edges is safe. Add it to an optimum containing the chosen edges, then remove an edge on the new cycle crossing the cut. Cost does not increase. Kruskal uses the current DSU component as the cut and the sorted order supplies the light edge. [Kruskal reference](https://cp-algorithms.com/graph/mst_kruskal.html)
- **Subtree parity.** XOR one at both endpoints of every extra edge. The XOR in a subtree counts its crossing edges mod 2, because a wholly internal edge contributes twice. A closed walk crosses every cut an even number of times. Apply this condition to each tree edge and verify that the selected edges give the required connected route. [NWERC 2025 Canal Crossing](https://2025.nwerc.eu/solutions.pdf)
- **Bridges and articulation points.** With DFS entry times and low links, a tree edge `u→v` is a bridge iff `low[v]>tin[u]`. A non-root `u` disconnects a child subtree iff `low[v]>=tin[u]`. A DFS root needs at least two children. Use edge IDs to skip exactly the parent edge in a multigraph. [NWERC 2024 Glued Grid](https://2024.nwerc.eu/main/solutions.pdf)
- **2-SAT.** Clause `a∨b` yields `¬a→b` and `¬b→a`. A variable and its negation in one SCC imply a contradiction. Otherwise topologically order SCCs from sources to sinks, and make the literal in the later SCC true. A violated implication `a→b` would give `rank(¬a)<rank(a)≤rank(b)<rank(¬b)≤rank(¬a)`, using the reverse complementary implication. The KCLACTL implementation handles its own literal encoding and assignment. [EUC 2026 Fix the Coloring](https://euc.icpc.global/wp-content/uploads/2026/02/euc-2026-solutions.pdf)
- **Min cut.** If a residual path reaches the sink, augment along it. Otherwise let `S` be the vertices reachable from the source through positive residual capacity. Every forward edge crossing `S` is saturated and any cancellable reverse flow across the cut is absent. Thus the cut capacity equals the flow, which is the upper bound from any cut. [Dinic reference](https://cp-algorithms.com/graph/dinic.html)

### 9. Probability, geometry, and integer arithmetic

- **Count by indicators.** For a total `X=Σ I_i`, `E[X]=Σ P(I_i=1)` even for dependent events. For independent choices ordered by cost, the chance the i-th is the first success is `p_i∏_{j<i}(1-p_j)`. If conditioning on some success, divide by `1-∏(1-p_i)` when it is nonzero. [NWERC 2024 Kruidnoten and Mouse Trap](https://2024.nwerc.eu/main/solutions.pdf)
- **Geometry signs.** `cross(b-a,c-a)` is twice signed triangle area and its sign tests left/right. Use a wide type before forming differences and products. The shoelace sum follows by summing signed origin triangles, since internal edges cancel. If summing over triples, group by the middle index and apply bilinearity to prefix and suffix vector sums.
- **Manhattan coordinates.** `|dx|+|dy| = max(|dx+dy|,|dx-dy|)`. One sign pair adds the magnitudes, and neither absolute sum can exceed their sum. Track checkerboard parity with `x+y mod 2`. [EUC 2025 Statues](https://euc.icpc.global/wp-content/uploads/2025/03/solutions.pdf)
- **Floors and ceilings.** For `b>0` and signed `a`, `q=a/b, r=a%b`. The mathematical floor is `q-(r<0)` and the ceiling is `q+(r>0)`. This avoids overflow from `a+b-1`. Take gcd before multiplying to form an lcm, and widen before evaluating an exact cross product.
- **Permutation parity.** A length-`k` cycle splits into `k-1` transpositions, so sign is `(-1)^(n-cycles)` counting fixed points. To compute binomial parity, `C(n,k)` is odd iff every set bit of `k` is in `n`. Over mod 2, `(1+x)^(2^i)=1+x^(2^i)` and the selected terms encode exactly the bit subsets. [NWERC 2024 Glued Grid](https://2024.nwerc.eu/main/solutions.pdf) · [NWERC 2025 Hasty Haul](https://2025.nwerc.eu/solutions.pdf)

### 10. Subsets, strings, and constructions

- **Submasks.** Enumerate `s=m`, then `s=(s-1)&m` until after processing 0. Over all masks there are `3^k` pairs, because each bit is outside the mask, in the mask only, or in the submask. The subset zeta transform in the current handbook costs `O(k2^k)`. After processing bits 0 through `b`, the accumulator sums exactly the choices that can differ on those bits. [EUC 2026 Jewel Guards](https://euc.icpc.global/wp-content/uploads/2026/02/euc-2026-solutions.pdf)
- **Exact pattern match.** For nonempty pattern `p`, use Z or prefix-function on `p+sep+text` with a reserved separator. An exact rolling hash alternative needs a verification or collision policy. Subsequence matching is a different greedy scan: take the earliest possible occurrence of each next character, which leaves the longest suffix for the rest.
- **Longest common substring.** Concatenate strings with a unique separator and build suffix array and LCP. Take the maximum LCP between adjacent suffixes from different strings. Suffixes sharing a prefix form a contiguous block, so any block containing both sources contains an adjacent pair from different sources. For suffix automaton distinct-substring count, add `len[v]-len[link[v]]` for each non-root state.
- **Period from a palindromic prefix.** If a palindrome has length `a` and a palindromic prefix of length `b`, reflection in the prefix followed by reflection in the whole string maps index `i<b` to `i+a-b`. Thus `a-b` is a period. Reverse those reflections for the converse. If periods `r,t` satisfy `n>=r+t`, the difference is also a period by one step of each size inside the string. Iterate Euclid to get `gcd(r,t)`. [EUC 2026 Palindromes](https://euc.icpc.global/wp-content/uploads/2026/02/euc-2026-solutions.pdf)
- **Constructive proof.** Separate necessary invariants from a recipe that attains them. Try fixing one vertex or suffix and preserving feasibility on the remaining instance. Use a small exhaustive base, symmetry or complements when the remaining cases are finite. For an operation applied repeatedly, seek a representation where it is composition instead of simulation. [NWERC 2025 Arcade Crane](https://2025.nwerc.eu/solutions.pdf) · [EUC 2025 Condorcet Elections](https://euc.icpc.global/wp-content/uploads/2025/03/solutions.pdf)

## Optional cards when space permits

### Range, graph, and DP optimizations

- **Offline dynamic connectivity.** Make an interval of active time for each edge and place it into the corresponding canonical nodes of a segment tree over time. DFS the tree, joining on entry and rolling back to its saved history on exit. Each leaf sees exactly its active edges. For `I` active intervals and `Q` times, the union/query work is `O((I log Q+Q) log V)`. Do not path-compress this rollback DSU.
- **HLD and centroid proofs.** A light child has at most half the parent's subtree size, since the heavy child is at least as large. This bounds the number of light edges on a root path. Removing a centroid leaves each component of size at most half. Each vertex is processed in only `O(log n)` decomposition levels. Either DFS before the shrink can still have linear stack depth.
- **Virtual tree.** Sort queried vertices by DFS entry, add LCAs of adjacent vertices, sort again and deduplicate. For each relevant branching ancestor, two consecutive queried vertices from different child subtrees witness it. Connect each node to its nearest included ancestor via a stack or the existing compressed tree recipe. Use depth differences for compressed edge lengths.
- **Mo ordering.** Sort queries by left block and right endpoint. Left movement is `O(QB+N)`. Across `O(N/B)` blocks the right pointer travels `O(N²/B+N)`. Include sort time and the cost of both add and remove. Try prefix sums or an offline Fenwick sweep before using it if an easier algebraic aggregate exists.
- **Divide-and-conquer DP.** Choose a consistent minimum argmin. If `opt[j]` is nondecreasing, after solving position `mid` no solution to its left needs a larger index, and none to its right needs a smaller index. At each level the candidate ranges split except for shared boundary optima. Give row length, total candidate width, and transition cost. [Divide-and-conquer DP](https://cp-algorithms.com/dynamic_programming/divide-and-conquer-dp.html)
- **Knuth DP.** If `opt(i,j-1) ≤ opt(i,j) ≤ opt(i+1,j)`, search that interval when processing by increasing length. For fixed length, the widths telescope over `i`, so the total tests over that diagonal are linear. Verify the quadrangle and interval monotonicity conditions, and choose consistent ties.
- **Convex hull trick.** Rewrite a transition as evaluation of a line `m_j x_i+b_j`. If slopes and query coordinates arrive in monotone compatible order, remove obsolete lines from the back and expired better choices from the front. Each line enters and leaves once. Otherwise the current dynamic hull or a compressed Li Chao tree supports logarithmic operations.
- **LIS reduction.** In a strict two-key increase, sort first key ascending and break ties by second key descending before taking strict LIS of the second key. Then no increasing subsequence can use two items with the same first key. State whether ties in the original problem permit equality. [NWERC 2025 Group Photo](https://2025.nwerc.eu/solutions.pdf)

### Additional formulas and proofs

- **Expected hitting time.** Set `E[terminal]=0` and `E[v]=1+Σ p(v→u)E[u]` for other states. This conditions on the first step. Process backward on a DAG. On a cyclic finite chain, confirm finite absorption time from the relevant states before solving a linear system.
- **Cauchy–Schwarz.** For positive `x_i,d_i`, `(Σx_i)(Σd_i/x_i)≥(Σ√d_i)²` with equality when `x_i` is proportional to `√d_i`. This can strip continuous effort allocation out of a shortest-path problem. [NWERC 2023 Galaxy Quest](https://2023.nwerc.eu/main/solutions.pdf)
- **Stable quadratic.** With real discriminant and `a!=0`, compute `q=-0.5*(b+copysign(sqrt(D),b))`. Use roots `q/a` and `c/q` by Vieta. Handle zero `q` and the linear case explicitly. Choosing the sign avoids cancellation in the root computed directly.
- **Game proof.** For finite normal play, terminal positions lose and a move to a losing state wins. In a graph with cycles, track unresolved outdegree and propagate statuses through predecessors. Any unresolved state has an unresolved successor and no losing one, so the cycle-capable portion can sustain draws under play that avoids loss. Include whose turn it is if edges differ by player. Grundy XOR is for disjoint impartial components where a turn affects exactly one.
- **Layered construction budget.** Prove that each layer reaches a smaller instance or permanently consumes new work. Bound the total over layers via halving, a geometric series, or charging each object once. Computing the smallest feasible limit without such a bound can conceal a quadratic simulation.
- **Interactive query accounting.** Derive the information each query gives. Look for composition and for redundant constraints before using a search. Count queries in the worst case and remember flushing and termination from the problem statement. [NWERC 2024 Hash Collision](https://2024.nwerc.eu/main/solutions.pdf)
