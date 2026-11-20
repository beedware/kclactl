/**
 * Author: KCLACTL
 * Date: 2026-11-20
 * License: CC0
 * Description: Minimum spanning forest. Edges are (weight, u, v).
 * Returns the selected edges and sorts the input. For a connected
 * graph with $n>0$, the forest contains $n-1$ edges.
 * Time: O(V + E\log(1+E))
 */
#pragma once

#include "../data-structures/UnionFind.h"

vector<tuple<ll,int,int>> kruskal(
		int n, vector<tuple<ll,int,int>>& edges) {
	sort(all(edges));
	UF uf(n);
	vector<tuple<ll,int,int>> forest;
	for (auto [w,u,v] : edges)
		if (uf.join(u,v)) forest.emplace_back(w,u,v);
	return forest;
}
