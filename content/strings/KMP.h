/**
 * Author: Johan Sannemo
 * Date: 2016-12-15
 * License: CC0
 * Description: pi[i] computes the length of the longest prefix of s that ends at i, other than s[0...i] itself.
 * This is used to find all occurrences of a string.
 * Time: O(n) for pi, O(n + m) for match
 * Status: Tested on kattis:stringmatching
 */
#pragma once

vector<int> pi(const string& s) {
	vector<int> p((int)s.size());
	for (int i = 1; i < (int)s.size(); ++i) {
		int g = p[i-1];
		while (g && s[i] != s[g]) g = p[g-1];
		p[i] = g + (s[i] == s[g]);
	}
	return p;
}

vector<int> match(const string& s, const string& pat) {
	vector<int> p = pi(pat + '\0' + s), res;
	int sz_s = (int)s.size(), sz_p = (int)pat.size();
	for (int i = (int)p.size() - sz_s; i < (int)p.size(); ++i)
		if (p[i] == sz_p) res.push_back(i - 2 * sz_p);
	return res;
}
