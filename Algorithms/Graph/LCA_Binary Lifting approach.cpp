#include<bits/stdc++.h>
using namespace std;

// Algorithm to Find LCA - binary lifting
/* Reference: https://cp-algorithms.com/graph/lca_binary_lifting.html
	| _ this implementation is best ... as it solves one sub-problem whehter one node is_ancestor? of other node!!!
*/

/*
	Time complexity:
		| _ O(N * log(N)) == implementation
		| _ O(log(N)) for each query

	Space complexity:
		| _ O(V + V * log(N))

*/

class Graph {
	private:
	vector<vector<int>> graph; // [[node] ... ]
	vector<int> depth;
	vector<vector<int>> parent;

	int V;
	int L;

	public:
	Graph(int V) {
		this->V = V;
		this->L = ceil(log2(V + 1));
		graph.resize(V + 1);
		depth.resize(V + 1, 0);
		parent.assign(V + 1, vector<int>(L + 1));
	}

	void add_edge(int node1, int node2) {
		// undirected graph-
		graph[node1].push_back(node2);
		graph[node2].push_back(node1);
	}

	void dfs(int current_node, int parent_node) {
		depth[current_node] = depth[parent_node] + 1;
		parent[current_node][0] = parent_node;

		for (int j = 1; j <= L; j++) {
			parent[current_node][j] = parent[parent[current_node][j - 1]][j - 1];
		}

		for (auto ngbr : graph[current_node]) {
			if (ngbr != parent_node) {
				dfs(ngbr, current_node);
			}
		}
		return;
	}

	int LCA_BinaryLiftingApproach(int u, int v) {
		if (u == v)
			return u;

		// considering depth of u is greater than v
		// if not than swap u, v
		if (depth[u] < depth[v]) {
			swap(u, v);
		}

		// climbing u till it reach to depth of v
		int diff = depth[u] - depth[v];
		for (int j = L + 1; j >= 0; j--) {
			if ((diff >> j) & 1) {
				u = parent[u][j];
			}
		}

		// now u and v are at same depth
		for (int j = L + 1; j >= 0; j--) {
			if (parent[u][j] != parent[v][j]) {
				u = parent[u][j];
				v = parent[v][j];
			}
		}

		return parent[u][0];
	}
};

int main() {

	Graph g(12);
	g.add_edge(1, 2);
	g.add_edge(1, 3);
	g.add_edge(2, 4);
	g.add_edge(2, 5);
	g.add_edge(2, 6);
	g.add_edge(4, 10);
	g.add_edge(5, 8);
	g.add_edge(8, 9);
	g.add_edge(8, 11);
	g.add_edge(3, 7);
	g.add_edge(7, 12);

	g.dfs(1, 0);

	cout << g.LCA_BinaryLiftingApproach(9, 12) << '\n';
	cout << g.LCA_BinaryLiftingApproach(10, 8) << '\n';
	cout << g.LCA_BinaryLiftingApproach(9, 11) << '\n';
	return 0;
}