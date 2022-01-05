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
		if (undir) {
			l[to].push_back(from);
		}
	}
	
	void printAdjList() {
		for (int i = 0; i < n; i++) {
			cout << i << "   --------->   ";
			for (auto &node : l[i]) {
				cout << node << ", ";
			}
			cout << "\n";
		}
	}	
};

int main(){
	Graph g(6);
	g.addEdge(0,1);
	g.addEdge(0,4);
	g.addEdge(2,1);
	g.addEdge(3,4);
	g.addEdge(4,5);
	g.addEdge(2,3);
	g.addEdge(3,5);
	g.printAdjList();
	return 0;
}
