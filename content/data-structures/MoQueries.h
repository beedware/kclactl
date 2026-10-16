/**
 * Author: Simon Lindholm
 * Date: 2019-12-28
 * License: CC0
 * Source: https://github.com/gabriel-russoc/competitive-programming/blob/master/codeforces/101744/j.cpp
 * Description: Answer interval queries in $O((N + Q) \sqrt{N})$ or $O(N \sqrt{Q})$.
 * The tree version orders queries by (I[u], I[v]), where I is an Euler tour of the tree.
 * The path from $u$ to $v$ is given by $\{x : \text{in}[x]\}$ after iterating through the tour.
 * To use, provide the \texttt{add}, \texttt{del}, and \texttt{calc} functions.
 * Time: O(N \sqrt{Q})
 * Status: stress-tested
 */
#pragma once

void add(int ind, int end) { ... } // add a[ind] (end = 0 or 1)
void del(int ind, int end) { ... } // remove a[ind]
int calc() { ... } // compute current answer

vector<int> mo(vector<pair<int, int>> Q) {
	int L = 0, R = 0, blk = 350; // ~N/sqrt(Q)
	vector<int> s(Q.size()), res = s;
#define K(x) pair(x.first/blk, x.second ^ -(x.first/blk & 1))
	iota(s.begin(), s.end(), 0);
	sort(s.begin(), s.end(), [&](int s, int t){ return K(Q[s]) < K(Q[t]); });
	for (int qi : s) {
		pair<int, int> q = Q[qi];
		while (L > q.first) add(--L, 0);
		while (R < q.second) add(R++, 1);
		while (L < q.first) del(L++, 0);
		while (R > q.second) del(--R, 1);
		res[qi] = calc();
	}
	return res;
}

vector<int> moTree(vector<array<int, 2>> Q,
	vector<vector<int>>& ed, int root=0) {
	int N = (int)ed.size(), pos[2] = {}, blk = 350; // ~N/sqrt(Q)
	vector<int> s(Q.size()), res = s, I(N), in(N), par(N);
	vector<int> L(N), R(N);
	add(0, 0), in[0] = 1;
	auto dfs = [&](int x, int p, int dep, auto& f) -> void {
		par[x] = p;
		L[x] = N;
		if (dep) I[x] = N++;
		for (int y : ed[x]) if (y != p) f(y, x, !dep, f);
		if (!dep) I[x] = N++;
		R[x] = N;
	};
	dfs(root, -1, 0, dfs);
#define K2(x) pair(I[x[0]]/blk, I[x[1]] ^ -(I[x[0]]/blk & 1))
	iota(s.begin(), s.end(), 0);
	sort(s.begin(), s.end(), [&](int s, int t){ return K2(Q[s]) < K2(Q[t]); });
	for (int qi : s) for (int end = 0; end < 2; ++end) {
		int &a = pos[end], b = Q[qi][end], i = 0;
#define step(c) { if (in[c]) { del(a, end); in[a] = 0; } \
                  else { add(c, end); in[c] = 1; } a = c; }
		while (L[a] < L[b]) step(par[a]);
		while (R[a] > R[b]) step(par[a]);
		while (a != b) { step(par[a]); step(par[b]); }
		if (end) res[qi] = calc();
	}
	return res;
}
