# Draft text for the printed appendix

This text occupies 122 listing lines, including blank rows, at a maximum width of 63 characters. It is a compact version of the [proof notes](06-proofs-and-tricks.md). The [layout results](05-space-and-runtime.md) report the scratch rendering. The larger explanation is useful when first studying a technique, while this version is for quick lookup in print.

```text
State graphs
Use a state for all history that affects legal next moves.
Examples: (cell,direction), (vertex,parity), (cell,last move).
Count states x transitions. Generate edges as needed.

Shortest paths
Unit edges: BFS layers give first discovery distances. Weights
0/1: relax and push 0 front, 1 back. Nonnegative: heap and skip
stale labels. The first unsettled vertex on a better path would
have a smaller label. DAG: relax in topological order. Keep
parents for reconstruction.

Binary search and greedy
First true: keep lo false and hi true until adjacent. Prove
monotonicity before searching. In sorted matching, pick the
least resource that fits. Swap its assignment with the larger
resource used by an optimum. The larger resource also fits what
used the smaller one.

Prefix, compression, and events
Sum [l,r) is pref[r]-pref[l]. Add to a range by adding at l,
subtracting at r, then taking prefixes. Compress for order.
Keep original gaps for lengths. In a sweep, account for the
previous state before changing events at this coordinate.

Monotone stack and successor sets
For next strictly greater, scan left to right and pop smaller
values, giving them the current index. Each pushes and pops
once. At each deletion, skip it forever. For DSU with size and
compression, keep the surviving successor as root data.

Doubling and rollback
When a vertex moves deeper in union by size, its component at
least doubles. With rollback log only changed fields and do not
compress. Restore k records in O(k). In small-to-large merges,
charge each moved record to a doubling container.

Segment tree search
For kth, require nonnegative counts. Go left if its sum >= k,
otherwise subtract the left sum and go right. For first value >
x, prune nonintersecting nodes and max <= x. Use ordered leaf
layout with a power-of-two base or explicit intervals.

DP state and knapsack
Write the cell meaning, base cases, and valid transitions.
Histories in one cell must have the same possible futures.
Count cells * transitions and bytes. Roll unused layers. 0-1
knapsack scans down, unbounded scans up. Boolean 0-1
reachability uses reach |= reach << w.

Mask DP and submasks
dp[mask][v] is a path with exactly mask ending at v. Remove v
to prove the recurrence. Boolean existence can use one end mask
per subset. Iterate submasks with s=(s-1)&mask, including 0
once. All masks give 3^n pairs: bit absent, mask-only, or both.

Trees and parity
XOR mark both endpoints of each extra edge. A subtree XOR
counts edges crossing its cut mod 2. A closed tour crosses
every cut an even number of times. A light HLD child is at most
half its parent. Every centroid child component is at most
half.

Low links and 2-SAT
Tree edge u-v is a bridge iff low[v]>tin[u]. Nonroot u cuts off
child v iff low[v]>=tin[u]. Root needs two children. Skip
parent by edge ID. Clause a|b yields !a->b and !b->a. A
variable in the same SCC as its negation makes it impossible.

Kruskal and residual cuts
A minimum edge crossing a cut respecting chosen edges is safe.
Add it to an MST, remove a crossing edge from the new cycle. In
a residual graph after max flow, let S be reached from s. Every
forward cut edge is full and reverse flow across it is 0.

Expectations and conditioning
E[sum indicators]=sum probabilities, with or without
independence. In a sorted list of independent options, first
success i has probability p[i]*product(1-p[j], j<i). Divide by
P(any success) only when the answer conditions on it.

Exact geometry
Sign of cross(b-a,c-a) gives orientation. Widen before
subtracting or multiplying. Shoelace is the sum of signed
origin triangle areas. Internal edges cancel. Manhattan
distance is max of |dx+dy| and |dx-dy|.

Integer arithmetic and parity
For b>0, floor(a/b) is q-(r<0), ceil is q+(r>0). When q=n/l>0,
floor(n/i)=q until i=n/q. Cancel a gcd before multiplying. A
permutation's parity is (n-number of cycles) mod 2. C(n,k) is
odd iff k is a bit-subset of n.

Strings
Use Z or prefix function with a delimiter outside the alphabet.
Longest common substring: maximum LCP among adjacent suffixes
from different strings. A shared prefix occupies one interval,
so if both sources appear there, some adjacent pair differs.

Constructions and debugging
First prove necessary conditions, then build a witness. Fix a
suffix or choose an extreme and reduce. Check length 0/1, ties,
disconnected cases, one large value and the memory budget.
Compare tiny random cases against an independent brute force.

DP optimization
D&C row: prove nondecreasing argmins. Solve the midpoint, then
restrict each side by its argmin. Knuth: require
opt(i,j-1)<=opt(i,j)<=opt(i+1,j). Search only that window.
State ties and prove the condition for the cost formula.

Divisibility and repetition
Modular inverse exists iff gcd(a,m)=1. In a functional graph
repeated jumps eventually cycle. Compose transformations by
squaring. For repeated index maps, lift states or simplify the
formula before simulating.

Period and palindrome
Two reflections, in a palindromic prefix of length b and in the
whole palindrome of length a, imply period a-b. Two periods r,t
with length >= r+t imply gcd(r,t): use one step of each size to
obtain period |r-t|, then repeat.
```

