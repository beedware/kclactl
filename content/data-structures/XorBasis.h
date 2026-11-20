/**
 * Author: KCLACTL
 * Date: 2026-11-20
 * License: CC0
 * Description: Basis for all subset XORs of unsigned 64-bit values.
 * add(x) returns true iff rank increases. contains(x) tests
 * reachability. maxXor(x) maximizes x XOR a reachable value.
 * Each pivot controls one bit while leaving higher bits fixed.
 * There are $2^{\mathrm{rank}}$ distinct subset XORs.
 * Time: O(B) per operation for $B=64$
 * Status: Compared against exhaustive subset XORs
 */
#pragma once

struct XorBasis {
	using U = uint64_t;
	array<U,64> b{};
	int rank = 0;
	U reduce(U x) const {
		for (int i = 64; i--;)
			if ((x >> i) & 1) x ^= b[i];
		return x;
	}
	bool add(U x) {
		x = reduce(x);
		if (!x) return false;
		b[63-__builtin_clzll(x)] = x;
		++rank;
		return true;
	}
	bool contains(U x) const { return reduce(x) == 0; }
	U maxXor(U x = 0) const {
		for (int i = 64; i--;) x = max(x, x ^ b[i]);
		return x;
	}
};
