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
	}

	bool bfs(int source, vector<bool> &visited) {
		// return true if backedge is found, else false
		
		vector<bool> isInCurrentPath(n, false);	// isInCurrentPath track the nodes which are in current path
		queue<int> q;
		
		q.push(source);		
		visited[source] = true;
		
		while(!q.empty()) {
			int node = q.front();
			q.pop();
			isInCurrentPath[node] = true;
			
			for (auto &ngbr : l[node]) {
				if (!visited[ngbr]) {
					q.push(ngbr);
					visited[ngbr] = true;
				} else if (isInCurrentPath[ngbr]) {
					return true;
				}
			}
			isInCurrentPath[node] = false;
		}		
		return false;
	}
	
	bool containsCycle() {
		vector<bool> visited(n, false);
				
		bool ans = false;
		
		// this loop is made because to check for other components (when graph is not a single component)
		for (int i = 0; i < n; i++) {
			int source = i;
			if (!visited[source]) {
				ans = bfs(source, visited);
				if (ans) break;
			}
		}
		return ans;
	}		
};

int main(){
	Graph g(10);
	g.addEdge(0,1);
	g.addEdge(1,2);
	g.addEdge(2,3);
	g.addEdge(0,3);
	g.addEdge(0,4);
	g.addEdge(0,5);
	g.addEdge(4,5);
	g.addEdge(6,7);
	g.addEdge(7,8);
	g.addEdge(8,9);
	g.addEdge(9,6);

	cout << "Directed Graph contains cycle ?\nAns. " << g.containsCycle() << "\n";
	return 0;
}