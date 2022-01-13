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
	
	bool dfs(int node, vector<bool> &visited, vector<bool> &isInCurrentPath) {
        visited[node] = true;
        isInCurrentPath[node] = true;
        
        for(auto &ngbr : l[node]) {
            if (!visited[ngbr]) {
                bool ngbrCycleFound = dfs(ngbr, visited, isInCurrentPath);
                if (ngbrCycleFound) {
                    return true;
                }
            } else if (isInCurrentPath[ngbr]) {
                return true;
            }
        }
        
        isInCurrentPath[node] = false;
        return false;        
    }
	
	bool containsCycle() {
		vector<bool> visited(n, false);
        vector<bool> isInCurrentPath(n, false);
        bool ans = dfs(0, visited, isInCurrentPath);
        return ans;
	}		
};

int main(){
	Graph g(6);
	g.addEdge(0,1);
	g.addEdge(1,2);
	g.addEdge(2,3);
	g.addEdge(3,0);
	g.addEdge(0,4);
	g.addEdge(0,5);
	g.addEdge(4,5);

	cout << "Directed Graph contains cycle ?\nAns. " << g.containsCycle() << "\n";
	return 0;
}