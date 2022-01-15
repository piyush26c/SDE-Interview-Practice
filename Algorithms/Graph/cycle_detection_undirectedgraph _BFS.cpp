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
	
	void addEdge(int from, int to) {
		l[from].push_back(to);
		l[to].push_back(from);		
	}
	
	bool bfs(int source, vector<bool> &visited) {
		vector<int> parent(n, -1);
		queue<int> q;
		
		q.push(source);
		visited[source] = true;
		parent[source] = source;
		
		
		while(!q.empty()) {
			int node = q.front();
			q.pop();
			
			// populating queue with node's neighbours(ngbr)
			for (auto &ngbr : l[node]) {
				if (!visited[ngbr]) {                    
					q.push(ngbr);
					visited[ngbr] = true;
					parent[ngbr] = node;
				} else if (ngbr != parent[node]) {
					return true;
				}
			}
		}
		return false;
	}
	
	bool containsCycle() {
		// graph is single component -- means graph is well connected there is not absolute part present
		vector<bool> visited(n, false);
		
		for (int i = 0; i < n; i++) {
			if(!visited[i]) {
				if(bfs(i, visited)) {
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
	g.addEdge(2,3);
	g.addEdge(0,4);
	// g.addEdge(4,5);
	g.addEdge(0,5);

	cout << "Graph contains cycle ?\nAns. " << g.containsCycle() << "\n";
	return 0;
}


/*
Test Case: 1
Graph g(6);
g.addEdge(0,1);
g.addEdge(1,2);
g.addEdge(3,4);
g.addEdge(4,5);
g.addEdge(3,5);
*/