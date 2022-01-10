#include<bits/stdc++.h>
using namespace std;

/*
	Time complexity:
		| _ adjacency list:
			| _ O(V + E)
		| _ adjacency matrix:
			| _ O(V^2)

	Space complexity:
		| _ adjacency list:
			| _ O(V)
		| _ adjacency matrix:
			| _ O(V^2)
*/

class Graph {
    int n;	// number of nodes
    list<int> *graph;	// pointer because initially we don't know the number of nodes in graph
    
    public:
    Graph(int _n) : n(_n) {
		graph = new list<int>[n];
	}
	
	void addEdge(int from, int to, bool undir = true) {
		graph[from].push_back(to);
		if (undir) {
			graph[to].push_back(from);
		}
	}
	
	void dfsHelper(int node, vector<bool> &visited) {
		visited[node] = true;
		
		cout << node << " ";
		
		for (auto &ngbr : graph[node]) {
			if (!visited[ngbr]) {
				dfsHelper(ngbr, visited);
			}
		}		
		return;
	}
	
	void dfs(int source) {
		vector<bool> visited(n, false);
		dfsHelper(source, visited);
		return;
	}
};

int main(){
	Graph g(7);
	g.addEdge(0,1);
	g.addEdge(1,2);
	g.addEdge(2,3);
	g.addEdge(3,5);
	g.addEdge(5,6);
	g.addEdge(4,5);
	g.addEdge(0,4);
	g.addEdge(3,4);
	
	g.dfs(0);
	return 0;
}


/*
	| _ all nodes are visited in DFS traversal
	| _ each branch is explored and then next is being taken into execution
*/