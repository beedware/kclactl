/**
 * Author: chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://cp-algorithms.com/graph/dinic.html
 * Description: Max flow with capacity scaling. Capacities are
 * nonnegative, source and sink differ, and each c + rcap and
 * the total flow must fit in ll. Call calc again after adding
 * edges to obtain the extra flow for the same terminals.
 * Time: O(VE\log(U+1)) for maximum capacity $U>0$.
 * O(\min(\sqrt E,V^{2/3})E) for unit-capacity networks
 * and O(\sqrt V E) for bipartite matching
 * Status: Tested on SPOJ FASTFLOW and SPOJ MATCHING, stress-tested
 */
#pragma once

struct Dinic {
	struct Edge {
		int to, rev;
		ll c, oc;
		ll flow() { return max(oc - c, 0LL); } // if you need flows
	};
	vi lvl, ptr, q;
	vector<vector<Edge>> adj;
	Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
	void addEdge(int a, int b, ll c, ll rcap = 0) {
		adj[a].push_back({b, sz(adj[b]) + (a == b), c, c});
		adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
	}
	ll dfs(int v, int t, ll f, ll lim) {
		if (v == t || !f) return f;
		for (int& i = ptr[v]; i < sz(adj[v]); i++) {
			Edge& e = adj[v][i];
			if (e.c >= lim && lvl[e.to] == lvl[v] + 1)
				if (ll p = dfs(e.to, t, min(f, e.c), lim)) {
					e.c -= p, adj[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}
	ll calc(int s, int t) {
		ll flow = 0, cap = 0, lim = 1;
		for (auto& es : adj) for (auto& e : es) cap = max(cap, e.c);
		while (lim <= cap/2) lim *= 2;
		q[0] = s;
		for (; lim; lim /= 2) do {
			fill(all(lvl), 0); fill(all(ptr), 0);
			int qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				int v = q[qi++];
				for (auto& e : adj[v])
					if (!lvl[e.to] && e.c >= lim)
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while (ll p = dfs(s, t, LLONG_MAX, lim)) flow += p;
		} while (lvl[t]);
		return flow;
	}
	bool leftOfMinCut(int a) { return lvl[a] != 0; }
};
