/**
 * Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed max-tree. Bounds are inclusive to the left and exclusive to the right.
 * firstAbove returns the first index in [L,R) with value > x, or -1.
 * To change T, f and unit for other aggregates, drop firstAbove.
 * Time: O(\log N)
 * Status: stress-tested
 */
#pragma once

struct Tree {
	typedef int T;
	static constexpr T unit = INT_MIN;
	T f(T a, T b) { return max(a, b); } // (any associative fn)
	vector<T> s; int n;
	Tree(int count = 0, T def = unit) : n(1) {
		while (n < count) n *= 2;
		s.assign(2*n, unit);
		fill_n(s.begin() + n, count, def);
		for (int i = n; --i;) s[i] = f(s[2*i], s[2*i+1]);
	}
	int firstAbove(int L, int R, T x, int i = 1,
			int l = 0, int r = -1) {
		if (r == -1) r = n;
		if (L >= R || R <= l || r <= L || s[i] <= x) return -1;
		if (r-l == 1) return l;
		int m = (l+r)/2;
		int left = firstAbove(L, R, x, 2*i, l, m);
		return left != -1 ? left :
			firstAbove(L, R, x, 2*i+1, m, r);
	}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};
