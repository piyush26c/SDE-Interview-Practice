#include<bits/stdc++.h>
using namespace std;

// Prims Algorithm
/*
	Time complexity:
		| _ O(E*Log(E))	   -- if E < V(V - 1) / 2
		| _ O(E*Log(V))	   -- if E ~ V(V - 1) / 2 = V^2
		
	Space complexity:
		| _ O(V + E)

*/

class Graph {
	int V;
	vector<vector<pair<int, int>> graph;
	
	public:
	Graph(int n) {
		V = n;
		graph.resize(V + 1);
	}
	
	void add_edge(int node1, int node2, int weight) {
		graph[node1].push_back({node2, weight});
		graph[node2].push_back({node1, weight});
	}
	
	int MST_Prims(int source) {
		int pathLength = 0; // should be minimum :)
		
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> pQueue;
		vector<bool> visited(V + 1, false); // +1 for as node starts from 1
		
		pQueue.push({0, source}); // first: weight; second: node
		
		while(!pQueue.empty()) {
			auto best = pQueue.front(); // best here is node having minimum weight and is unvisited
			pQueue.pop();
			
			int to = best.second;
			int weight = best.first;
			
			if (visited[to]) {
				// discard the edge and continue | this is needed for those nodes who didn't carry minimum weight and remain present in pQueue and last even after MST we had got.
				continue;
			}
			
			pathLength += weight;
			visited[to] = true;
			
			// add new edges to pQueue
			for (auto &edge : graph[to]) {
				if (!visited[edge.first]) {
					pQueue.push({edge.second, edge.first});
				}
			}			
		}
		
		return pathLength;
	}
};


int main() {
	
	Graph g(9);
	g.add_edge(1, 2, 10);
	g.add_edge(1, 3, 12);
	g.add_edge(2, 3, 9);
	g.add_edge(2, 4, 8);
	g.add_edge(4, 5, 7);
	g.add_edge(5, 3, 3);
	g.add_edge(5, 6, 3);
	g.add_edge(3, 6, 1);
	g.add_edge(4, 6, 10);
	g.add_edge(4, 7, 8);
	g.add_edge(4, 8, 5);
	g.add_edge(6, 8, 6);
	g.add_edge(7, 8, 9);
	g.add_edge(7, 9, 2);
	g.add_edge(8, 9, 11);
	
	cout << "Minimum Spanning Tree pathLength: " << g.MST_Prims(1) << "\n";	// answer: 43
	return 0;
}