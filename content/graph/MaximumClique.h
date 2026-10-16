/**
 * Author: chilli, Andrew He, Simon Lindholm
 * Date: 2019-05-17
 * License: CC0
 * Source: https://en.wikipedia.org/wiki/MaxCliqueDyn_maximum_clique_algorithm, https://gitlab.com/janezkonc/mcqd/blob/master/mcqd.h
 * Description: Quickly finds a maximum clique of a dense graph, running in
 * $O(1.21^V)$ on average. Graph vertices are 0-indexed.
 * Time: "Typically practically instantaneous up to $N = 150$"
 * Status: stress-tested
 */
#pragma once

typedef vector<bool> vb;
struct Vertex { int i, d = 0; };

typedef bool (*proc)(const vector<int>&);
struct Maxclique {
	const double limit=0.025;
	const double pk=0;
	struct Vertex { int i, d = 0; };
	typedef vector<Vertex> vv;
	vb e;
	vv V;
	vector<vector<int>> C;
	vector<int> qmax, q, S, old;
	void init(vv& r) {
		for (auto& v : r) v.d = 0;
		for (auto& v : r) for (auto j : r) v.d += e[v.i][j.i];
		sort(r.begin(), r.end(),
			[](auto a, auto b) { return a.d > b.d; });
		int mxD = r[0].d, i = 0;
		for (auto& x : r) x.d = min(i++, mxD) + 1;
	}
	void expand(vv& R, int lev = 1) {
		S[lev] += S[lev - 1] - old[lev];
		old[lev] = S[lev - 1];
		while (!R.empty()) {
			if (q.size() + R.back().d <= qmax.size()) return;
			q.push_back(R.back().i);
			vv T;
			for(auto v:R) if (e[R.back().i][v.i]) T.push_back({v.i});
			if (!T.empty()) {
				if (S[lev]++ / ++pk < limit) init(T);
				int j = 0, mxk = 1;
				int mnk = max(int(qmax.size() - q.size()) + 1, 1);
				C[1].clear(), C[2].clear();
				for (auto v : T) {
					int k = 1;
					auto f = [&](int i) { return e[v.i][i]; };
					while (any_of(C[k].begin(), C[k].end(), f)) k++;
					if (k > mxk) mxk = k, C[mxk + 1].clear();
					if (k < mnk) T[j++].i = v.i;
					C[k].push_back(v.i);
				}
				if (j > 0) T[j - 1].d = 0;
				for (int k = mnk; k < mxk + 1; ++k) for (int i : C[k])
					T[j].i = i, T[j++].d = k;
				expand(T, lev + 1);
			} else if (q.size() > qmax.size()) qmax = q;
			q.pop_back(), R.pop_back();
		}
	}
	vector<int> maxClique() { init(V), expand(V); return qmax; }
	Maxclique(vb conn) : e(conn), C(e.size()+1), S(C.size()),
		old(S) {
		for (int i = 0; i < (int)e.size(); ++i) V.push_back({i});
	}
};
