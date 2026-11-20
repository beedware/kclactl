/**
 * Author: KCLACTL
 * Date: 2026-11-20
 * License: CC0
 * Description: nextGreater gives the index of the next strictly
 * larger value to the right, or $n$. slidingMin gives each
 * complete window's minimum, with window size $k>0$.
 * Each index enters and leaves once. A newer value at most as
 * large can replace an older minimum candidate as it expires later.
 * Time: O(n) each
 * Memory: O(n) stack or O(k) deque, excluding output
 * Status: Compared against direct searches and window scans
 */
#pragma once

vi nextGreater(const vi& a) {
	vi next(sz(a),sz(a)), st;
	rep(i,0,sz(a)) {
		while (!st.empty() && a[st.back()] < a[i]) {
			next[st.back()] = i;
			st.pop_back();
		}
		st.push_back(i);
	}
	return next;
}

vi slidingMin(const vi& a, int k) {
	deque<int> q;
	vi res;
	rep(i,0,sz(a)) {
		if (!q.empty() && q.front() <= i-k) q.pop_front();
		while (!q.empty() && a[q.back()] >= a[i]) q.pop_back();
		q.push_back(i);
		if (i >= k-1) res.push_back(a[q.front()]);
	}
	return res;
}
