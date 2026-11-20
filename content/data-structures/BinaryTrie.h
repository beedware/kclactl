/**
 * Author: KCLACTL
 * Date: 2026-11-20
 * License: CC0
 * Description: Multiset with unsigned $B$-bit inputs.
 * Use add(x) to insert and add(x,-1) to erase a present copy.
 * maxXor(x) returns the greatest XOR with a stored value.
 * Query a nonempty trie. Recover the partner by XOR with x.
 * Time: O(B), amortized for insertion
 * Memory: O(1+BD) for $D$ distinct values ever inserted
 * Status: Compared against linear scans with duplicate insertions
 */
#pragma once

template<int B = 32> struct BinaryTrie {
	using U = uint64_t;
	static_assert(1 <= B && B <= 64);
	struct Node { int ch[2]{}, count = 0; };
	vector<Node> t{1};
	void add(U x, int delta = 1) {
		int u = 0;
		t[u].count += delta;
		for (int i = B; i--;) {
			int b = (x >> i) & 1;
			if (!t[u].ch[b]) {
				t[u].ch[b] = sz(t);
				t.emplace_back();
			}
			u = t[u].ch[b];
			t[u].count += delta;
		}
	}
	U maxXor(U x) const {
		assert(t[0].count > 0);
		U res = 0;
		int u = 0;
		for (int i = B; i--;) {
			int b = (x >> i) & 1, v = t[u].ch[!b];
			if (v && t[v].count) res |= U(1) << i, u = v;
			else u = t[u].ch[b];
		}
		return res;
	}
};
