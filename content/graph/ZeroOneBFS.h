/**
 * Author: KCLACTL
 * Date: 2026-11-20
 * License: CC0
 * Description: Adjacency entries are (neighbor, weight), weight 0 or 1.
 * Unreachable vertices have distance INT\_MAX.
 * Time: O(V+E)
 */
#pragma once

vi zeroOneBfs(const vector<vector<pii>>& g, int s) {
	vi d(sz(g), INT_MAX);
	deque<pii> q{{0,s}};
	d[s] = 0;
	while (!q.empty()) {
		auto [du,u] = q.front(); q.pop_front();
		if (du != d[u]) continue;
		for (auto [v,w] : g[u]) if (du + w < d[v]) {
			d[v] = du + w;
			if (w) q.emplace_back(d[v], v);
			else q.emplace_front(d[v], v);
		}
	}
	return d;
}
