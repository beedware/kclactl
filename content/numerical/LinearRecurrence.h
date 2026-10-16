/**
 * Author: Lawrence Luo, Simon Lindholm
 * Date: 2020-08-04
 * License: CC0
 * Source: http://people.csail.mit.edu/virgi/6.890/lecture5.pdf
 * Description: Generates the $k$'th term of an $n$-order
 * linear recurrence $S[i] = \sum_j S[i-j-1]tr[j]$,
 * given $S[0 \dots \ge n-1]$ and $tr[0 \dots n-1]$.
 * Faster than matrix multiplication.
 * Useful after Berlekamp-Massey.
 * Usage: linearRec({0, 1}, {1, 1}, k) // k'th Fibonacci number
 * Time: O(n \log n \log k)
 * Status: stress-tested
 */
#pragma once

#include "FastFourierTransform.h"

const long long mod = 5; /** exclude-line */
typedef vector<double> Poly; /** exclude-line */
typedef vector<long long> Poly;
long long linearRec(Poly S, Poly tr, long long k) {
	int n = (int)tr.size();
	auto combine = [&](Poly a, Poly b) {
		Poly res(n * 2 + 1);
		for (int i = 0; i < n+1; ++i) for (int j = 0; j < n+1; ++j)
			res[i + j] = (res[i + j] + a[i] * b[j]) % mod;
		for (int i = 2 * n; i > n; --i) for (int j = 0; j < n; ++j)
			res[i - 1 - j] = (res[i - 1 - j] + res[i] * tr[j]) % mod;
		res.resize(n + 1);
		return res;
	};
	Poly pol(n + 1), e(pol);
	pol[0] = e[1] = 1;

	for (++k; k; k /= 2) {
		if (k % 2) pol = combine(pol, e);
		e = combine(e, e);
	}

	long long res = 0;
	for(int i=0; i<n; ++i) res = (res + pol[i+1]*S[i]) % mod;
	return res;
}
