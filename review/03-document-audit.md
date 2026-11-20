# Mathematical content, proofs, and reference quality

**Review date:** 2026-11-19  
**Scope:** Handwritten formulas and theorem descriptions in the PDF, plus the amount of proof and “when to use it” guidance that fits in the current 25-page document.

## Confirmed text/formula defects

### Bernoulli power-sum formula has a variable typo

[content/combinatorial/chapter.tex](/Users/kutay/code/kclactl/content/combinatorial/chapter.tex:50) writes

`sum_{i=1}^n n^m = ...`

The summand must be `i^m`. For integer `m>=1` the right side is the Faulhaber polynomial for `1^m + ... + n^m` under the stated `B_1=-1/2` convention. Give `m=0` separately as `n`.

### The unsigned first-kind Stirling row is wrong

[content/combinatorial/chapter.tex](/Users/kutay/code/kclactl/content/combinatorial/chapter.tex:65) gives ten values for `c(8,k)`, although `k=0..8` has nine entries. The correct unsigned row in increasing `k` order is

`0, 5040, 13068, 13132, 6769, 1960, 322, 28, 1`.

The current leading `8, 0` shifts all entries and conflicts with the recurrence and generating function printed immediately above it.

### Bézout statement is malformed

[content/number-theory/chapter.tex](/Users/kutay/code/kclactl/content/number-theory/chapter.tex:22) prints `a \neq , b \neq 0`; the first comparison is missing its value. More precisely, the needed condition is that `a` and `b` are not both zero. The identity itself and the stated family of solutions are standard once a particular solution is known.

### Eulerian number statistics need separate definitions

