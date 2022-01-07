#include<bits/stdc++.h>
using namespace std;


/*
	Calculating Short path distance and path --- Undirected Graph (without weights)
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
	
	void bfs_shortest_path(int source) {
		queue<int> q;
		vector<bool> visited(n, false);
		vector<int> dist(n, 0);
		vector<int> parent(n);
		
		q.push(source);
		visited[source] = true;
		dist[source] = 0;
		parent[source] = source; // = source done for just source node 
		
		while(!q.empty()) {
			int node = q.front();
			cout << node << "  ";			
			q.pop();
			
			// pushing ngbrs of node - node in queue.
			for (auto &ngbr : l[node]) {
				if (!visited[ngbr]) {
					q.push(ngbr);
					visited[ngbr] = true;
					parent[ngbr] = node;
					dist[ngbr] = dist[parent[ngbr]] + 1;
				}				
			}
		}
		
		// print shortest path distance
		cout << "\nShortest Path distance: " << dist[n - 1] << "\n";
		
		// print shortest path
		// as the very first node visited in the level corresponds to the shortest path
		cout << "\nShortest Path (destination node first): ";
		int node = n - 1;
		do {
			cout << node << "  ";
			node = parent[node];
		} while(node != source);
		cout << source << "\n";
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
	
	g.bfs_shortest_path(1);
	
	return 0;
}
