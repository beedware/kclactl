# Contest coverage and solution data

I read the jury solution material for the main sets of NWERC 2023–2025, SWERC 2022–23 and 2025, and the ICPC Europe Championship 2024–2026. This gives 94 problems across eight sets. Each row assigns one primary technique family to a jury approach. Other techniques mentioned in that row can matter just as much. The family counts depend on the judgment call about which step drives the solution. The sample excludes practice sessions and is too small to predict an event's future topic distribution.

The lookup column maps the approach to the current KCLACTL PDF. “Checklist” means the term appears in the appendix without a working recipe. “Gap” means the recipe is absent or incomplete. “Keep” identifies a listing or formula that directly helps with the reduction or implementation. A familiar technique may only need a few lines even when it appears several times.

| Primary family | Problems |
|---|---:|
| Direct and constructive | 21 |
| Graphs and trees | 16 |
| Ordering and sweep | 11 |
| Dynamic programming | 11 |
| Arithmetic and probability | 9 |
| Data structures | 7 |
| Geometry | 7 |
| Games | 4 |
| Enumeration | 3 |
| Strings | 3 |
| Flow and SAT | 2 |
| **Total** | **94** |

Graphs and trees includes shortest paths, parity, and structural DFS. Ordering and sweep includes greedy feasibility and binary search on a predicate. Direct and constructive includes invariants or formulas that avoid a larger model. Flow and SAT counts the two rows where a flow or SAT solver drives the cited approach. For example, the matching in Hasty Haul comes from an explicit Gray order and is counted under construction.

## NWERC 2023

