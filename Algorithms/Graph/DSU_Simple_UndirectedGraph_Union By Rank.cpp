#include<bits/stdc++.h>
using namespace std;

/*
	DSU - Disjoint Set Union  -- Undirected Graph - [[ UNION BY RANK ]]
*/

// cycle detection code for undirected graph
// Reference: https://cp-algorithms.com/data_structures/disjoint_set_union.html


/*
	find_set() - Time complexity == < O(V)
	union_set() - Time complexity = O(V) - Ranking will mitigate O(V) time complexity of find_set()
	
	Space complexity: O(V)
*/

class Graph {
	private:
	int V;
	list<pair<int, int>> graph; // known as "Edge List" representation
	
	public:
	Graph(int V) {
		this->V = V;
	}
	
	void add_edge(int node1, int node2) {
		graph.push_back(make_pair(node1, node2)); // undirected graph
	}
	
	int find_set(int node, vector<int> &parent) {
		if (parent[node] == -1) {
			return node;
		}		
		return find_set(parent[node], parent);
	}
	
	void union_set(int node1, int node2, vector<int> &parent, vector<int> &rank) {
		int s1 = find_set(node1, parent);
		int s2 = find_set(node2, parent);
		
		if (rank[s1] < rank[s2]) {
			parent[s1] = s2;
			rank[s2] += rank[s1];
		} else {
			parent[s2] = s1;
			rank[s1] += rank[s2];
		}
	}
	
	bool contains_cycle() {
		// DSU logic to check whether graph contains cycle or not
		vector<int> parent(V, -1);	// nodes numbering starting from 0
		vector<int> rank(V, 1);
		
		for (auto &edge : graph) {
			int node1 = edge.first;
			int node2 = edge.second;
			
			int s1 = find_set(node1, parent);
			int s2 = find_set(node2, parent);
			
			if (s1 != s2) {
				union_set(s1, s2, parent, rank);
			} else {
				cout << "\nNode: " << node1 << " Node: " << node2 << " forms a cycle\n";
				return true;
			}			
		}
		return false;
	}
};

int main() {
	Graph g(5);
	g.add_edge(0, 1);
	g.add_edge(1, 2);
	g.add_edge(2, 3);
	g.add_edge(3, 4);
	g.add_edge(4, 0);
	
	cout << "Graph contains cycle? " << (g.contains_cycle() ? "Yes" : "No") << "\n";
	
	return 0;
}