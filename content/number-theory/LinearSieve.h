/**
 * Author: KCLACTL
 * Date: 2026-11-20
 * License: CC0
 * Description: Least prime factor of each integer in $[2,N]$
 * and the list of primes. Entries for 0 and 1 are zero.
 * To factor x, divide by lp[x] until x reaches 1.
 * Each composite x is written once, by x / lp[x] and lp[x].
 * Usage: auto [lp, primes] = linearSieve(N);
 * Time: O(N)
 * Memory: O(N)
 * Status: Compared least factors against trial division
 */
#pragma once

pair<vi,vi> linearSieve(int n) {
	vi lp(n+1), primes;
	for (int x = 2; x <= n; ++x) {
		if (!lp[x]) lp[x] = x, primes.push_back(x);
		int lim = min(lp[x], n/x);
		for (int p : primes) {
			if (p > lim) break;
			lp[x*p] = p;
		}
	}
	return {move(lp), move(primes)};
}
