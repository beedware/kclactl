/**
 * Author: chilli
 * Date: 2019-04-16
 * License: CC0
 * Source: based on KACTL's FFT
 * Description: ntt(a) computes $\hat f(k) = \sum_x a[x] g^{xk}$ for all $k$, where $g=\text{nttRoot}^{(nttMod-1)/N}$.
 * N must be a power of 2 up to $2^{23}$.
 * Useful for convolution modulo specific nice primes of the form $2^a b+1$,
 * where the convolution result has size at most $2^a$. For arbitrary modulo, see FFTMod.
   \texttt{conv(a, b) = c}, where $c[x] = \sum a[i]b[x-i]$.
   For manual convolution: NTT the inputs, multiply
   pointwise, divide by n, reverse(start+1, end), NTT back.
 * Inputs must be in [0, nttMod).
 * Time: O(N \log N)
 * Memory: O(N)
 * Status: stress-tested
 */
#pragma once

#include "../number-theory/ModMulLL.h"

const ll nttMod = 998244353, nttRoot = 62;
typedef vector<ll> vl;
void ntt(vl &a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vl rt(2, 1);
	for (static int k = 2, s = 2; k < n; k *= 2, s++) {
		rt.resize(n);
		ll z[] = {1, (ll)modpow(nttRoot, nttMod >> s, nttMod)};
		rep(i,k,2*k) rt[i] = rt[i / 2] * z[i & 1] % nttMod;
	}
	vi rev(n);
	rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
			ll z = rt[j + k] * a[i + j + k] % nttMod, &ai = a[i + j];
			a[i + j + k] = ai - z + (z > ai ? nttMod : 0);
			ai += (ai + z >= nttMod ? z - nttMod : z);
		}
}
vl conv(const vl &a, const vl &b) {
	if (a.empty() || b.empty()) return {};
	int s = sz(a) + sz(b) - 1, n = 1;
	assert(s <= (1 << 23));
	while (n < s) n *= 2;
	ll inv = (ll)modpow(n, nttMod - 2, nttMod);
	vl L(a), R(b);
	L.resize(n), R.resize(n);
	ntt(L), ntt(R);
	rep(i,0,n) L[i] = L[i] * R[i] % nttMod * inv % nttMod;
	reverse(L.begin() + 1, L.end());
	ntt(L);
	L.resize(s);
	return L;
}
