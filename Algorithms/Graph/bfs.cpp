#include<bits/stdc++.h>
using namespace std;

/*
	Time complexity:
		| _ adjacency list:
			| _ O(V + E)
		| _ adjacency matrix:
			| _ O(V^2)

	Space complexity:
		| _ adjacency list:
			| _ O(V)
		| _ adjacency matrix:
			| _ O(V^2)
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
		if (undir) {
			l[to].push_back(from);
		}
	}
	
	void bfs(int source) {
		queue<int> q;
		vector<bool> visited(n, false);
		
		q.push(source);
		visited[source] = true;
		
		while(!q.empty()) {
			int node = q.front();
			cout << node << "  ";
			q.pop();
			
			// pushing ngbrs of node - node in queue.
			for (auto &ngbr : l[node]) {
				if (!visited[ngbr]) {
					q.push(ngbr);
					visited[ngbr] = true;
				}
				
			}
		}		
	}
	
};

int main(){
	Graph g(7);
	g.addEdge(0,1);
	g.addEdge(1,2);
	g.addEdge(2,3);
	g.addEdge(3,5);
	g.addEdge(5,6);
	g.addEdge(4,5);
	g.addEdge(0,4);
	g.addEdge(3,4);
	g.bfs(1);
	
	return 0;
}
