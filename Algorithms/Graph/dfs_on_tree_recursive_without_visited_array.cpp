#include<bits/stdc++.h>
using namespace std;
// DFS on Tree [without using visited array]

// NOTE: Input must be a "T.R.E.E"
/*
	Time complexity:
		| _ adjacency list:
			| _ O(V + E)		

	Space complexity:
		| _ adjacency list:
			| _ O(V)		
*/

class Graph {
	int V;	// number of nodes
	vector<vector<int>> graph;

	public:
	Graph(int _n) {
		this->V = _n;
		graph.resize(V + 1);
	}

	void addEdge(int from, int to, bool undir = true) {
		graph[from].push_back(to);
		if (undir) {
			graph[to].push_back(from);
		}
	}

	void dfsHelper(int current_node, int parent_node) {
		cout << current_node << " ";

		for (auto ngbr : graph[current_node]) {
			if (ngbr != parent_node) {
				dfsHelper(ngbr, current_node);
			}
		}
		return;
	}

	void dfs() {
		int source_node = 1; // node number starting from 1
		int parent_node = -1;
		dfsHelper(source_node, parent_node);
		return;
	}
};

int main(){
	Graph g(6);
	g.addEdge(1,2);
	g.addEdge(1,3);
	g.addEdge(2,6);
	g.addEdge(3,4);
	g.addEdge(3,5);

	g.dfs();
	return 0;
}
/*
	| _ all nodes are visited in DFS traversal
	| _ each branch is explored and then next is being taken into execution
*/