/**
 * Author: David Rydh, Per Austrin
 * Date: 2015-04-18
 * License: CC0
 * Source: based on KACTL's FFT
 * Description: ntt(a) computes $\hat f(k) = \sum_x a[x] g^{xk}$ for all $k$, where $g=\text{root}^{(mod-1)/N}$.
 * N must be a power of 2.
 * Useful for polynomial multiplication modulo specific nice primes of the form $2^a b+1$,
 * where the convolution result has terms smaller than $2^a b$.
 * Inputs must be in $[0, mod)$.
 * Time: O(N \log N)
 * Status: somewhat tested
 */
#pragma once

#include "../number-theory/ModPow.h"

const long long mod = (119 << 23) + 1, root = 62; // = 998244353
// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.
typedef vector<long long> vl;
void ntt(vl &a) {
	int n = (int)a.size(), L = 31 - __builtin_clz(n);
	static vl rt(2, 1);
	for (static int k = 2, s = 2; k < n; k *= 2, s++) {
		rt.resize(n);
		long long z[] = {1, modpow(root, mod >> s)};
		for (int i = k; i < 2*k; ++i) rt[i] = rt[i / 2] * z[i & 1] % mod;
	}
	vector<int> rev(n);
	for(int i=0; i<n; ++i) rev[i] = (rev[i/2] | (i&1) << L) / 2;
	for(int i=0; i<n; ++i) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) for (int j = 0; j < k; j++) {
			long long z = rt[j+k] * a[i+j+k] % mod, &ai = a[i+j];
			a[i + j + k] = ai - z + (z > ai ? mod : 0);
			ai += (ai + z >= mod ? z - mod : z);
		}
}
vl conv(const vl &a, const vl &b) {
	if (a.empty() || b.empty()) return {};
	int s = (int)a.size() + (int)b.size() - 1;
	int B = 32 - __builtin_clz(s), n = 1 << B;
	long long inv = modpow(n, mod - 2);
	vl L(a), R(b), out(n);
	L.resize(n), R.resize(n);
	ntt(L), ntt(R);
	for (int i = 0; i < n; ++i)
		out[-i & (n - 1)] = (long long)L[i] * R[i] % mod * inv % mod;
	ntt(out);
	return {out.begin(), out.begin() + s};
}
