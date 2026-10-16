/**
 * Author: Stanford
 * Date: unknown
 * Source: Stanford Notebook
 * Description: Min-cost max-flow.
 *  If costs can be negative, call \texttt{setpi} before \texttt{maxflow}, but no negative cycles are allowed.
 *  To get the flow on an edge, look at \texttt{e.flow}.
 * Status: Tested on kattis:mincostmaxflow, stress-tested against simplex
 * Time: $O(F E \log(V))$ where $F$ is max flow. $O(V E)$ for \texttt{setpi}.
 */
#pragma once

// #include <bits/extc++.h> /// include-line, keep-include

const long long INF = numeric_limits<long long>::max() / 4;

struct MCMF {
	struct edge {
		int from, to, rev;
		long long cap, cost, flow;
	};
	int N;
	vector<vector<edge>> ed;
	vector<int> seen;
	vector<long long> dist, pi;
	vector<edge*> par;

	MCMF(int N) : N(N), ed(N), seen(N), dist(N), pi(N), par(N) {}

	void addEdge(int s, int t, long long cap, long long cost) {
		if (s == t) return;
		ed[s].push_back(edge{s, t, (int)ed[t].size(), cap, cost, 0});
		ed[t].push_back(edge{t, s, (int)ed[s].size()-1, 0, -cost, 0});
	}

	void path(int s) {
		fill(seen.begin(), seen.end(), 0);
		fill(dist.begin(), dist.end(), INF);
		dist[s] = 0; long long di;

		__gnu_pbds::priority_queue<pair<long long, int>> q;
		vector<decltype(q)::point_iterator> its(N);
		q.push({ 0, s });

		while (!q.empty()) {
			s = q.top().second; q.pop();
			seen[s] = 1; di = dist[s] + pi[s];
			for (edge& e : ed[s]) if (!seen[e.to]) {
				long long val = di - pi[e.to] + e.cost;
				if (e.cap - e.flow > 0 && val < dist[e.to]) {
					dist[e.to] = val;
					par[e.to] = &e;
					if (its[e.to] == 0) its[e.to] = q.push({ -dist[e.to], e.to });
					else q.modify(its[e.to], { -dist[e.to], e.to });
				}
			}
		}
		for (int i = 0; i < N; ++i) pi[i] = min(pi[i]+dist[i], INF);
	}

	pair<long long, long long> maxflow(int s, int t) {
		long long totflow = 0, totcost = 0;
		while (path(s), seen[t]) {
			long long fl = INF;
			for (edge* x = par[t]; x; x = par[x->from])
				fl = min(fl, x->cap - x->flow);

			totflow += fl;
			for (edge* x = par[t]; x; x = par[x->from]) {
				x->flow += fl;
				ed[x->to][x->rev].flow -= fl;
			}
		}
		for (auto& v : ed) for (edge& e : v)
			totcost += e.cost * e.flow;
		return {totflow, totcost/2};
	}

	// If some costs can be negative, call this before maxflow:
	void setpi(int s) { // (otherwise, leave this out)
		fill(pi.begin(), pi.end(), INF); pi[s] = 0;
		int it = N, ch = 1; long long v;
		while (ch-- && it--)
			for (int i = 0; i < N; ++i) if (pi[i] != INF)
			  for (edge& e : ed[i]) if (e.cap)
				  if ((v = pi[i] + e.cost) < pi[e.to])
					  pi[e.to] = v, ch = 1;
		assert(it >= 0); // negative cost cycle
	}
};
