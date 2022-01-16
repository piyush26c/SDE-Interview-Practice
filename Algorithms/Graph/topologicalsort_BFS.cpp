#include<bits/stdc++.h>
using namespace std;

// this algorithm is also known as "Kahn's Algorithm"

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
	
	vector<int> topological_sort() {
		vector<int> sortedOrder;
		vector<int> indegree(n, 0);
		
		// iterate over all edges to find approvpriate indegree of each nodes
		for (int i = 0; i < n; i++) {
			for (auto &ngbr : graph[i]) {
				indegree[ngbr] += 1;
			}
		}
		
		// applying BFS
		queue<int> q;
		
		// initialize q with nodes having indegree 0
		for (int i = 0; i < n; i++) {
			if (indegree[i] == 0) {
				q.push(i);
			}
		}
		
		// BFS code
		while(!q.empty()) {
			int node = q.front();
			sortedOrder.push_back(node);
			q.pop();
			
			// update the indegree of node's neighbours
			for (auto &ngbr : graph[node]) {
				indegree[ngbr] -= 1;
				if (indegree[ngbr] == 0) {
					q.push(ngbr);
				}
			}
		}
		return sortedOrder;
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