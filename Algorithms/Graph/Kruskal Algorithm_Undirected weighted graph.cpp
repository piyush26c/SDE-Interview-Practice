#include<bits/stdc++.h>
using namespace std;

// Kruskal Algorithm
/*
	Time complexity:
		| _ O(E*Log(E))	   -- if E < V(V - 1) / 2
		| _ O(E*Log(V))	   -- if E ~ V(V - 1) / 2 = V^2
		
	Space complexity:
		| _ O(V + E)

*/

class DSU {
	private:
	vector<int> parent;
	vector<int> rank;
	
	public:
	DSU(int n) {
		parent.resize(n + 1);	// + 1 because node numbering is from 1 not from 0!
		rank.resize(n + 1);
		fill(rank.begin(), rank.end(), 1);
		fill(parent.begin(), parent.end(), -1);
	}
	
	int find_set(int node) {
		if (parent[node] == -1) {
			return node;
		}
		return parent[node] = find_set(parent[node]);
	}
	
	void union_set(int node1, int node2) {
		// rank compression method
		
		int s1 = find_set(node1);
		int s2 = find_set(node2);

		if (s1 != s2) {
			if (rank[s1] < rank[s2]) {
			parent[s1] = s2;
			rank[s2] += rank[s1];
			} else {
				parent[s2] = s1;
				rank[s1] += rank[s2];
			}
		}		
	}	
};

class Graph {
	private:
	vector<vector<int>> edgeList; // [[weight, node1, node2] ... ]
	int V;
	
	public:
	Graph(int V) {
		this->V = V;
	}
	
	void add_edge(int node1, int node2, int weight) {
		edgeList.push_back({weight, node1, node2});		
	}
	
	int kruskalAlgorithm() {
		int pathLength = 0; // should be minimum :)
		
		DSU aDSU(V);
		
		// 1. sort all edges based upon weight	
		sort(edgeList.begin(), edgeList.end());
		
		for (auto &edge : edgeList) {
			int weight = edge[0];
			int node1_ = edge[1];
			int node2_ = edge[2];
			
			if (aDSU.find_set(node1_) != aDSU.find_set(node2_)) {
				aDSU.union_set(node1_, node2_);
				pathLength += weight;
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
	
	cout << "Minimum Spanning Tree pathLength (Kruskal Algorithm): " << g.kruskalAlgorithm() << "\n";	// answer: 43
	return 0;
}