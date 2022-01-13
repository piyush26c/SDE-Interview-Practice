#include<bits/stdc++.h>
using namespace std;

/*
	below code [[will]]  work if graph as more than one components (means) a graph is composition of two or more connected graphs, but itself not a single componenet(akhand graph nahi aahe) !!!
*/

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
	
	bool dfs(int node, vector<bool> &visited, int parent) {
		visited[node] = true;
		
		for(auto &ngbr : l[node]) {
			if (!visited[ngbr]) {
				bool ngbrFoundACycle = dfs(ngbr, visited, node);
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
		for (int i = 0; i < n; i++) {
			if(!visited[i]) {
				if(dfs(i, visited, -1)) {
					return true;
				}
			}
		}
		return false;
	}		
};

int main(){
	Graph g(6);
	g.addEdge(0,1);
	g.addEdge(1,2);
	g.addEdge(3,4);
	g.addEdge(4,5);
	g.addEdge(3,5);

	cout << "Graph contains cycle ?\nAns. " << g.containsCycle() << "\n";
	return 0;
}