#include<bits/stdc++.h>
using namespace std;

class Graph {
    int n;	// number of nodes
    list<int> *l;	// pointer because initially we don't know the number of nodes in graph
    
    public:
    Graph(int _n) : n(_n) {
		l = new list<int>[n];
	}
	
	void addEdge(int from, int to, bool undir = true) {
		l[from].push_back(to);
		l[to].push_back(from);		
	}
	
	int dfs(int node, vector<bool> &visited, int parent) {
		visited[node] = true;
		
		for(auto &ngbr : l[node]) {
			if (!visited[ngbr]) {
				int ngbrFoundACycle = dfs(ngbr, visited, node);
				if (ngbrFoundACycle) {
					return true;
				}
			} 
			/* ngbr is visited and other than parent in the current dfs call, 
			a node is found [in last] that is visited! thus cycle is detected;*/
			else if (ngbr != parent) {
				return true;
			}
		}		
		return false;
	}
	
	bool containsCycle() {
		// graph is single component -- means graph is well connected there is not absolute part present
		vector<bool> visited(n, false);
		return dfs(0, visited, -1);
	}		
};

int main(){
	Graph g(4);
	g.addEdge(0,1);
	g.addEdge(1,2);
	g.addEdge(2,3);

	cout << "Graph contains cycle ?\nAns. " << g.containsCycle() << "\n";
    // Ans. 1 means present and 0 means absent
	return 0;
}