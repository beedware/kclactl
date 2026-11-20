#include "../utilities/template.h"

#include "../../content/number-theory/ModMulLL.h"

ull modmulReference(ull a, ull b, ull m) {
	auto add = [m](ull x, ull y) {
		return x >= m-y ? x-(m-y) : x+y;
	};
	ull res = 0;
	for (a %= m; b; a = add(a, a), b /= 2)
		if (b & 1) res = add(res, a);
	return res;
}

int main() {
	mt19937_64 rng(1);
	rep(i,0,100000) {
		ull a = rng(), b = rng(), m = max(1ULL, (ull)rng());
		assert(modmul(a, b, m) == modmulReference(a, b, m));
	}
	assert(modmul(ULLONG_MAX, ULLONG_MAX, ULLONG_MAX-1) == 1);
	assert(modpow(7, 0, 1) == 0);
	cout << "Tests passed!" << endl;
}
