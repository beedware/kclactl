/**
 * Author: Simon Lindholm
 * Date: 2016-10-08
 * License: CC0
 * Source: me
 * Description: Segment tree with ability to add or set values of large intervals, and compute max of intervals.
 * Can be changed to other things.
 * Ranges are half-open. Build on a nonempty range.
 * Implicit nodes start at zero. Values and pending adds must fit int.
 * Time: O(\log N).
 * Usage: auto tr = make_unique<Node>(v, 0, sz(v));
 * Status: stress-tested a bit
 */
#pragma once

struct Node {
	unique_ptr<Node> l, r;
	int lo, hi, mset = 0, madd = 0, val = 0;
	bool hasSet = false;
	Node(int lo,int hi):lo(lo),hi(hi){}
	Node(vi& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = make_unique<Node>(v, lo, mid);
			r = make_unique<Node>(v, mid, hi);
			val = max(l->val, r->val);
		}
		else val = v[lo];
	}
	int query(int L, int R) {
		if (R <= lo || hi <= L) return INT_MIN;
		if (L <= lo && hi <= R) return val;
		push();
		return max(l->query(L, R), r->query(L, R));
	}
	void set(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) mset = val = x, madd = 0,
			hasSet = true;
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void add(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			if (hasSet) mset += x;
			else madd += x;
			val += x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = make_unique<Node>(lo, mid);
			r = make_unique<Node>(mid, hi);
		}
		if (hasSet)
			l->set(lo,hi,mset), r->set(lo,hi,mset), hasSet = false;
		else if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};
