/**
 * Author: KCLACTL
 * Date: 2026-10-16
 * License: CC0
 * Source: folklore
 * Description: Online suffix automaton for lowercase letters.
 * Root is 0; paths from it are exactly the substrings.
 * State v represents lengths (len[link[v]], len[v]].
 * Sum these length differences over non-root states to
 * count distinct nonempty substrings.
 * Time: O(N) construction, O(N) space (fixed alphabet)
 * Status: smoke-tested
 */
#pragma once

struct SuffixAutomaton {
	struct Node {
		int len = 0, link = -1, next[26];
		Node() { fill(next, next+26, -1); }
	};
	vector<Node> st{1};
	int last = 0;
	SuffixAutomaton(string s = "") {
		for (char c : s) extend(c);
	}
	void extend(char c) {
		int x = c - 'a', cur = sz(st), p = last;
		st.emplace_back();
		st[cur].len = st[last].len + 1;
		while (p != -1 && st[p].next[x] == -1) {
			st[p].next[x] = cur;
			p = st[p].link;
		}
		if (p == -1) st[cur].link = 0;
		else {
			int q = st[p].next[x];
			if (st[p].len + 1 == st[q].len) st[cur].link = q;
			else {
				int clone = sz(st);
				st.push_back(st[q]);
				st[clone].len = st[p].len + 1;
				while (p != -1 && st[p].next[x] == q) {
					st[p].next[x] = clone;
					p = st[p].link;
				}
				st[q].link = st[cur].link = clone;
			}
		}
		last = cur;
	}
};
