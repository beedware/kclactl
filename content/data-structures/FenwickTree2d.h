/**
 * Author: Simon Lindholm
 * Date: 2017-05-11
 * License: CC0
 * Source: folklore
 * Description: Computes $\sum_{i \le x, j \le y} A[i][j]$ for a 2D array, where each $(i, j)$
 * is added at most once.
 * Point updates, range queries.
 * Time: Both operations are $O(\log^2 N)$.
 * Space: $O(N \log N)$
 * Status: Stress-tested
 */
#pragma once

#include "FenwickTree.h"

struct FT2 {
	vector<vector<int>> ys; vector<FT> ft;
	FT2(int limx) : ys(limx) {}
	void fakeUpdate(int x, int y) {
		for (; x < (int)ys.size(); x |= x + 1) ys[x].push_back(y);
	}
	void init() {
		for (auto& v : ys)
			sort(v.begin(), v.end()), ft.emplace_back(v.size());
	}
	int ind(int x, int y) {
		auto& v = ys[x];
		return lower_bound(v.begin(), v.end(), y) - v.begin();
	}
	void update(int x, int y, long long dif) {
		for (; x < (int)ys.size(); x |= x + 1)
			ft[x].update(ind(x, y), dif);
	}
	long long query(int x, int y) {
		long long sum = 0;
		for (; x; x &= x - 1)
			sum += ft[x-1].query(ind(x-1, y));
		return sum;
	}
};
