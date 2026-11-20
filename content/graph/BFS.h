/**
 * Author: KCLACTL
 * Date: 2026-11-20
 * License: CC0
 * Description: Unit edge distances. Unreachable vertices have distance -1.
 * For paths, store a parent at first discovery. For state graphs,
 * encode the complete state (e.g. vertex and parity) as the vertex ID.
 * Time: O(V+E)
 */
#pragma once

vi bfs(const vector<vi>& g, int s) {
	vi d(sz(g), -1), q{s};
	d[s] = 0;
	rep(i,0,sz(q)) for (int v : g[q[i]]) if (d[v] < 0) {
		d[v] = d[q[i]] + 1;
		q.push_back(v);
	}
	return d;
}
