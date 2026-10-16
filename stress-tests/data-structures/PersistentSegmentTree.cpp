#include "../utilities/template.h"
#include "../utilities/random.h"

#include "../../content/data-structures/PersistentSegmentTree.h"

int main() {
	// Branch from arbitrary historical versions, including negative sums.
	rep(n,1,65) {
		PersistentSegTree st(n);
		vi roots{0};
		vector<vector<ll>> versions(1, vector<ll>(n));
		rep(it,0,200) {
			int base = randRange(sz(roots)), p = randRange(n);
			ll delta = (ll)randRange(-1000000, 1000001) * 1000000;
			auto next = versions[base]; next[p] += delta;
			roots.push_back(st.add(roots[base], p, delta));
			versions.push_back(next);
			rep(q,0,5) {
				int v = randRange(sz(roots));
				int a = randRange(n+1), b = randRange(n+1);
				if (a > b) swap(a, b);
				ll sum = accumulate(versions[v].begin()+a,
					versions[v].begin()+b, 0LL);
				assert(st.query(roots[v], a, b) == sum);
			}
			assert(st.query(0, 0, n) == 0);
		}
	}
	// Prefix histograms: compare k-th queries with sorted subarrays.
	rep(n,1,65) {
		PersistentSegTree st(n);
		vi roots{0}, values;
		rep(i,0,100) {
			int p = randRange(n); values.push_back(p);
			roots.push_back(st.add(roots.back(), p, 1));
		}
		rep(it,0,500) {
			int l = randRange(100), r = randRange(l+1, 101);
			vi sorted(values.begin()+l, values.begin()+r);
			sort(all(sorted));
			for (int k : {1, sz(sorted), randRange(1, sz(sorted)+1)})
				assert(st.kth(roots[l], roots[r], k) == sorted[k-1]);
		}
	}
	// Counts and k can exceed 32 bits; zero-count subtrees are skipped.
	rep(n,1,65) {
		PersistentSegTree st(n);
		int root = 0;
		vector<ll> counts(n);
		rep(it,0,100) {
			int p = randRange(n);
			ll delta = (ll)randRange(1, 101) * 1000000000;
			counts[p] += delta; root = st.add(root, p, delta);
			ll total = accumulate(all(counts), 0LL);
			for (ll k : {1LL, total, randRange(1LL, total+1)}) {
				int pos = 0; ll sum = counts[0];
				while (sum < k) sum += counts[++pos];
				assert(st.kth(0, root, k) == pos);
			}
		}
	}
	cout << "Tests passed!" << endl;
}
