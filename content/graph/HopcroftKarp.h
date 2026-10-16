/**
 * Author: Chen Xing
 * Date: 2009-10-13
 * License: CC0
 * Source: N/A
 * Description: Fast bipartite matching algorithm. Graph $g$ should be a list
 * of neighbors of the left partition, and $r$ will be filled with the matched
 * vertex on the right partition, or $-1$ if it is not matched. Also considers
 * the vertex to be matched with itself if it is not in the graph.
 * Time: O(\sqrt{V} E)
 * Status: stress-tested by kattis/graphtheory
 */
#pragma once

int hopcroftKarp(vector<vector<int>>& g, vector<int>& r) {
	int n = (int)g.size(), res = 0;
	vector<int> l(n, -1), q(n), d(n);
	auto dfs = [&](auto f, int u) -> bool {
		int t = exchange(d[u], 0) + 1;
		for (int v : g[u])
			if (r[v] == -1 || (d[r[v]] == t && f(f, r[v])))
				return l[u] = v, r[v] = u, 1;
		return 0;
	};
	for (int t = 0, f = 0;; t = f = 0, d.assign(n, 0)) {
		for(int i=0; i<n; ++i) if (l[i] < 0) q[t++] = i, d[i] = 1;
		for (int i = 0; i < t; ++i) for (int v : g[q[i]]) {
			if (r[v] == -1) f = 1;
			else if (!d[r[v]]) d[r[v]] = d[q[i]] + 1, q[t++] = r[v];
		}
		if (!f) return res;
		for(int i=0; i<n; ++i) if (l[i] < 0) res += dfs(dfs, i);
	}
}
