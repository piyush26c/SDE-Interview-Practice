#include<bits/stdc++.h>
using namespace std;
/*
 TOPOLOGICAL SORT - DFS(RECURSIVE) | can also be done by iterative way
															| _ first put all nodes whose indegree = 0 in stack, 
																pop out -> add in list(push_back) and with that add 
																neighbours of poped node in stack.
*/
class Graph {
	int n;	// number of nodes
	list<int> *graph;	// pointer because initially we don't know the number of nodes in graph
	
	public:
	Graph(int _n) : n(_n) {
		graph = new list<int>[n];
	}
	
	void addEdge(int from, int to) {
		graph[from].push_back(to);		
	}
	
	void dfs_topological_sort(int node, vector<bool> &visited, list<int> &ordering) {
		visited[node] = true;
		
		for (auto &ngbr : graph[node]) {
			if (!visited[ngbr]) {
				dfs_topological_sort(ngbr, visited, ordering);
			}
		}
		
		ordering.push_front(node);
		return;		
	}
	
	list<int> topological_sort() {
		vector<bool> visited(n, false);
		list<int> ordering;
		
		// we call dfs from every row if not visited, this provision is made if graph contains multiple compoinenets
		for (int i = 0; i < n; i++) {
			if (!visited[i]) {
				dfs_topological_sort(i, visited, ordering);
			}
		}
		
		return ordering;
	}
};

int main(){
	Graph g(6);
	g.addEdge(0, 2);
	g.addEdge(2, 3);
	g.addEdge(3, 5);
	g.addEdge(4, 5);	
	g.addEdge(1, 4);
	g.addEdge(1, 2);
	
	vector<int> sortedOrder = g.topological_sort();
	
	// print order
	for (auto node : sortedOrder) {
		cout << node << " ";
	}
	cout << "\n";
	return 0;
}