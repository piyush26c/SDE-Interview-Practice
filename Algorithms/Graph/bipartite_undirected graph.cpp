#include<bits/stdc++.h>
using namespace std;

class Graph {
    int n;	// number of nodes
    list<int> *l;	// pointer because initially we don't know the number of nodes in graph
    
    public:
    Graph(int _n) : n(_n) {
		l = new list<int>[n];
	}
	
	void addEdge(int from, int to) {
		l[from].push_back(to);
        l[to].push_back(from);		
	}
	
	bool dfs_helper(int node, int parent, vector<int> &visited, int color) {
		visited[node] = color;
		
		for (auto &ngbr : l[node]) {
			if (visited[ngbr] == 0) {
				bool subProb = dfs_helper(ngbr, node, visited, 3 - color);	// 3 - color is the best technique to flip 1 -> 2 or 2 -> 1
				if (!subProb) {
					return false;
				}
			} else if (ngbr != parent && visited[ngbr] == color) {
				return false;
			}
		}		
		return true;
	}
	
	//we can apply BFS or DFS, by coloring the nodes at each step (current node has color 1, ngbr should have a color 2)
	bool dfs() {
		
		vector<int> visited(n, 0);	// 0 - not visited | 1 - visited & color = 1 | 2 - visited & color = 2
		int color = 1;
		
		for (int i = 0; i < n; i++) {
			if (visited[i] == 0) {
				if(!dfs_helper(i, -1, visited, color)) {
					return false;
				}
			}
		}
		return true;		
	}	
};

int main(){
	Graph g(9);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 3);
	g.addEdge(2, 4);
	g.addEdge(3, 4);
	// g.addEdge(5, 6);
	// g.addEdge(6, 7);
	// g.addEdge(7, 8);
	// g.addEdge(8, 5);
    
	cout << "Is graph Bipartite?\nAns. " << g.dfs() << "\n";
	return 0;
}
