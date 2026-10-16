/**
 * Author: KCLACTL
 * Date: 2026-10-16
 * License: CC0
 * Source: folklore
 * Description: Union area of axis-aligned rectangles
 * $(x_1,y_1,x_2,y_2)$, with $x_1 \le x_2$, $y_1 \le y_2$.
 * Sweep x; a segment tree maintains covered y-length.
 * Time: O(N \log N)
 * Status: smoke-tested
 */
#pragma once

struct CoverTree {
	vi y, cnt;
	vector<ll> len;
	CoverTree(vi y) : y(y), cnt(4*sz(y)), len(4*sz(y)) {}
	void add(int a, int b, int d, int v, int l, int r) {
		if (b <= l || r <= a) return;
		int m = (l + r) / 2;
		if (a <= l && r <= b) cnt[v] += d;
		else {
			add(a, b, d, 2*v, l, m);
			add(a, b, d, 2*v+1, m, r);
		}
		len[v] = cnt[v] ? (ll)y[r] - y[l] :
			(r-l == 1 ? 0 : len[2*v] + len[2*v+1]);
	}
};

ll rectUnion(vector<array<int, 4>> rect) {
	vector<array<int, 4>> ev;
	vi y;
	for (auto [x1, y1, x2, y2] : rect) {
		if (x1 == x2 || y1 == y2) continue;
		ev.push_back({x1, y1, y2, 1});
		ev.push_back({x2, y1, y2, -1});
		y.push_back(y1); y.push_back(y2);
	}
	if (ev.empty()) return 0;
	sort(all(ev)); sort(all(y));
	y.erase(unique(all(y)), y.end());
	CoverTree t(y);
	ll area = 0, prev = ev[0][0];
	for (auto [x, lo, hi, d] : ev) {
		area += (x - prev) * t.len[1];
		int a = int(lower_bound(all(y), lo) - y.begin());
		int b = int(lower_bound(all(y), hi) - y.begin());
		t.add(a, b, d, 1, 0, sz(y)-1);
		prev = x;
	}
	return area;
}
