/**
 * Author: Simon Lindholm
 * Date: 2016-08-31
 * License: CC0
 * Source: http://eli.thegreenplace.net/2009/03/07/computing-modular-square-roots-in-python/
 * Description: Tonelli-Shanks. Finds $x$ with $x^2\equiv a\pmod p$
 * for prime $p$ and a square residue $a$. The other root is $-x$.
 * Time: O(\log^2 p) after finding a nonsquare
 * Status: Tested for all a,p <= 10000
 */
#pragma once

#include "ModMulLL.h"

ll sqrt(ll a, ll p) {
	a %= p; if (a < 0) a += p;
	if (a == 0 || p == 2) return a;
	assert(modpow(a, (p-1)/2, p) == 1); // else no solution
	if (p % 4 == 3) return modpow(a, p/4 + 1, p);
	ll s = p - 1, n = 2;
	int r = 0, m;
	while (s % 2 == 0)
		++r, s /= 2;
	/// find a non-square mod p
	while (modpow(n, (p - 1) / 2, p) != (ull)(p - 1)) ++n;
	ll x = modpow(a, (s + 1) / 2, p);
	ll b = modpow(a, s, p), g = modpow(n, s, p);
	for (;; r = m) {
		ll t = b;
		for (m = 0; m < r && t != 1; ++m)
			t = modmul(t, t, p);
		if (m == 0) return x;
		ll gs = modpow(g, 1LL << (r - m - 1), p);
		g = modmul(gs, gs, p);
		x = modmul(x, gs, p);
		b = modmul(b, g, p);
	}
}
