/**
 * Author: KCLACTL
 * Date: 2026-11-20
 * License: CC0
 * Description: Starts with integers $0$ through $n-1$. Delete an
 * integer and find the least remaining integer $\ge x$, or $n$.
 * Repeated deletions are harmless. Never delete the sentinel $n$.
 * Time: O(n) setup, O(\alpha(n)) amortized per operation
 */
#pragma once

#include "UnionFind.h"

struct SuccessorSet {
	UF uf;
	vi last;
	SuccessorSet(int n) : uf(n+1), last(n+1) {
		iota(all(last), 0);
	}
	int next(int x) { return last[uf.find(x)]; }
	void erase(int x) {
		int y = next(x+1);
		uf.join(x, x+1);
		last[uf.find(x)] = y;
	}
};
