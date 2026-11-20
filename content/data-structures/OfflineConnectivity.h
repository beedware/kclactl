/**
 * Author: KCLACTL
 * Date: 2026-11-20
 * License: CC0
 * Description: Offline connectivity at times $[0,Q)$.
 * Add each undirected edge lifetime $[l,r)$, then visit
 * each time in order with the current rollback DSU.
 * For connectivity, compare roots. Use query-only callbacks.
 * Each active edge occurs once on the root-to-leaf path.
 * Time: O(\log(Q+1)) per interval, then
 * O(V+Q+I\log(Q+1)\log(V+1)) plus callbacks for $I$ intervals
 * Memory: O(V+Q+I\log(Q+1))
 * Status: Compared against per-time BFS on random graphs
 */
#pragma once

#include "UnionFindRollback.h"

struct OfflineConnectivity {
	int q, base = 1;
	vector<vector<pii>> edges;
	OfflineConnectivity(int q) : q(q) {
		while (base < q) base *= 2;
		edges.resize(2*base);
	}
	void add(int l, int r, int u, int v) {
		for (l += base, r += base; l < r; l /= 2, r /= 2) {
			if (l & 1) edges[l++].emplace_back(u,v);
			if (r & 1) edges[--r].emplace_back(u,v);
		}
	}
	template<class F> void run(int n, F visit) {
		RollbackUF uf(n);
		auto dfs = [&](auto& go, int i) -> void {
			int save = uf.time();
			for (auto [u,v] : edges[i]) uf.join(u,v);
			if (i < base) go(go,2*i), go(go,2*i+1);
			else if (i-base < q) visit(i-base,uf);
			uf.rollback(save);
		};
		dfs(dfs,1);
	}
};
