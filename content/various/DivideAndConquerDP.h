/**
 * Author: Unknown
 * License: CC0
 * Description: Given $a[i] = \min_{lo(i) \le k < hi(i)}(f(i, k))$ where the (minimal) optimal $k$ increases with $i$, computes $a[i]$ for $i = L..R-1$.
 * Time: O((N + (hi - lo)) \log N)
 * Status: tested
 */
#pragma once

struct DP { // Modify at will:
	int lo(int ind) { return 0; }
	int hi(int ind) { return ind; }
	long long f(int ind, int k) { return dp[ind][k]; }
	void store(int ind, int k, long long v) {
		res[ind] = {k, v};
	}

	void rec(int L, int R, int LO, int HI) {
		if (L >= R) return;
		int mid = (L + R) >> 1;
		pair<long long, int> best(LLONG_MAX, LO);
		for (int k = max(LO,lo(mid)); k < min(HI,hi(mid)); ++k)
			best = min(best, make_pair(f(mid, k), k));
		store(mid, best.second, best.first);
		rec(L, mid, LO, best.second+1);
		rec(mid+1, R, best.second, HI);
	}
};