[NWERC 2023 jury solutions](https://2023.nwerc.eu/main/solutions.pdf)

| Problem | Primary family | Jury approach and reusable idea | KCLACTL lookup |
|---|---|---|---|
| A Arranging Adapters | Ordering and sweep | Sort, handle the outside chargers, and binary search a feasible count. Group the remaining widths by residue mod 3 in the feasibility test. | Binary search is checklist only. Add a fixed-count predicate and exchange argument. |
| B Brickwork | Dynamic programming | Unbounded reachability over width supports the construction. Find two different usable brick types and justify a gap-free arrangement. The jury compares word-parallel DP with convolution. | NTT exists. Add unbounded versus 0–1 bitset reachability and reconstruction. |
| C Chair Dance | Arithmetic and probability | Compose modular affine maps lazily. When a multiplier is noninvertible on the occupied positions, simulate the merge and cut the number of occupants at least in half. | Keep extended gcd. Add affine composition and a halving argument. |
| D Date Picker | Enumeration | Enumerate subsets on the seven-day side only. For each, take the hours with the largest available counts. | Add “enumerate the smaller axis, optimize the other.” |
| E Exponentiation | Data structures | A symbolic representation avoids evaluating enormous exponents. A no-carry argument reduces comparisons to lexicographic order of digit positions. Maintain that order using a trie or ordered lists. | Trie is checklist only. Add a compact trie recipe after the core omissions. |
| F Fixing Fractions | Enumeration | Enumerate retained numerator digits. Equality determines the new denominator, then check divisibility and the digit removals. | Add gcd cancellation and widening before cross multiplication. |
| G Galaxy Quest | Graphs and trees | Cauchy–Schwarz separates the continuous allocation from route selection. The route minimizes the sum of square roots of segment lengths, so run Dijkstra once. | Keep 3D distance primitives and add shortest path code and the equality condition in Cauchy–Schwarz. |
| H Higher Arithmetic | Direct and constructive | Reduce candidate expressions to products of sums and prove the cases for grouping ones and twos. | Add the exchange and local replacement pattern. |
| I Isolated Island | Direct and constructive | Translate to bipartiteness in the planar dual, then use endpoint parity to avoid building the arrangement. Sort or count repeated endpoints. | Exact coordinate pairs suffice. Add parity as a way to eliminate graph construction. |
| J Jogging Tour | Dynamic programming | Only angles induced by pairs need testing. For each, subset TSP is `O(n²2^n)`, giving `O(n⁴2^n)` overall. | Subset DP is checklist only. Add state and memory formulas. |
| K Klompendans | Graphs and trees | Use a grid state for each previous move type and traverse the doubled graph in `O(n²)`. | Add implicit state BFS and DFS. |
| L Lateral Damage | Direct and constructive | Cover all length-five placements via one diagonal residue class, then inspect the neighborhood of a hit. | Add residue-class hitting sets and count the query budget. |

## NWERC 2024

[NWERC 2024 jury solutions](https://2024.nwerc.eu/main/solutions.pdf) · [Problem set](https://2024.nwerc.eu/main/problem-set.pdf)

| Problem | Primary family | Jury approach and reusable idea | KCLACTL lookup |
|---|---|---|---|
| A Alphabetical Aristocrats | Ordering and sweep | Sort by the substring beginning at the first capital letter. Precompute keys if comparing them is costly. | A short custom-key sorting example suffices. |
| B Binary Search | Graphs and trees | Analyze walks compatible with the four phases of a fixed periodic pattern. Cycles give unbounded length. Finite cases use longest walks and a folding argument. | SCC and topological sort help after the state model. Add a state expansion reminder. |
| C Connect Five | Geometry | Move a unique extreme terminal inward along a safe shortest-path segment. Finish the small number of cases up to symmetry. | Add a Manhattan metric and extreme-point reduction note. An MST alone does not enforce preservation of all shortest paths. |
| D Dutch Democracy | Dynamic programming | Assign each minimal majority to its smallest member under a fixed tie order. Count the remaining choices with a seat-sum DP in `O(nS)`. | `FastKnapsack` solves a maximization variant. Add ordinary counting knapsack and tie discipline. |
| E Evolving Etymology | Arithmetic and probability | Compose index doubling modulo the string length. Precompute the exponent effect in `O(log k)`, then produce characters in `O(n)`. | Keep modular power and show how to pass an arbitrary modulus. |
| F Flowing Fountain | Data structures | Precompute the next strictly greater level with a monotone stack. Skip filled levels with a successor structure and amortize work over deletions. | DSU is printed. Add the monotone stack and explain how to preserve the physical successor when union by size selects the representative. |
| G Glued Grid | Graphs and trees | Decompose at articulation points and check permutation parity in each movable component. A grid-specific alternative uses flood fill. | Keep biconnected components. Add parity from cycle count or inversion count. |
| H Hash Collision | Direct and constructive | For any `x`, query `c=f^n(x)` and obtain `r=f^(n-c)(x)`. Composition proves the answer in at most two queries. The jury also presents a longer functional cycle approach. | Add the idea of composing an operation with its inverse exponent or complementary step. String hashing is unrelated to the main solution. |
| I It's a Kind of Magic | Arithmetic and probability | Replace products with sums of prime exponents. Use a sieve, inclusion–exclusion for repeated entries, and prefix sums over cube roots. | Keep sieve, elimination, and combinatorics. Add SPF factorization and an inclusion–exclusion recipe. |
| J Jib Job | Geometry | A crane can pick its longest safe jib independently. For each, scan for the closest taller tower in `O(n²)` overall. | Keep basic squared distance. No geometric union algorithm is required for the editorial approach. |
| K Kruidnoten | Graphs and trees | Compute route distance through each store using distances from the two ends. Sort candidate lengths and multiply the probabilities that all earlier stores fail. | Add Dijkstra and first-success probability over an ordered list. |
| L Limited Library | Ordering and sweep | Sort both sides. For a fixed number of reduced shelves, assign the reductions to the shortest shelves and greedily match heights. Binary search the monotone count. | Add greedy feasibility and binary search together. |
| M Mouse Trap | Geometry | Probability for each triangle is its area divided by the polygon area. Group by the middle vertex and use bilinearity and vector prefix sums for `O(n)` time. | Keep point cross products and polygon area. Add linearity of expectation and the bilinearity trick. |

## NWERC 2025

[NWERC 2025 jury solutions](https://2025.nwerc.eu/solutions.pdf) · [Problem set](https://2025.nwerc.eu/problem-set.pdf)

| Problem | Primary family | Jury approach and reusable idea | KCLACTL lookup |
|---|---|---|---|
| A Arcade Crane | Direct and constructive | Move the largest active value into the final suffix and reduce to a bounded base case. | Add the “fix a suffix, exhaust the tiny base” construction pattern. |
| B Bisecting Bargain | Dynamic programming | Restrict denominations by safe replacements, then test candidate partitions by bitset subset sum. | Add `reachable \|= reachable << w` and its assumptions. |
| C Canal Crossing | Graphs and trees | A closed tour crosses any cut an even number of times. Aggregate parity of extra-edge endpoints in each subtree, select the necessary tree edges, then recover a walk. | Keep Euler walk. Add the subtree endpoint XOR argument. |
| D Dreamcatcher | Arithmetic and probability | The step must be coprime to the number of notches to maximize the cycle contribution. Optimize the chord by taking a coprime step near half, with residue cases. | Keep gcd and basic geometry. Add the modular step cycle-length formula. |
| E Erratic Lights | Arithmetic and probability | Collapse color configurations by counts. Condition on the binomial split after removing the least common color. The jury also gives a count-state DP option. | Keep binomial and expectation formulas. Add conditioning and state aggregation. |
| F Fair Share | Direct and constructive | Rearrange the inequalities to compare each person's net value with one precomputed aggregate. | Add a “sum once, subtract the selected item” reminder. |
| G Group Photo | Data structures | A quadratic grid DP has only linear many scoring transitions. Rephrase it as LIS, or skip inactive states using a segment tree. | Keep LIS and segment tree. Add tie handling and grid-DP sparsification. |
| H Hasty Haul | Direct and constructive | Build a fixed-weight Gray order recursively, then pair consecutive ranks. The parity of the binomial count decides existence. | Add Lucas mod 2 and the fixed-weight Gray recursion as an optional proof card. |
| I Illuminated Stalls | Geometry | Sweep orthogonal segments, cap the number of reported intersections using a structural threshold, and scan ordered neighbors after rotations. | Keep orientation and ordered sets. `SweepLine.h` is rectangle union, so add generic event and active-set guidance. |
| J Juggling Keys | Ordering and sweep | Sort arrivals and departures. Identify which trips require a key, then simulate inventory. | Add sorting equal-time events and two-pass sweep invariants. |
| K KIT Finding | Direct and constructive | Place one desired occurrence and order the remaining letters so no additional occurrence can form. | Add the constructive pattern “build one witness, then forbid the local trigger elsewhere.” |
| L Last Christmas | Direct and constructive | Count appearances and ranks per name, then select the lexicographically best count vector. | An STL counting and tie-breaking reminder suffices. |

## SWERC 2022–23

[Official SWERC 2022–23 solutions](https://swerc.eu/2022/problemset/solutions_swerc2022_2023.pdf)

| Problem | Primary family | Jury approach and reusable idea | KCLACTL lookup |
|---|---|---|---|
| A Walking Boy | Direct and constructive | Insert end-of-day sentinel times and count disjoint available gaps. | Add sentinels for boundary intervals. |
| B Uniform Chemistry | Dynamic programming | Use independence to compute a hitting-time distribution for each actor, then multiply competing survival probabilities. | Add expectation/conditional probability and prefix aggregation in DP. |
| C Another Wine Tasting Event | Ordering and sweep | Take the maximum white count among fixed-size windows. Extend the extremal window to prove the necessary family of distinct witnesses exists. | Add running sums and the extremal choice proof. |
| D Crossing the Railways | Geometry | Make distance and time coordinates, reduce continuous paths to a finite family of critical segments, and advance a DP between rail lines. | Keep orientation and line intersection. Add the “slide to a critical event” proof. |
| E Spinach Pizza | Games | The smallest removable ear has the smallest triangle area in the remaining convex polygon. Choosing it yields pairwise nondecreasing costs and a parity strategy. | Keep cross products. Add pair-a-turn strategy proofs alongside impartial-game notes. |
| F Beppa and SwerChat | Ordering and sweep | Use the complement of the desired set. Relative ranks in the two permutations reveal a maximum eligible suffix. | Add inverse permutation and suffix invariant. |
| G Parmigiana With Seafood | Games | Characterize the game on a path first, then generalize through tree parity and median triples. A rooted DFS aggregates the answer. | Game theory section is useful. Add tree-game modeling and a warning to prove the decomposition. |
| H Controllers | Arithmetic and probability | Count plus and minus signs and reduce each query to an integer equation and an interval for its coefficient. | Add signed division and divisibility boundary checks. |
| I Library game | Games | Sort requirements. Prove one strategy by the largest remaining gap and the other by a pigeonhole argument on multiples. | Add examples of necessity and sufficiency backed by explicit strategies. |
| J Italian Data Centers | Graphs and trees | The large graph is a product. Compress its shortest paths into parity BFS on the base graph plus Hamming distance. | Add parity augmentation and implicit graph traversal. |
| K Train Splitting | Direct and constructive | Use edges incident to a non-universal vertex, with a separate complete-graph construction. | Standard proper edge coloring solves a different problem. Add graph construction invariants. |
| L Vittorio Plays with LEGO Bricks | Dynamic programming | Ordered chains share a common base until they split. The earliest divergence yields an interval DP in `O(n³)`. | Add basic interval DP before the conditional Knuth optimization. |

## SWERC 2025

[Official SWERC 2025 problem analysis](https://swerc.eu/2025/analysis.pdf) · [Problem statements](https://swerc.eu/2025/statements.pdf)

| Problem | Primary family | Jury approach and reusable idea | KCLACTL lookup |
|---|---|---|---|
| A Adjusting Drones | Ordering and sweep | Prove a deterministic evolution toward a monotone condition. Simulate a chosen number of operations in linear time per predicate. | Add integer binary search endpoints and its proof. |
| B Billion Players Game | Ordering and sweep | The worst case is at an endpoint of a linear payoff. An exchange argument sorts the chosen roles and leaves at most one unused value. Use prefix sums for each split. | Add exchange, prefix sums, and “linear maximum/minimum lies at an endpoint.” |
| C Chamber of Secrets 2 | Graphs and trees | Split the blocks into halves when needed. A compatibility cycle recovers the original order up to rotation. | Add mapping labels to graph nodes and walking permutation cycles. |
| D Dungeon Equilibrium | Direct and constructive | Optimize each frequency independently. A bounded frequency array gives linear time. | Add an array-versus-map selection note. |
| E Expansion Plan 2 | Arithmetic and probability | Counts of two expansion moves are sufficient. Prefix counts and two coordinate reach inequalities answer each query. | Add prefix counts and Manhattan/Chebyshev reach conditions. |
| F Factory Table | Direct and constructive | Recover row identifiers from adjacent increases or row boundaries, then infer columns by division. | Add reverse-engineering a construction from adjacent differences. |
| G Git Gud | Direct and constructive | Batch a guaranteed strategy in residue and scale layers to meet the cost budget. | Add a worst-case accounting proof for a layered construction. |
| H Hyper Smawk Bros | Games | Track the previous forbidden move, characterize losing residues, and accelerate using the structure of the exceptional positions. | Add “previous move is state,” plus the finite game recurrence and invariant. |
| I Isaac's Queries | Data structures | Use prefix XOR and recover a binary trie of equivalence classes. LCA describes the highest differing bit. A greedy spanning tree controls query cost. | LCA and bit tricks exist. Add a short bitwise trie and Kruskal reminder as space allows. |
| J Jewels Building | Dynamic programming | An LCS-like two-prefix table with a mode bit captures when blocks can be consumed. Constant time transitions give `O(nm)`. | Add prefix DP, state sufficiency, and rolling rows. |
| K Keygen 3 | Direct and constructive | Transform small solutions to larger bitonic permutations while controlling cycle count. Use bounded enumeration for the small side. | Add cycle notation and lifting a verified base construction. |
| L LFS | Strings | A maximal-frequency substring has a one-character witness. Precompute character counts and successor changes, then inspect an alphabet-sized graph per query. | Keep prefix functions. Add next occurrence tables and “reduce to alphabet size.” |

## ICPC Europe Championship 2024

[Official EUC 2024 solutions](https://euc.icpc.global/wp-content/uploads/2024/03/EUC-Solutions.pdf)

| Problem | Primary family | Jury approach and reusable idea | KCLACTL lookup |
|---|---|---|---|
| A Grove | Enumeration | Memoize a reduced frontier and discretize radius values at distances where feasibility changes. Maximum clique on a compatibility graph is an alternative. | A concrete reason to retain one compact maximum-clique implementation. |
| B Charming Meals | Ordering and sweep | Reorder within the two threshold directions and try the split. Sorting and a dominance argument replace general matching. | Add sorted matching exchange proof. |
| C Annual Ants' Gathering | Graphs and trees | A move must preserve connected occupied vertices. Only a centroid can be the final vertex in the tree solution. Check each by DFS. | Keep centroid finding. A whole centroid decomposition is unnecessary for this task. |
| D Funny or Scary? | Direct and constructive | Build the color split around small connected components, exploiting a two-part structure. The jury's `O(n2^n)` subset checking technique is used for the output checker. | Add greedy graph construction and mask DP as distinct applications. |
| E Damage per Second | Arithmetic and probability | Use a continuous lower bound to prune candidate integers, then group equal ceiling quotients to price the remaining candidates. | Add quotient grouping and “lower bound before enumeration.” |
| F Dating | Data structures | Sort sets by size and try to build their laminar containment forest. A conflict produces the required witness. | Add laminar families and a last-owner map. A heavy/light incidence split is an alternative. |
| G Scooter | Graphs and trees | Remove the already placed items, then construct the route by a greedy elimination on the dependency structure. | Add a progress invariant for graph elimination. |
| H Division Avoidance | Direct and constructive | Replace cells with diagonal counts and prove a termination criterion. Sorting or bounded-key counting avoids long simulation. | A proof of compression matters more here than an instruction set optimization. |
| I Disks | Graphs and trees | Build the tangency graph. The radius perturbations must alternate signs and only a bipartite component with unequal sides can decrease their sum. | Keep integer geometry primitives. Add bipartite BFS coloring. |
| J Amanda the Amoeba | Graphs and trees | Connect the two shapes by a path and use rooted-tree traversal orders to maintain connectivity during deletion and addition. | Add graph construction by BFS parents and leaf deletion. |
| K Make Triangle | Ordering and sweep | Sort and use prefix sums to maintain necessary and sufficient group feasibility while assigning items. | Add the greedy completion invariant and scalar prefix sums. |

## ICPC Europe Championship 2025

[Official EUC 2025 solutions](https://euc.icpc.global/wp-content/uploads/2025/03/solutions.pdf)

| Problem | Primary family | Jury approach and reusable idea | KCLACTL lookup |
|---|---|---|---|
| A Condorcet Elections | Direct and constructive | A vote pair boosts exactly one comparison. Combine such independent gadgets for all required pairs. | Add “create a gadget whose side effects cancel.” |
| B Urban Planning | Direct and constructive | Place separated partially filled rectangles whose contributions sum to the required count. Bound the remainder before allocating space to the next region. | Add additive constructions and a residual bound. |
| C Ads | Ordering and sweep | Use shortest/longest choices with an ordered multiset. Exchange arguments justify size-three groups before smaller ones. | Standard multiset and exchange reasoning. Weighted matching would add unnecessary cost. |
| D Morse Code | Dynamic programming | Model prefix codes as a tree with different edge costs. Compress shape into counts at two levels and reconstruct from an `O(n³)` DP. | Add tree shape aggregation. Ordinary equal-cost Huffman does not model these edges. |
| E Porto Vs. Benfica | Graphs and trees | Use a BFS tree and replacement paths. Merge small sets into large ones with a lazy offset. A heap finalizes the remaining minimax distances. | Keep DSU and add small-to-large, subtree membership, and Dijkstra invariants. |
| F Mascot Naming | Strings | Greedily maintain the forbidden subsequence progress and merge required strings around each character. | Add the two-pointer subsequence test and greedy witness proof. |
| G A Very Long Hike | Graphs and trees | Use periodicity and a convex limiting shape. Reuse each source's distances, reduce the relevant sources, and exploit bounded integer edge weights with buckets. | Keep convex hull. Add distance batching and the bucket shortest-path option. |
| H Statues | Direct and constructive | Parity and the triangle inequality characterize feasibility. Build the points inductively in `O(n)`. | Add a Manhattan parity and feasible-interval proof. |
| I Pinball | Graphs and trees | Treat cell and direction as state and charge 0 or 1 for each transition. A shortest path gives the wall count, followed by reverse reconstruction. | Add 0–1 BFS and predecessor recovery. |
| J The Ultimate Wine Tasting Event | Direct and constructive | Derive necessary order and parity constraints on the two halves and prove they suffice by constructing a swap partition. | Add necessity/sufficiency and preserving relative order. |
| K Amusement Park Rides | Flow and SAT | Compress equal types into capacities, then add candidate times in order and maintain an augmenting path solution. Stop creating candidates that cannot help. | Keep residual flow code and document how to continue a feasible residual network. |

## ICPC Europe Championship 2026

[Official EUC 2026 solutions](https://euc.icpc.global/wp-content/uploads/2026/02/euc-2026-solutions.pdf)

| Problem | Primary family | Jury approach and reusable idea | KCLACTL lookup |
|---|---|---|---|
| A Three Circles | Geometry | Reduce to directed supporting lines. Precompute convexity checks for regions defined by pairs, then enumerate triples of lines. | Keep hull and orientation. Reuse sort order for repeated hulls. |
| B Bitwise Beach | Arithmetic and probability | Equal contributions cancel under XOR. Distinct positive gap sizes with total `n` number only `O(√n)`, so the remaining cross product is linear. | Add XOR cancellation and the distinct-values sum bound. |
| C Copy-paste | Graphs and trees | Work backward by bounded divisors and round down to the closest multiple. Explore the implicit states with a heap or memoized decreasing DAG. | Add state generation, bounding moves, and memoized DAG choice. |
| D Deque Sort | Data structures | Charge deletions to each original element once. Use segment tree searches for the first larger value and k-th live element in `O(n log n)`. | Keep segment tree and add guided descent. The present range-query API alone invites an extra logarithm. |
| E Evaluation | Dynamic programming | Aggregate all parse possibilities using counts and sums of partially completed terms. Four state values update per digit. | Add a linear aggregate state DP example. |
| F Fix the Coloring | Flow and SAT | Enumerate a vertex of the red clique and turn edge and nonedge conflicts into binary clauses. Solve the resulting 2-SAT instances. | Keep 2-SAT and SCC. Add clause modeling and the SCC proof. |
| G Good Permutations | Data structures | Descending blocks have constant `index + value`. Transform pair compatibility into range bounds and answer with RMQ or a segment tree. | Keep RMQ and segment tree. Add “derive one scalar per neighbor pair, query its extremum.” |
| H House | Dynamic programming | Binary search area, enumerate a tight plank constraint, then test candidates with a DP that stores the best pair of resource measures. | Add real answer search and state dominance. |
| I Palindromes | Strings | Palindromic prefixes imply periods of the whole palindrome. Combine compatible periods by gcd and repeatedly shrink the represented length. | Add the period lemma. The task's symbolic length reduction is beyond raw Manacher. |
| J Jewel Guards | Dynamic programming | Sweep active guard masks, sum over subsets, and apply a complement formula for coverage by two guards. Complexity `O(c log c + k2^k)`. | Keep the existing subset-sum transform idiom. Add the complement and counting proof. |
| K Multiset Variance | Geometry | Represent each distribution by its first and second moments, then optimize over their convex hull. Along an edge only a quadratic remains. | Keep convex hull, expectation and a stable quadratic note. |

## What earns space

- **Add short graph fundamentals.** State augmentation appears in Klompendans, Italian Data Centers, Pinball, and Copy-paste. Weighted shortest paths appear in Galaxy Quest, Kruidnoten, A Very Long Hike, and the heap phase of Porto Vs. Benfica. Add one adjacency convention and cover BFS, 0–1 BFS, Dijkstra, and parent recovery. [NWERC 2023 jury](https://2023.nwerc.eu/main/solutions.pdf) · [NWERC 2024 jury](https://2024.nwerc.eu/main/solutions.pdf) · [SWERC 2022–23 jury](https://swerc.eu/2022/problemset/solutions_swerc2022_2023.pdf) · [EUC 2025 jury](https://euc.icpc.global/wp-content/uploads/2025/03/solutions.pdf) · [EUC 2026 jury](https://euc.icpc.global/wp-content/uploads/2026/02/euc-2026-solutions.pdf)
- **Add decisions and proofs around the existing code.** Binary search, greedy exchanges, monotone stacks, amortized deletions, state compression, and prefix sums recur under different problem names. Good Permutations and Group Photo depend on the reduction to range queries or LIS. The existing listings are already suitable after that step. [NWERC 2024 jury](https://2024.nwerc.eu/main/solutions.pdf) · [NWERC 2025 jury](https://2025.nwerc.eu/solutions.pdf) · [EUC 2026 jury](https://euc.icpc.global/wp-content/uploads/2026/02/euc-2026-solutions.pdf)
- **Retain specialized code with a clear lookup advantage.** Biconnected components directly applies in Glued Grid. 2-SAT directly applies in Fix the Coloring. Residual flow helps Amusement Park Rides. Hull and robust orientation support multiple geometry reductions. Grove gives a concrete case for one maximum clique implementation. [NWERC 2024 jury](https://2024.nwerc.eu/main/solutions.pdf) · [EUC 2024 jury](https://euc.icpc.global/wp-content/uploads/2024/03/EUC-Solutions.pdf) · [EUC 2025 jury](https://euc.icpc.global/wp-content/uploads/2025/03/solutions.pdf) · [EUC 2026 jury](https://euc.icpc.global/wp-content/uploads/2026/02/euc-2026-solutions.pdf)
- **Treat specialized omissions as a second tier.** Add a linear basis, Li Chao tree, rollback connectivity diagram, or linear sieve with SPF only after packing the core. The sample directly supports the DSU successor, segment descent, subset DP, and shortest-path ideas. A weighted assignment template, a second Delaunay implementation, and link-cut trees need stronger team-specific evidence to justify taking their full space from those topics.
- **Use the archives as a training corpus.** Suggested short set: Klompendans for state expansion, Limited Library for a predicate proof, Flowing Fountain for amortization, Dutch Democracy for counting DP, Glued Grid for low links, Pinball for 0–1 BFS, Deque Sort for segment descent, and Fix the Coloring for clauses. Practice writing only the reduction and the API call first, then code the entire solution under the normal team workflow.

## Reference libraries

[cp-algorithms](https://cp-algorithms.com/) is useful for checking preconditions and alternative complexity bounds. Compare its treatments of [sparse Dijkstra](https://cp-algorithms.com/graph/dijkstra_sparse.html), [0–1 BFS](https://cp-algorithms.com/graph/01_bfs.html), [DSU with successor metadata](https://cp-algorithms.com/data_structures/disjoint_set_union.html), and [divide-and-conquer DP](https://cp-algorithms.com/dynamic_programming/divide-and-conquer-dp.html) with KCLACTL's snippet contracts. Keep the essential invariant and complexity in the printed copy.

[Algovault](https://github.com/sgtlaugh/algovault) is a useful comparison for source organization. Its templates describe API, limits, and complexity and have examples, differential tests, and judge-test links. Its broader index includes coordinate compression, shortest paths, range queries, and an XOR basis. KCLACTL can use the same approach to testing in the repository while keeping printed examples short. Presence in another library is evidence of availability, with contest relevance established by the problem sample and team practice.
