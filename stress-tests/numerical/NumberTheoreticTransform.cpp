#include "../utilities/template.h"

typedef vector<ll> vl;
#include "../../content/numerical/NumberTheoreticTransform.h"

vl simpleConv(vl a, vl b) {
	int s = sz(a) + sz(b) - 1;
	if (a.empty() || b.empty()) return {};
	vl c(s);
	rep(i,0,sz(a)) rep(j,0,sz(b))
		c[i+j] = (c[i+j] + (ll)a[i] * b[j]) % nttMod;
	for(auto &x: c) if (x < 0) x += nttMod;
	return c;
}

int ra() {
	static unsigned X;
	X *= 123671231;
	X += 1238713;
	X ^= 1237618;
	return (X >> 1);
}

int main() {
	ll res = 0, res2 = 0;
	int ind = 0, ind2 = 0;
	vl a, b;
	rep(it,0,6000) {
		a.resize(ra() % 10);
		b.resize(ra() % 10);
		for(auto &x: a) x = (ra() % 100 - 50+nttMod)%nttMod;
		for(auto &x: b) x = (ra() % 100 - 50+nttMod)%nttMod;
		for(auto &x: simpleConv(a, b)) res += (ll)x * ind++ % nttMod;
		for(auto &x: conv(a, b)) res2 += (ll)x * ind2++ % nttMod;
		a.resize(16);
			vl a2 = a;
			ntt(a2);
			rep(k, 0, sz(a2)) {
				ll sum = 0;
				rep(x, 0, sz(a2)) { sum = (sum + a[x] * (ll)modpow(nttRoot, k * x * (nttMod - 1) / sz(a), nttMod)) % nttMod; }
				assert(sum == a2[k]);
			}
	}
	assert(res==res2);
	cout<<"Tests passed!"<<endl;
}
