#include<bits/stdc++.h>
using namespace std;

// Algorithm to Find LCA - 2 Pointer Approach

/*
	Time complexity:
		| _ O(V + E) ~ (Time complexity of DFS)

	Space complexity:
		| _ O(V)

*/

class Graph {
	private:
	vector<vector<int>> graph; // [[node] ... ]
	vector<int> depth;
	vector<int> parent;

	int V;

	public:
	Graph(int V) {
		this->V = V;
		graph.resize(V + 1);
		depth.resize(V + 1, 0);
		parent.resize(V + 1);
	}

	void add_edge(int node1, int node2) {
		// undirected graph-
		graph[node1].push_back(node2);
		graph[node2].push_back(node1);
	}

	void dfs(int current_node, int parent_node) {
		parent[current_node] = parent_node;
		depth[current_node] = depth[parent_node] + 1;

		for (auto ngbr : graph[current_node]) {
			if (ngbr != parent_node) {
				dfs(ngbr, current_node);
			}
		}
		return;
	}

	int LCA_2PointerApproach(int u, int v) {
		if (u == v)
			return u;

		// considering depth of u is greater than v
		// if not than swap u, v
		if (depth[u] < depth[v]) {
			swap(u, v);
		}

		// climbing u till it reach to depth of v
		int diff = depth[u] - depth[v];
		while(diff--) {
			u = parent[u];
		}

		// now u and v are at same depth
		// climb up together, till both are equal
		while(u != v) {
			u = parent[u];
			v = parent[v];
		}

		// return any of u or v, as both are same!
		return u;
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

	cout << g.LCA_2PointerApproach(9, 12) << '\n';
	cout << g.LCA_2PointerApproach(10, 8) << '\n';
	cout << g.LCA_2PointerApproach(9, 11) << '\n';
	return 0;
}