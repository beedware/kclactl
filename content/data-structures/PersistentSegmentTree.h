/**
 * Author: KCLACTL
 * Date: 2026-10-16
 * License: CC0
 * Source: folklore
 * Description: Point-add, range-sum tree on $[0,N)$, $N>0$.
 * Root 0 is all zeros; add returns a new root, preserving old
 * versions. query uses $[a,b)$. kth(a,b,k) returns the coordinate
 * of the 1-based k-th item in version b minus version a;
 * requires nonnegative count differences and valid k.
 * For range order statistics, compress values; build prefix
 * roots root[i+1] = add(root[i], rank[i], 1), then use
 * kth(root[l], root[r], k) for the subarray $[l,r)$.
 * Usage: PersistentSegTree st(N); int rt = st.add(0, p, 1);
 * Time: O(\log N) per operation; O(\log N) new nodes per add.
 * Status: stress-tested
 */
#pragma once

struct PersistentSegTree {
	struct Node { int l = 0, r = 0; ll sum = 0; };
	vector<Node> t = vector<Node>(1);
	int n;
	PersistentSegTree(int n) : n(n) {}
	int add(int v, int p, ll x, int l = 0, int r = -1) {
		if (r == -1) r = n;
		int u = sz(t); t.push_back(t[v]);
		t[u].sum += x;
		if (r-l > 1) {
			int m = (l+r)/2;
			if (p < m) t[u].l = add(t[v].l, p, x, l, m);
			else t[u].r = add(t[v].r, p, x, m, r);
		}
		return u;
	}
	ll query(int v, int a, int b, int l = 0, int r = -1) const {
		if (r == -1) r = n;
		if (!v || b <= l || r <= a) return 0;
		if (a <= l && r <= b) return t[v].sum;
		int m = (l+r)/2;
		return query(t[v].l, a, b, l, m) +
			query(t[v].r, a, b, m, r);
	}
	int kth(int a, int b, ll k, int l = 0, int r = -1) const {
		if (r == -1) r = n;
		if (r-l == 1) return l;
		int m = (l+r)/2;
		ll cnt = t[t[b].l].sum - t[t[a].l].sum;
		return k <= cnt ? kth(t[a].l, t[b].l, k, l, m) :
			kth(t[a].r, t[b].r, k-cnt, m, r);
	}
};
