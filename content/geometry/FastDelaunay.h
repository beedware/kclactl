/**
 * Author: Philippe Haas
 * Date: 2020-04-24
 * License: CC0
 * Source: https://github.com/c137y/pointpack/blob/master/include/pointpack/delaunay.hpp
 * Description: Fast Delaunay triangulation.
 * Each circumcircle contains none of the input points.
 * There must be no duplicate points.
 * If all points are on a line, no triangles will be returned.
 * Should work for doubles as well, though there may be precision issues in 'circ'.
 * Returns triangles in order $\{A_1, B_1, C_1, A_2, B_2, C_2, \dots\}$ after Delaunay.
 * Time: O(n \log n)
 * Status: stress-tested
 */
#pragma once

#include "Point.h"

typedef Point<long long> P;
typedef struct Quad* Q;
typedef __int128_t lll; // (long long if coords < 2e4)
P arb(LLONG_MAX,LLONG_MAX); // not equal to any other point

struct Quad {
	Q rot, o; P p = arb; bool mark;
	P& F() { return r()->p; }
	Q& r() { return rot->rot; }
	Q prev() { return rot->o->rot; }
	Q next() { return r()->prev(); }
} *H;

bool circ(P p, P a, P b, P c) { // is p in the circumcircle?
	lll p2 = p.dist2(), A = a.dist2()-p2, B = b.dist2()-p2, C = c.dist2()-p2;
	return p.cross(a,b)*C + p.cross(b,c)*A + p.cross(c,a)*B > 0;
}

Q makeEdge(P orig, P dest) {
	Q r = H ? H : new Quad{new Quad{new Quad{new Quad{0}}}};
	H = r->o; r->r()->r() = r;
	for (int i = 0; i < 4; ++i)
		r = r->rot, r->p = arb, r->o = i & 1 ? r : r->r();
	r->p = orig; r->F() = dest;
	return r;
}

void splice(Q a, Q b) {
	swap(a->o->rot->o, b->o->rot->o); swap(a->o, b->o);
}

Q connect(Q a, Q b) {
	Q q = makeEdge(a->F(), b->p);
	splice(q, a->next());
	splice(q->r(), b);
	return q;
}

pair<Q,Q> rec(const vector<P>& s) {
	if ((int)s.size() <= 3) {
		Q a = makeEdge(s[0], s[1]), b = makeEdge(s[1], s.back());
		if ((int)s.size() == 2) return { a, a->r() };
		splice(a->r(), b);
		auto side = s[0].cross(s[1], s[2]);
		Q c = side ? connect(b, a) : 0;
		return {side < 0 ? c->r() : a, side < 0 ? c : b->r() };
	}

#define H(e) e->F(), e->p
#define valid(e) (e->F().cross(H(base)) > 0)
	Q A, B, ra, rb;
	int half = (int)s.size() / 2;
	tie(ra, A) = rec({s.begin(), s.end() - half});
	tie(B, rb) = rec({s.end() - half, s.end()});
	while ((B->p.cross(H(A)) < 0 && (A = A->next())) ||
	       (A->p.cross(H(B)) > 0 && (B = B->r()->o)));
	Q base = connect(B->r(), A);
	if (A->p == ra->p) ra = base->r();
	if (B->p == rb->p) rb = base;

#define DEL(e, init, dir) Q e = init->dir; if (valid(e)) \
		while (circ(e->dir->F(), H(base), e->F())) { \
			Q t = e->dir; \
			splice(e, e->prev()); \
			splice(e->r(), e->r()->prev()); \
			e->o = H; H = e; e = t; \
		}
	for (;;) {
		DEL(lc, base->r(), o);  DEL(rc, base, prev());
		if (!valid(lc) && !valid(rc)) break;
		if (!valid(lc) || (valid(rc) && circ(H(rc), H(lc))))
			base = connect(rc, base->r());
		else
			base = connect(base->r(), lc->r());
	}
	return { ra, rb };
#undef DEL
#undef H
#undef valid
}

vector<P> triangulate(vector<P> pts) {
	sort(pts.begin(), pts.end());
	assert(unique(pts.begin(), pts.end()) == pts.end());
	if ((int)pts.size() < 2) return {};
	Q e = rec(pts).first;
	vector<Q> q = {e};
	int qi = 0;
	while (q.size()) {
		Q c = q.back(); q.pop_back();
		c->mark = 0;
	}
#define ADD { Q c = e; do { c->mark = 1; pts.push_back(c->p); \
	q.push_back(c->r()); c = c->next(); } while (c != e); }
	ADD; pts.clear();
	while (qi < (int)q.size()) if (!(e = q[qi++])->mark) ADD;
	return pts;
}
