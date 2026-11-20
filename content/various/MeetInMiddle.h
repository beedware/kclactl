/**
 * Author: KCLACTL
 * Date: 2026-11-20
 * License: CC0
 * Description: Count index subsets summing to target, including
 * the empty subset. Allows signed values and $n\le 60$. Left
 * half subset sums must fit in ll. Each subset splits uniquely
 * across the halves. Count all left sums complementary to each right sum.
 * Time: O((n+1)2^{\lceil n/2\rceil})
 * Memory: O(2^{\lfloor n/2\rfloor})
 * Status: Compared against exhaustive subset sums
 */
#pragma once

ll countSubsetSum(const vector<ll>& a, ll target) {
	int m = sz(a)/2;
	vector<ll> s{0};
	s.reserve(1ULL << m);
	rep(i,0,m) {
		int k = sz(s);
		rep(j,0,k) s.push_back(s[j] + a[i]);
	}
	sort(all(s));
	auto dfs = [&](auto& go, int i, __int128 t) -> ll {
		if (i == sz(a)) {
			auto [l,r] = equal_range(all(s), t);
			return r-l;
		}
		return go(go,i+1,t) + go(go,i+1,t-a[i]);
	};
	return dfs(dfs,m,target);
}
