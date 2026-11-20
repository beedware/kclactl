/**
 * Author: chilli, Ramchandra Apte, Noam527, Simon Lindholm
 * Date: 2019-04-24
 * License: CC0
 * Source: https://github.com/RamchandraApte/OmniTemplate/blob/master/src/number_theory/modulo.hpp
 * Description: Exact modular multiplication and exponentiation for
 * unsigned 64-bit inputs and a positive modulus. Requires GNU
 * \texttt{\_\_uint128\_t}.
 * Time: O(1) for \texttt{modmul}, O(\log e) for \texttt{modpow}.
 */
#pragma once

typedef unsigned long long ull;
ull modmul(ull a, ull b, ull mod) {
	return (ull)((__uint128_t)a * b % mod);
}
ull modpow(ull b, ull e, ull mod) {
	ull ans = 1 % mod;
	for (; e; b = modmul(b, b, mod), e /= 2)
		if (e & 1) ans = modmul(ans, b, mod);
	return ans;
}
