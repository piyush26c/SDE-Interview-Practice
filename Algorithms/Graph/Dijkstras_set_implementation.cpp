#include<bits/stdc++.h>
using namespace std;

/*
	Dijkstras Algorithm
		| _ SSSP
		| _ only work for "POSITIVE" weights

/*
	Time complexity: O(E * log(E))
								| _ if E ~ V*(V - 1) == E ~ V^2
					
					= O(E * log(V))
*/

const int INF = INT_MAX;

class Graph {

	int V;	// number of nodes
	vector<vector<pair<int, int>>> graph;	// pointer because initially we don't know the number of nodes in graph
	vector<int> restorePath;	// stores the shortest path from source to "to" node
	int source;

	public:
	Graph(int V, int source) {
		this->V = V;
		this->source = source;
		graph.resize(V);
		restorePath.resize(V);
	}

	void addEdge(int node1, int node2, int weight) {
		graph[node1].push_back({node2, weight});
		graph[node2].push_back({node1, weight});
	} // end-addEdge

	void Dijkstra() {
		vector<int> distance(V, INF);
		set<pair<int, int>> S;

		// initialization
		S.insert({0, source}); // {weight, source_node}
		distance[source] = 0;
		restorePath[source] = source;

		while(!S.empty()) {
			auto best = S.begin();

			int distanceTillNow = best->first;
			int from = best->second;
			S.erase(best);	// O(log(V))

			for (auto [to, toWeight] : graph[from]) {

				if ((distanceTillNow + toWeight) < distance[to]) {
					// remove if "to" already exists in S
					auto toFound = S.find({distance[to], to});
					if (toFound != S.end()) {
						S.erase(toFound);
					} // end-if

					distance[to] = distanceTillNow + toWeight;
					S.insert({distance[to], to});

					restorePath[to] = from;
				} // end-if
			} // end-for
		} // end-while

		for (int i = 0; i < V; i++) {
			cout << "\nNode: " << i << " Cost: " << distance[i];
		} // end-for
		return;
	} // end-Dijkstra

	void getPath(int to) {
		vector<int> path;

		for (int i = to; i != source; ) {
			path.push_back(i);
			i = restorePath[i];
		} // end-for

		path.push_back(source);

		reverse(path.begin(), path.end());

		cout << "\nShortest Path from " << source << " to " << to << " : ";
		for(auto node : path) {
			cout << node << " ";
		} // end-for
		return;
	} // end-getPath

}; // end-Graph

int main(){
	int V = 9;
	int source = 0;
	Graph g(V, source);
	g.addEdge(0, 1, 4);
	g.addEdge(0, 7, 8);
	g.addEdge(1, 7, 11);
	g.addEdge(1, 2, 8);
	g.addEdge(7, 8, 7);
	g.addEdge(7, 6, 1);
	g.addEdge(2, 8, 2);
	g.addEdge(8, 6, 6);
	g.addEdge(6, 5, 2);
	g.addEdge(2, 5, 4);
	g.addEdge(2, 3, 7);
	g.addEdge(3, 5, 14);
	g.addEdge(3, 4, 9);
	g.addEdge(5, 4, 10);

	g.Dijkstra();

	for (int i = source + 1; i < V; i++) {
		g.getPath(i);
	} // end-for

	return 0;
} // end-main

/*
	Instead of set<pair<int, int>> we can use priority_queue<pair<int, int>, vector<pair<int ,int>>, greater<pair<int, int>>>
	but priority_queue won't update the existing nodes weight in queue it will insert another pair (updated with weight)
	and bcz of this priority_queue will contain unnecessary nodes thus led to increase space an time complexity.
*/


/*
test case - 1

int V = 9;
int source = 0;
Graph g(V, source);
g.addEdge(0, 1, 4);
g.addEdge(0, 7, 8);
g.addEdge(1, 7, 11);
g.addEdge(1, 2, 8);
g.addEdge(7, 8, 7);
g.addEdge(7, 6, 1);
g.addEdge(2, 8, 2);
g.addEdge(8, 6, 6);
g.addEdge(6, 5, 2);
g.addEdge(2, 5, 4);
g.addEdge(2, 3, 7);
g.addEdge(3, 5, 14);
g.addEdge(3, 4, 9);
g.addEdge(5, 4, 10);


test case - 2

int V = 5;
int source = 0;
Graph g(V, source);
g.addEdge(0, 1, 1);
g.addEdge(0, 2, 4);
g.addEdge(0, 3, 7);
g.addEdge(1, 2, 1);
g.addEdge(2, 3, 2);
g.addEdge(3, 4, 3);
*/