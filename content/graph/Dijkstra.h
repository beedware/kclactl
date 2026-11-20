/**
 * Author: KCLACTL
 * Date: 2026-11-20
 * License: CC0
 * Description: Adjacency entries are (neighbor, nonnegative weight).
 * Finite answers must fit strictly below LLONG\_MAX.
 * Returns distances and parents. Unreachable: LLONG\_MAX, parent -1.
 * Time: O(V + E\log(1+E))
 * Memory: O(V+E)
 */
#pragma once

pair<vector<ll>, vi> dijkstra(
		const vector<vector<pair<int,ll>>>& g, int s) {
	using Q = pair<ll,int>;
	priority_queue<Q, vector<Q>, greater<Q>> q;
	vector<ll> d(sz(g), LLONG_MAX);
	vi par(sz(g), -1);
	q.emplace(d[s] = 0, s);
	while (!q.empty()) {
		auto [du,u] = q.top(); q.pop();
		if (du != d[u]) continue;
		for (auto [v,w] : g[u]) if (w < d[v] - du) {
			q.emplace(d[v] = du + w, v);
			par[v] = u;
		}
	}
	return {move(d), move(par)};
}
