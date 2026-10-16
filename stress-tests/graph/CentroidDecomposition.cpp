#include "../utilities/template.h"
#include "../utilities/random.h"

#include "../../content/graph/CentroidDecomposition.h"

void test(const vector<vi>& adj) {
	auto original = adj;
	CentroidDecomposition cd(adj);
	assert(adj == original);
	int n = sz(adj), root = -1;
	vi children(n), nodes(n);
	iota(all(nodes), 0);
	rep(v,0,n) {
		int p = cd.par[v];
		assert(p >= -1 && p < n && p != v);
		if (p == -1) { assert(root == -1); root = v; }
		else children[p]++;
	}
	function<void(int, vi)> check = [&](int c, vi comp) {
		assert(find(all(comp), c) != comp.end());
		vi seen(n, 1);
		for (int v : comp) seen[v] = 0;
		seen[c] = 1;
		int parts = 0;
		for (int v : comp) if (!seen[v]) {
			vi part{v}; seen[v] = 1;
			rep(i,0,sz(part)) for (int u : adj[part[i]])
				if (!seen[u]) { seen[u] = 1; part.push_back(u); }
			assert(2 * sz(part) <= sz(comp));
			int child = -1;
			for (int u : part) if (cd.par[u] == c) {
				assert(child == -1); child = u;
			}
			assert(child != -1);
			check(child, part);
			parts++;
		}
		assert(parts == children[c]);
	};
	if (n) { assert(root != -1); check(root, nodes); }
}

int main() {
	test({});
	rep(n,1,201) rep(type,0,4) {
		vector<vi> adj(n);
		rep(v,1,n) {
			int p = type == 0 ? v-1 : type == 1 ? 0 :
				type == 2 ? (v-1)/2 : randRange(v);
			adj[v].push_back(p); adj[p].push_back(v);
		}
		test(adj);
	}
	rep(it,0,5000) {
		int n = randRange(1, 101);
		vi labels(n); iota(all(labels), 0); shuffle_vec(labels);
		vector<vi> adj(n);
		rep(v,1,n) {
			int a = labels[v], b = labels[randRange(v)];
			adj[a].push_back(b); adj[b].push_back(a);
		}
		for (auto& edges : adj) shuffle_vec(edges);
		test(adj);
	}
	cout << "Tests passed!" << endl;
}
