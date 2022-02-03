#include<bits/stdc++.h>
using namespace std;

/*
	DSU - Disjoint Set Union  -- Undirected Graph - [[ UNION BY RANK(union_set()) && PATH COMPRESSION(find_set())]] - {optimized code}
*/

// cycle detection code for undirected graph
// Reference: https://cp-algorithms.com/data_structures/disjoint_set_union.html

/*
	find_set() - Time complexity
					| _ Worst case = 1st call = O(log(n)))
					| _ Average case = O(1)

	union_set() - Time complexity = O(V)

	Space complexity: O(V)
*/

class DSU {
	private:
	vector<int> dsu;
	
	public:	   
	DSU() {		   
	}
	
	DSU(int size) {
		dsu.resize(size);
		fill(dsu.begin(), dsu.end(), -1);
	}
	
	int find_set(int node) {
		if (dsu[node] < 0) {
			return node;
		}
		return dsu[node] = find_set(dsu[node]);	// path compression optimization
	}
		
	/*
	using rank (group size) here. When we have a non-negative value in dsu, it's a link to the parent. 
	Parents has a negative value which is the size of the group.	
	*/
	void union_set(int node1, int node2) {
		int s1 = find_set(node1);
		int s2 = find_set(node2);

		if (dsu[s1] > dsu[s2]) {
			swap(s1, s2);
		}
		
		dsu[s1] += dsu[s2];
		dsu[s2] = s1;		
	}
};

class Graph : public DSU {
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

	bool contains_cycle() {
		// nodes numbering starting from 0		  
		DSU aDSU(V);

		for (auto &edge : graph) {
			int node1 = edge.first;
			int node2 = edge.second;

			int s1 = aDSU.find_set(node1);
			int s2 = aDSU.find_set(node2);

			if (s1 != s2) {
				aDSU.union_set(s1, s2);
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
	// g.add_edge(4, 0);

	cout << "Graph contains cycle? " << (g.contains_cycle() ? "Yes" : "No") << "\n";

	return 0;
}