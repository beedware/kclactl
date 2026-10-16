/**
 * Author: Unknown
 * Date: 2002-09-13
 * Source: predates tinyKACTL
 * Description: Topological sorting. Given is an oriented graph.
 * Output is an ordering of vertices, such that there are edges only from left to right.
 * If there are cycles, the returned list will have size smaller than $n$ -- nodes reachable
 * from cycles will not be returned.
 * Time: $O(|V|+|E|)$
 * Status: stress-tested
 */
#pragma once

vector<int> topoSort(const vector<vector<int>>& gr) {
	vector<int> indeg((int)gr.size()), q;
	for (auto& li : gr) for (int x : li) indeg[x]++;
	for (int i = 0; i < (int)gr.size(); ++i) if (indeg[i] == 0) q.push_back(i);
	for (int j = 0; j < (int)q.size(); ++j) for (int x : gr[q[j]])
		if (--indeg[x] == 0) q.push_back(x);
	return q;
}
