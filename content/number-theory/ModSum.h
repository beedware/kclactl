/**
 * Author: Simon Lindholm
 * Date: 2015-09-01
 * License: CC0
 * Source: https://vault.hackerank.com/challenges/aladin/editorial
 * Description: Sum of modulos. \texttt{modsum(to, c, k, m)} $\sum_{i=0}^{\mathrm{to}-1} (ki+c \bmod m)$.
 * Time: $\log(m)$
 * Status: Tested for all |k|,|c|,to,m <= 50, and on kattis:aladin
 */
#pragma once

typedef unsigned long long ull;

ull sumsq(ull to) { return to / 2 * ((to-1) | 1); }

ull divsum(ull to, ull c, ull k, ull m) {
	ull res = k / m * sumsq(to) + c / m * to;
	k %= m; c %= m;
	if (!k) return res;
	ull to2 = (to * k + c) / m;
	return res + (to - 1) * to2 - divsum(to2, m-1 - c, m, k);
}

long long modsum(ull to, long long c,
                 long long k, long long m) {
	c = ((c % m) + m) % m;
	k = ((k % m) + m) % m;
	return to * c + k * sumsq(to) - m * divsum(to, c, k, m);
}
