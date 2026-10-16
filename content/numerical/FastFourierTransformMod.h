/**
 * Author: Simon Lindholm
 * Date: 2016-12-09
 * License: CC0
 * Source: http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf
 * Description: Higher precision FFT, can be used for convolutions modulo arbitrary integers
 * as long as $N\log_2 N\cdot \text{mod} < 8.6 \cdot 10^{14}$ (in practice $10^{16}$ or higher).
 * Inputs must be in $[0, \text{mod})$.
 * Time: O(N \log N), about 5x slower than FFT
 * Status: stress-tested
 */
#pragma once

#include "FastFourierTransform.h"

typedef vector<long long> vl;
template<int M> vl convMod(const vl &a, const vl &b) {
	if (a.empty() || b.empty()) return {};
	int sa = a.size(), sb = b.size();
	vl res(sa + sb - 1);
	int B = 32 - __builtin_clz(res.size()), n = 1 << B, cut = sqrt(M);
	vector<C> L(n), R(n), outs(n), outl(n);
	for (int i = 0; i < sa; ++i) L[i] = C(a[i]/cut, a[i]%cut);
	for (int i = 0; i < sb; ++i) R[i] = C(b[i]/cut, b[i]%cut);
	fft(L), fft(R);
	for (int i = 0; i < n; ++i) {
		int j = -i & (n - 1);
		outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
		outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
	}
	fft(outl), fft(outs);
	for (int i = 0; i < (int)res.size(); ++i) {
		long long av = real(outl[i]) + .5, cv = imag(outs[i]) + .5;
		long long bv = imag(outl[i]) + .5; bv += real(outs[i]) + .5;
		res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
	}
	return res;
}