The recurrence counts permutations with `k` descents, defined by `π(j) > π(j+1)`. The number of ascents and the number of strict excedances have the same distribution as descents. The number of weak excedances has the distribution of descents plus one. This is a statement about counts over all permutations. An individual permutation can have different values for these statistics. [Combinatorial chapter](../content/combinatorial/chapter.tex#L68)

### Fermat's little theorem needs a coprimality condition

The formula `a^(p-1) ≡ 1 (mod p)` requires `p ∤ a`. For `a=p` the left side is 0. The version valid for all integer `a` is `a^p ≡ a (mod p)`. [phiFunction.h](../content/number-theory/phiFunction.h#L15)

### The Markov limit matrix has the wrong orientation

The chapter defines `p_ij = Pr(X_next=i | X_now=j)`, so `P` is column stochastic and distributions are column vectors. If a finite irreducible aperiodic chain converges to `π`, the limit of `P^k` is `π 1ᵀ`, with `π` in every column. The current `1 π` reverses the order. Also, convergence to the same distribution from every start alone permits reducible examples with a unique accessible absorbing state. For expected absorption time give the boundary `t_i=0` on absorbing states, and use the displayed recurrence on transient states. [Math chapter](../content/math/chapter.tex#L153)

### Quadrilateral identity needs a domain caveat

The term `F tan(theta)` is undefined for perpendicular diagonals. A square gives `F=0` and `theta=π/2`, while the cross product formula remains valid. With an unoriented choice of angle, the sign convention for `F` also needs care. The square root or `2ef sin(theta)` expression is enough for the area of a convex quadrilateral. [Math chapter](../content/math/chapter.tex#L56)

### Directed matrix-tree root orientation is unspecified

This Laplacian decrements `mat[a][b]` for `a→b` and increments `mat[b][b]`. Deleting root `i` counts spanning arborescences whose edges point away from `i`. A two-vertex graph `0→1` gives minor 1 for root 0 and minor 0 for root 1. Specify that convention beside the formula. [Graph chapter](../content/graph/chapter.tex#L52)

## Formula audit notes

- The triangle median, angle-bisector, inradius/circumradius, sine/cosine-law formulas were algebraically checked and are consistent with the displayed side labels.
- The quadrilateral area identity `4A = sqrt(4e^2 f^2 - F^2)` is consistent with the stated `F`; only the chained `F tan(theta)` expression needs the domain caveat above.
- The geometric and first four power sums, Bernoulli signs, displayed Taylor coefficients, binomial distribution, and expectation and variance identities are consistent under their ordinary domains.
- A geometric waiting time has finite mean as stated for `0<p<=1`. At `p=0` success never occurs. Show `p>0` next to the formula. The transition matrix recurrence assumes a time homogeneous chain. The stationary degree distribution holds for connected undirected walks even if periodic. Aperiodicity is used for convergence.
- Give `p(n)=0` for negative `n` in the pentagonal recurrence, `D(0)=1` separately from the nearest-integer derangement formula, and the index range `0..n` on the Catalan convolution. State that Cramer's rule requires a nonzero determinant. The infinite Euler–Maclaurin expansion needs smoothness, decay and a remainder or an asymptotic interpretation. It is unsafe to use as a universally convergent identity. [Math](../content/math/chapter.tex) · [Combinatorial](../content/combinatorial/chapter.tex)
- `feenableexcept(29)` is a GNU environment trick. The bits select numeric exceptions, including overflow and underflow on the corresponding x86 setup. They do not trap every occurrence of infinity or every denormal operand. The vectorization and floating point pragmas should sit behind explicit compiler and CPU assumptions. [Various chapter](../content/various/chapter.tex#L21)

## Proofs and contest-use guidance

The handbook is intentionally a compact reference rather than a textbook. Its code headers usually give API, complexity, source, and status, but the PDF contains few correctness proofs or reminders of the key invariant. `content/appendix/techniques.txt` is a long topic checklist, not an explanation of those topics. The checked-in `doc/modmul-proof.tex` is not imported into the PDF. `GameTheory.tex` is a useful exception: it states normal-play assumptions, Sprague–Grundy recurrence, Nim xor strategy, and the retrograde queue rule for cyclic state graphs.

The highest-value additions are short proof/reduction cards that explain how to recognize and trust an approach, not full formal proofs for every code listing:

1. **Binary search on an answer:** state the monotone predicate and maintain one feasible and one infeasible endpoint; complexity is predicate cost times `log(range)`.
2. **Greedy by sorting:** record the exchange step that swaps an optimal solution into agreement with the greedy choice. NWERC examples repeatedly use sorted matching and feasibility checks.
3. **BFS/Dijkstra:** name the state graph and why unit/nonnegative edge weights make the queue/heap finalization valid; include 0–1 BFS as the small-weight special case.
4. **Subset DP:** name the state, transition, and memory as well as time (`O(n 2^n)` storage may be the actual limit); cite the often-used state-expanded BFS pattern.
5. **DSU and small-to-large:** distinguish amortized `O(alpha(n))` DSU operations from the simpler doubling proof for moving elements (`O(log n)` moves per element). Do not call DSU operations worst-case constant.
6. **DP optimizations:** state the required monotone-optimum/quadrangle or Monge condition beside divide-and-conquer and Knuth DP, and warn that the condition must be proved for the cost function.
7. **Tree invariants:** centroid components are at most half the tree; parity/subtree aggregation can replace repeated path simulation.

The [proposed appendix text](06-proofs-and-tricks.md) expands these into small proofs, examples, and conditions. The [space proposal](05-space-and-runtime.md) budgets room for them. See [divide-and-conquer DP](https://cp-algorithms.com/dynamic_programming/divide-and-conquer-dp.html) and [DSU](https://cp-algorithms.com/data_structures/disjoint_set_union.html) for the respective preconditions and the amortized bound.

## Source/selection consistency

The two matching templates cover different domains. `WeightedMatching` is rectangular weighted **bipartite** assignment, and `GeneralMatching` is unweighted general matching. The README's exclusion of general weighted matching is consistent with those imports. The README misspells `doc/scripts/skip_headers` as `docs/scripts/skip_headers`. Its copy-and-paste guidance would benefit from a sentence explaining that listings use the common contest template and their printed dependencies. [README](../README.md#L43) · [Matching chapter](../content/graph/chapter.tex#L17)
