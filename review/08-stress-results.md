# Stress test data

Snapshot `54ec932`, local GCC 16.1 C++17 at `-O2`, Darwin arm64. Each duration excludes compilation. Four tests could execute concurrently. See the [verification record](01-verification.md) for the native run and qualified reruns.

| Topic | Pass | Compile failure | Assertion | Timeout | Skip |
|---|---:|---:|---:|---:|---:|
| data-structures | 9 | 0 | 0 | 0 | 0 |
| geometry | 18 | 2 | 0 | 0 | 0 |
| graph | 19 | 0 | 0 | 1 | 0 |
| number-theory | 8 | 0 | 2 | 1 | 1 |
| numerical | 11 | 0 | 0 | 0 | 0 |
| strings | 7 | 0 | 0 | 0 | 0 |
| various | 5 | 0 | 0 | 0 | 0 |
| **Total** | **77** | **2** | **2** | **2** | **1** |

| Existing test | Native result | Runtime (s) | Follow-up or fixture note |
|---|---|---:|---|
| [data-structures/FenwickTree.cpp](../stress-tests/data-structures/FenwickTree.cpp) | Pass | 0.019 | — |
| [data-structures/FenwickTree2d.cpp](../stress-tests/data-structures/FenwickTree2d.cpp) | Pass | 3.521 | — |
| [data-structures/LazySegmentTree.cpp](../stress-tests/data-structures/LazySegmentTree.cpp) | Pass | 0.047 | — |
| [data-structures/LineContainer.cpp](../stress-tests/data-structures/LineContainer.cpp) | Pass | 0.559 | — |
| [data-structures/MoQueries.cpp](../stress-tests/data-structures/MoQueries.cpp) | Pass | 0.232 | Locally copied variants in this fixture |
| [data-structures/PersistentSegmentTree.cpp](../stress-tests/data-structures/PersistentSegmentTree.cpp) | Pass | 0.026 | — |
| [data-structures/RMQ.cpp](../stress-tests/data-structures/RMQ.cpp) | Pass | 0.012 | — |
| [data-structures/SegmentTree.cpp](../stress-tests/data-structures/SegmentTree.cpp) | Pass | 0.437 | — |
| [data-structures/Treap.cpp](../stress-tests/data-structures/Treap.cpp) | Pass | 0.013 | — |
| [geometry/CircleIntersection.cpp](../stress-tests/geometry/CircleIntersection.cpp) | Pass | 0.269 | — |
| [geometry/CircleLine.cpp](../stress-tests/geometry/CircleLine.cpp) | Pass | 0.013 | — |
| [geometry/CirclePolygon.cpp](../stress-tests/geometry/CirclePolygon.cpp) | Pass | 0.342 | — |
| [geometry/CircleTangents.cpp](../stress-tests/geometry/CircleTangents.cpp) | Pass | 0.083 | — |
| [geometry/ClosestPair.cpp](../stress-tests/geometry/ClosestPair.cpp) | Pass | 1.486 | — |
| [geometry/ConvexHull.cpp](../stress-tests/geometry/ConvexHull.cpp) | Pass | 0.744 | — |
| [geometry/DelaunayTriangulation.cpp](../stress-tests/geometry/DelaunayTriangulation.cpp) | Compile failure | — | Passed with the GNU trap helper stubbed |
| [geometry/FastDelaunay.cpp](../stress-tests/geometry/FastDelaunay.cpp) | Compile failure | — | Passed with the GNU trap helper stubbed |
| [geometry/HullDiameter.cpp](../stress-tests/geometry/HullDiameter.cpp) | Pass | 0.239 | — |
| [geometry/insidePolygon.cpp](../stress-tests/geometry/insidePolygon.cpp) | Pass | 0.412 | — |
| [geometry/LineHullIntersection.cpp](../stress-tests/geometry/LineHullIntersection.cpp) | Pass | 0.414 | — |
| [geometry/LineIntersection.cpp](../stress-tests/geometry/LineIntersection.cpp) | Pass | 0.043 | — |
| [geometry/LineProjectionReflection.cpp](../stress-tests/geometry/LineProjectionReflection.cpp) | Pass | 0.011 | — |
| [geometry/ManhattanMST.cpp](../stress-tests/geometry/ManhattanMST.cpp) | Pass | 0.628 | — |
| [geometry/MinimumEnclosingCircle.cpp](../stress-tests/geometry/MinimumEnclosingCircle.cpp) | Pass | 2.550 | — |
| [geometry/PointInsideHull.cpp](../stress-tests/geometry/PointInsideHull.cpp) | Pass | 0.104 | — |
| [geometry/PolygonArea.cpp](../stress-tests/geometry/PolygonArea.cpp) | Pass | 0.010 | — |
| [geometry/PolygonCut.cpp](../stress-tests/geometry/PolygonCut.cpp) | Pass | 0.394 | — |
| [geometry/PolygonUnion.cpp](../stress-tests/geometry/PolygonUnion.cpp) | Pass | 0.042 | — |
| [geometry/SegmentIntersection.cpp](../stress-tests/geometry/SegmentIntersection.cpp) | Pass | 0.089 | — |
| [graph/2sat.cpp](../stress-tests/graph/2sat.cpp) | Timed out | 90.006 | Passed with a 128 MiB thread stack |
| [graph/CentroidDecomposition.cpp](../stress-tests/graph/CentroidDecomposition.cpp) | Pass | 0.336 | — |
| [graph/DirectedMST.cpp](../stress-tests/graph/DirectedMST.cpp) | Pass | 0.235 | — |
| [graph/EdgeColoring.cpp](../stress-tests/graph/EdgeColoring.cpp) | Pass | 0.451 | — |
| [graph/erdos-gallai.cpp](../stress-tests/graph/erdos-gallai.cpp) | Pass | 0.019 | — |
| [graph/EulerWalk.cpp](../stress-tests/graph/EulerWalk.cpp) | Pass | 0.069 | — |
| [graph/GeneralMatching.cpp](../stress-tests/graph/GeneralMatching.cpp) | Pass | 1.925 | — |
| [graph/GomoryHu.cpp](../stress-tests/graph/GomoryHu.cpp) | Pass | 0.281 | — |
| [graph/HLD.cpp](../stress-tests/graph/HLD.cpp) | Pass | 0.776 | — |
| [graph/LCA.cpp](../stress-tests/graph/LCA.cpp) | Pass | 0.019 | — |
| [graph/LinkCutTree.cpp](../stress-tests/graph/LinkCutTree.cpp) | Pass | 0.842 | — |
| [graph/matrix-tree.cpp](../stress-tests/graph/matrix-tree.cpp) | Pass | 0.009 | — |
| [graph/maxflow.cpp](../stress-tests/graph/maxflow.cpp) | Pass | 1.659 | — |
| [graph/MaximalCliques.cpp](../stress-tests/graph/MaximalCliques.cpp) | Pass | 0.023 | — |
| [graph/MaximumClique.cpp](../stress-tests/graph/MaximumClique.cpp) | Pass | 1.216 | — |
| [graph/MinCostMaxFlow.cpp](../stress-tests/graph/MinCostMaxFlow.cpp) | Pass | 1.436 | — |
| [graph/MinimumVertexCover.cpp](../stress-tests/graph/MinimumVertexCover.cpp) | Pass | 0.701 | — |
| [graph/SCC.cpp](../stress-tests/graph/SCC.cpp) | Pass | 0.032 | — |
| [graph/TopoSort.cpp](../stress-tests/graph/TopoSort.cpp) | Pass | 0.092 | — |
| [graph/WeightedMatching.cpp](../stress-tests/graph/WeightedMatching.cpp) | Pass | 0.164 | — |
| [number-theory/ContinuedFractions.cpp](../stress-tests/number-theory/ContinuedFractions.cpp) | Pass | 4.408 | — |
| [number-theory/CRT.cpp](../stress-tests/number-theory/CRT.cpp) | Pass | 0.932 | — |
| [number-theory/Eratosthenes.cpp](../stress-tests/number-theory/Eratosthenes.cpp) | Pass | 0.019 | — |
| [number-theory/Factor.cpp](../stress-tests/number-theory/Factor.cpp) | Timed out | 90.003 | Also reproduced on the primality counterexample |
| [number-theory/FracBinarySearch.cpp](../stress-tests/number-theory/FracBinarySearch.cpp) | Pass | 4.259 | — |
| [number-theory/MillerRabin.cpp](../stress-tests/number-theory/MillerRabin.cpp) | Asserted | 0.106 | Prime 754221686909783899 rejected on this host |
| [number-theory/ModInverse.cpp](../stress-tests/number-theory/ModInverse.cpp) | Pass | 0.010 | Targeted ASan rerun reproduced a read before the allocation |
| [number-theory/ModLog.cpp](../stress-tests/number-theory/ModLog.cpp) | Pass | 0.090 | — |
| [number-theory/ModMulLL.cpp](../stress-tests/number-theory/ModMulLL.cpp) | Explicit skip | 0.009 | 53-bit `long double` significand |
| [number-theory/ModSqrt.cpp](../stress-tests/number-theory/ModSqrt.cpp) | Pass | 0.550 | — |
| [number-theory/ModSum.cpp](../stress-tests/number-theory/ModSum.cpp) | Asserted | 0.085 | Exact oracle agreed at the failing average assertion |
| [number-theory/ModularArithmetic.cpp](../stress-tests/number-theory/ModularArithmetic.cpp) | Pass | 0.009 | — |
| [numerical/BerlekampMassey.cpp](../stress-tests/numerical/BerlekampMassey.cpp) | Pass | 0.094 | — |
| [numerical/FastFourierTransform.cpp](../stress-tests/numerical/FastFourierTransform.cpp) | Pass | 0.009 | — |
| [numerical/FastFourierTransformMod.cpp](../stress-tests/numerical/FastFourierTransformMod.cpp) | Pass | 0.041 | — |
| [numerical/FastSubsetTransform.cpp](../stress-tests/numerical/FastSubsetTransform.cpp) | Pass | 0.009 | — |
| [numerical/IntDeterminant.cpp](../stress-tests/numerical/IntDeterminant.cpp) | Pass | 1.846 | Locally copied variant |
| [numerical/LinearRecurrence.cpp](../stress-tests/numerical/LinearRecurrence.cpp) | Pass | 13.142 | — |
| [numerical/NumberTheoreticTransform.cpp](../stress-tests/numerical/NumberTheoreticTransform.cpp) | Pass | 0.111 | — |
| [numerical/SolveLinear.cpp](../stress-tests/numerical/SolveLinear.cpp) | Pass | 0.339 | Integer modular variant in the fixture |
| [numerical/SolveLinear2.cpp](../stress-tests/numerical/SolveLinear2.cpp) | Pass | 0.223 | Separate elimination function |
| [numerical/SolveLinearBinary.cpp](../stress-tests/numerical/SolveLinearBinary.cpp) | Pass | 0.415 | Locally copied variant with five-bit rows |
| [numerical/Tridiagonal.cpp](../stress-tests/numerical/Tridiagonal.cpp) | Pass | 4.541 | Locally copied variants |
| [strings/AhoCorasick.cpp](../stress-tests/strings/AhoCorasick.cpp) | Pass | 0.388 | — |
| [strings/Hashing-codeforces.cpp](../stress-tests/strings/Hashing-codeforces.cpp) | Pass | 0.028 | — |
| [strings/Hashing.cpp](../stress-tests/strings/Hashing.cpp) | Pass | 0.026 | — |
| [strings/KMP.cpp](../stress-tests/strings/KMP.cpp) | Pass | 0.222 | — |
| [strings/MinRotation.cpp](../stress-tests/strings/MinRotation.cpp) | Pass | 0.373 | — |
| [strings/SuffixArray.cpp](../stress-tests/strings/SuffixArray.cpp) | Pass | 1.467 | — |
| [strings/Zfunc.cpp](../stress-tests/strings/Zfunc.cpp) | Pass | 0.158 | — |
| [various/FastInput.cpp](../stress-tests/various/FastInput.cpp) | Pass | 0.014 | Locally copied reader in this fixture |
| [various/FastKnapsack.cpp](../stress-tests/various/FastKnapsack.cpp) | Pass | 0.289 | — |
| [various/FastMod.cpp](../stress-tests/various/FastMod.cpp) | Pass | 0.272 | — |
| [various/IntervalContainer.cpp](../stress-tests/various/IntervalContainer.cpp) | Pass | 0.677 | — |
| [various/LIS.cpp](../stress-tests/various/LIS.cpp) | Pass | 0.253 | — |
