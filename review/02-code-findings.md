# Source code findings

The [header inventory](07-header-inventory.md) records all 145 files and includes API and complexity notes. The [verification record](01-verification.md) gives the test environment and counterexample results.

## Highest priority for the printed reference

| Listing | What fails | Recommended resolution |
|---|---|---|
| [LazySegmentTree](../content/data-structures/LazySegmentTree.h#L17) | Starting from `[1,2]`, `set(0,2,1e9)` then `query(0,1)` returned `1`. `mset=1e9` doubles as “no pending assignment,” including when an add lands on that value. The disjoint result `-1e9` masks smaller values. HLD inherits these bounds. | Use a separate assignment flag and a valid maximum identity. State the bounds on values and accumulated updates. |
| [SuffixTree](../content/strings/SuffixTree.h#L17) | The LCS helper inserts two separators that index columns 26 and 27 of a 26 column table. UBSan caught index 26. `LCS` also allocates a 24,001,256 byte object on the stack locally. Setup initializes tables at fixed capacity even for short inputs. | Use suffix array and LCP or suffix automaton for longest common substring. If retaining Ukkonen, make alphabet mapping, storage placement, and combined length limit explicit. |
| [BumpAllocator](../content/various/BumpAllocator.h#L13) | The global `new` returns the next byte address without alignment. Allocations of 16, 1, and 16 bytes produced addresses with residues 8, 7, and 7 modulo 16 on a platform with 16 byte fundamental alignment. Exhaustion can wrap with assertions disabled. GCC warns about the sized deallocation pairing. | Use contiguous nodes addressed by index. Keep a general arena only if it handles alignment, exhaustion, and lifecycle deliberately. |
| [MillerRabin](../content/number-theory/MillerRabin.h#L7) and [Factor](../content/number-theory/Factor.h#L54) | With `LDBL_MANT_DIG=53`, the library rejected prime `754221686909783899` while an exact 128-bit modular implementation accepted it. A call to `factor` on the same prime timed out. The `ModMulLL` source documents the architecture assumption in `Details`, which the preprocessor leaves out of the PDF. | Print exact GNU `__uint128_t` multiplication as the default for 64-bit arithmetic. Keep the reciprocal optimization only with its target restriction visible and after measuring it there. |
| [ModSum](../content/number-theory/ModSum.h#L19) | `modsum(6,5,m-1,m)` for `m=4000000000000000000` should sum `5+4+3+2+1+0=15`. It returned `3106511852580896783`. `to*k+c` wraps before division. Signed modular normalization can separately overflow at large moduli. | Widen the numerator before division and state the input and output bounds. Replace the test's unrelated average assertion with an exact oracle. |
| [PolyRoots](../content/numerical/PolyRoots.h#L13) | `-x²` on `[-1,1]` returned no roots. The sign change search misses this repeated root. The linear case returned `10` for `x-10` on `[-1,1]`. Degree zero can reach `pop_back()` on an empty vector. | Remove from the printed set or define and test interval, multiplicity, degree, and error semantics. At each degree `d` it may test `O(d)` intervals with `O(d)` Horner evaluation. Over the derivative chain this gives `O(n³ I)` for `I` bisection steps. |
| [Simplex](../content/numerical/Simplex.h#L52) | On the feasible example below the unchanged solver timed out. A scratch trace found the same basis, variable order, and tableau again after 12 pivots in phase 1. Most negative reduced cost with index tie breaking permits cycling. | Take it out of the handout pending a rule that guarantees progress, or repair and verify before relying on it. [Analysis of simplex cycles](https://pubsonline.informs.org/doi/abs/10.1287/opre.1070.0474) |
| [NumberTheoreticTransform](../content/numerical/NumberTheoreticTransform.h#L19) | The standalone header includes `ModPow.h` and redeclares `mod`. The stress fixture supplies a compatible local exponentiation function. The convolution also pads to the next **strictly greater** power of two. Output length 2²³ requests a transform of length 2²⁴, which 998244353 cannot support. Smaller exact powers of two incur twice the transform buffer size. | Share one modulus definition, print the paste instructions, and pad to the least power of two at least as large as the result. Verify the maximum supported size and length 1. |

Simplex counterexample in the API's `Ax <= b` convention, with `x >= 0`.

```text
A = [[0.5, -5.5, -2.5, 9], [0.5, -1.5, -0.5, 1], [1, 0, 0, 0]]
b = [0, 0, 1]
c = [10, -57, -9, -24]
```

The point `[1,0,1,0]` is feasible and has objective 1. The solver should terminate on this finite LP.

## Contracts with concrete edge cases

| Listing | Boundary or requirement |
|---|---|
| [FastInput](../content/various/FastInput.h#L23) | The ASCII offset accumulator overflows on `2147483647` under UBSan. A call at EOF spins in the skip loop. Prefer the normal fast iostream template or spell out the supported digit count, signed range, and EOF contract. |
| [SuffixArray](../content/strings/SuffixArray.h#L22) | A string containing byte 128 indexes the count table negatively when `char` is signed. The GNU bounds check reproduced it. Map bytes through `unsigned char` and reserve 0, or state the symbol range `[1,lim)`. |
| [Point](../content/geometry/Point.h#L23) and [Point3D](../content/geometry/Point3D.h#L37) | Integer vector normalization truncates the norm before division, and integer rotation truncates coordinates. For example `Point<long long>(1,1).unit()` returns `(1,1)`. Use floating types for these operations and a nonzero vector or axis. Bound integer dot and cross products before computing them. |
| [Angle](../content/geometry/Angle.h#L48) | `angleDiff(Angle(50000,0),Angle(50000,0))` overflows `int` under UBSan. The ordering operator widens its products and the composition functions still need their own bounds. |
| [FenwickTree](../content/data-structures/FenwickTree.h#L24) | Order search needs nonnegative point frequencies. The sum of all jumps starting at `1<<25` is `2^26-1`, so for `n>=2^26` some results, including the absent sentinel `n`, cannot be returned. |
| [FracBinarySearch](../content/number-theory/FracBinarySearch.h#L9) | The example tests `p>=3*q` over `[0,1]` and fails `assert(f(hi))`. For the stated answer `1/3` the example needs `3*p>=q`, with wide cross products as needed. |
| [ContinuedFractions](../content/number-theory/ContinuedFractions.h#L6) | `approximate(3.5,4)` correctly returns a closest fraction `3/1`, error 0.5, exceeding the printed bound 0.25. A simultaneous numerator limit can defeat the familiar denominator-only bound. |
| [ModInverse](../content/number-theory/ModInverse.h#L12) | Forms a pointer one before a new array, which C++ pointer arithmetic does not allow. The existing test exceeds `LIM<=mod` and had an actual read before the allocation under ASan. Ordinary indices 1 through `LIM-1` in a vector of size `LIM` are sufficient for the valid domain. |
| [ModSqrt](../content/number-theory/ModSqrt.h#L12) | The declared include defines a two argument power function and the code calls a three argument one. The PDF lists `ModMulLL` earlier and the test supplies its own overload. State the dependency, odd prime and quadratic residue inputs, and the bound for direct signed products inside the loop. A search for a nonresidue adds its own cost. |
| [multinomial](../content/combinatorial/multinomial.h#L12) | `{31,31}` gives `465428353255261088`. UBSan caught an overflowing intermediate product despite that result fitting. Cancel factors or multiply in a wider type. |
| [IntPerm](../content/combinatorial/IntPerm.h#L11) | The signed rank supports the full range of lengths through 12. `13!-1` exceeds `INT_MAX`. The domain is a permutation of `0..n-1`. |
| [CompressTree](../content/graph/CompressTree.h#L19) | Empty subsets reach `li[0]`. The first call may initialize `O(V)` scratch space. Later queries on the same tree have subset-dependent cost. |
| [DivideAndConquerDP](../content/various/DivideAndConquerDP.h#L15) | The skeleton assumes application globals and narrows the `ll` cost through `pii`. Use a wide result and define what an empty candidate interval means. |
| [BumpAllocatorSTL](../content/various/BumpAllocatorSTL.h#L12) and [SmallPtr](../content/various/SmallPtr.h#L14) | The STL arena base is aligned to 16 bytes and has no exhaustion check. Offsets alone cannot align types requiring more than the base guarantees. `SmallPtr` needs an object in the arena or null. |
| [EulerWalk](../content/graph/EulerWalk.h#L6) | An open trail can end away from `src`. The printed endpoint wording describes circuits only. Flow snippets also assume distinct source and sink and bounded totals. |
| [Eratosthenes](../content/number-theory/Eratosthenes.h#L12) | This repository-only sieve advertises a 100,000,000 example with a bitset of 5,000,000 positions. Calls with `lim>5,000,000` index beyond its size. The printed segmented sieve is a different implementation. |
| [SIMD](../content/various/SIMD.h#L51) | The repository-only dot product example zero extends signed 32-bit lanes. By inspection, for 16 copies of `a=-1,b=1` it differs from the scalar result `-16` by `8·2^32`. ARM compilation separately rejects its x86 directive. |

## Corrections to complexity annotations

| Listing | Bound to use in a solution |
|---|---|
| [UnionFind](../content/data-structures/UnionFind.h#L7) and [UnionFindRollback](../content/data-structures/UnionFindRollback.h#L20) | DSU with path compression and size has amortized `O(α(n))` operations. Rollback DSU find and join take `O(log n)` plus amortized record appends. Restoring `k` entries takes `O(k)`. |
| [LineContainer](../content/data-structures/LineContainer.h#L30) and [Treap](../content/data-structures/Treap.h#L27) | A hull insertion can erase many obsolete lines in a single call. Its insertion bound is amortized. Treap split and merge take expected `O(log n)` with linear worst case. |
| [MoQueries](../content/data-structures/MoQueries.h#L9) | For block size `B`, include `O(Q log Q)` sorting, `O(QB + N²/B + N)` endpoint moves, and the cost of updating and answering. Tune 350 to the problem. |
| [IntervalContainer](../content/various/IntervalContainer.h#L13) | An update erasing `k` intervals costs `O(log n+k)`. Starting empty, each update creates at most two intervals, so total erasures over the sequence are linear in the number of updates. Avoid mutating a `set` key through a cast, especially if adapting the comparator. |
| [ConstantIntervals](../content/various/ConstantIntervals.h#L8) | Use `O(k(1+log(n/k)))` for `k>0` runs, assuming constant function and callback cost. The additive term covers the `k=n` case. |
| [PolygonUnion](../content/geometry/PolygonUnion.h#L36) | For `N` total vertices, the pair scan costs `O(N²)`. Sorting per-edge events adds `O(Σ K_e log(K_e+1))`, with worst case upper bound `O(N² log N)` overall. Rectangle union has a separate `O(N log N)` routine. |
| [kdTree](../content/geometry/kdTree.h#L35) and [3dHull](../content/geometry/3dHull.h#L31) | Sorting at every KD split gives `O(n log² n)` preprocessing. Nearest queries can take `O(n)`. The 3D hull uses `O(n²)` space for its edge table. |
| [IntDeterminant](../content/numerical/IntDeterminant.h#L16) | Euclidean steps yield an `O(n³ log M)` bound with modulus `M` and normalized entries. The cubic annotation absorbs the factor for a fixed modulus. |
| [MaximalCliques](../content/graph/MaximalCliques.h#L24) | The first set bit determines the pivot and the loop scans all vertices. The published `O(3^(n/3))` algorithm uses a particular pivot and output strategy. Counting possible maximal cliques alone does not bound this implementation's search. [The Tomita, Tanaka and Takahashi analysis](https://snap.stanford.edu/class/cs224w-readings/tomita06cliques.pdf) |
| [Dinic](../content/graph/Dinic.h#L25) | The printed scaling bound needs justification for this implementation. BFS thresholds by capacity but DFS can send flow on smaller residual edges. The standard scaling proof that charges a minimum increment to every augmentation needs a corresponding DFS restriction. The generic and unit network bounds have separate proofs. [Dinic analysis](https://cp-algorithms.com/graph/dinic.html) |

## Snippet composition and stack

- The PDF removes most includes and prints dependencies as text. Many snippets define short globals such as `Node`, `Tree`, `P`, `mod`, and `inf`. Build the chosen combination with the contest template and rename conflicting symbols. Examples include `LazySegmentTree` with a treap, `BellmanFord` with `FloydWarshall`, and `ModularArithmetic` with `ModPow`.
- The `MoQueries` listing defines two versions of the macro `K` and contains placeholder callbacks. Its test includes a local copy of the algorithms. The `SolveLinear2` fixture also exercises a separate implementation. Individual compile exemptions are in the [verification record](01-verification.md).
- The full 2-SAT stress case timed out at the recursive solve on the local default stack and passed on a 128 MiB thread stack. SCC, bridges, centroid preprocessing, HLD, and LCA can also recurse deeply on a path. A logarithmic number of centroid decomposition levels does not bound the DFS call stack. The NWERC 2026 document sets a 2 GiB total judge sandbox limit for C++ and describes C++ stack and heap limits in terms of that budget. [2sat.h](../content/graph/2sat.h#L57) · [CentroidDecomposition.h](../content/graph/CentroidDecomposition.h#L21) · [NWERC 2026 systems](https://2026.nwerc.eu/system)
- An empty interval can be considered by `IntervalCover` without changing the endpoint. The loop consumes all eligible candidates, and the next iteration returns failure if nothing can advance coverage. An empty successful target and failure share the empty vector result by design. [IntervalCover.h](../content/various/IntervalCover.h#L19)
