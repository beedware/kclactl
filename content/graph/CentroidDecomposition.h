/**
 * Author: FamALouiz, KCLACTL
 * Date: 2026-10-16
 * License: CC BY-SA 4.0
 * Source: https://cp-algorithms.com/graph/centroid_decomposition.html
 * Description: Builds centroid parents of an undirected tree;
 * root has parent -1. Add per-component work at the comment.
 * Usage: CentroidDecomposition cd(adj);
 * Time: O(N \log N)
 * Status: stress-tested
 */
#pragma once

struct CentroidDecomposition {
	const vector<vi>& adj;
	vi siz, par, removed;
	CentroidDecomposition(const vector<vi>& g) : adj(g),
		siz(sz(g)), par(sz(g), -1), removed(sz(g)) {
		if (sz(g)) build(0);
	}
	int dfs(int v, int p = -1) {
		siz[v] = 1;
		for (int u : adj[v]) if (u != p && !removed[u])
			siz[v] += dfs(u, v);
		return siz[v];
	}
	int centroid(int v, int n, int p = -1) {
		for (int u : adj[v]) if (u != p && !removed[u])
			if (siz[u] > n / 2) return centroid(u, n, v);
		return v;
	}
	void build(int v, int p = -1) {
		int c = centroid(v, dfs(v));
		par[c] = p;
		// Process paths through c here, ignoring removed nodes.
		removed[c] = 1;
		for (int u : adj[c]) if (!removed[u]) build(u, c);
	}
};
