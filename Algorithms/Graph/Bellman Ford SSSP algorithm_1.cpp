#include<bits/stdc++.h>
using namespace std;

// https://cp-algorithms.com/graph/bellman_ford.html

/*
	Bellman Ford Algorithm - simple (no optimization)
		| _ SSSP
		| _ work for "POSITIVE" & "NEGATIVE" weights

	Time complexity: O(V * E)

*/

const int INF = INT_MAX;

class Edge {
	public:
	int u;
	int v;
	int weight;

	Edge(int u, int v, int weight) {
		this->u = u;
		this->v = v;
		this->weight = weight;
	}
};

class Graph {

	int V;	// number of nodes
	vector<Edge> graph;
	vector<int> restorePath;	// stores the shortest path from source to "to" node
	int source;

	public:
	Graph(int V, int source) {
		this->V = V;
		this->source = source;
		restorePath.resize(V);
	}

	void addEdge(int node1, int node2, int weight) {
		graph.push_back(Edge(node1, node2, weight));
	} // end-addEdge


	vector<int> BellmanFord() {
		vector<int> distance(V, INF);
		distance[source] = 0;
		restorePath[source] = source;

		// relaxation for V - 1 times
		for (int i = 1; i <= V - 1; i++) {

			for (auto edge : graph) {
				if ((distance[edge.u] != INF) && (distance[edge.u] + edge.weight < distance[edge.v])) {
					distance[edge.v] = distance[edge.u] + edge.weight;
					restorePath[edge.v] = edge.u;
				}
			}
		}

		// checking for negative weight cycle : Vth iteration
		for (auto edge : graph) {
			if ((distance[edge.u] != INF) && (distance[edge.u] + edge.weight < distance[edge.v])) {
				cout << "\nNegative Weight Cycle is present!!!";
				exit(0);
			}
		}
		return distance;
	} // end-BellmanFord-1

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
	int V = 5;
	int source = 0;
	Graph g(V, source);
	g.addEdge(0, 1, -1);
	g.addEdge(0, 2, 4);
	g.addEdge(1, 2, 3);
	g.addEdge(1, 3, 2);
	g.addEdge(3, 1, 1);
	g.addEdge(3, 2, 5);
	g.addEdge(4, 3, -3);
	g.addEdge(1, 4, 2);

	vector<int> dist = g.BellmanFord();

	for (int i = source + 1; i < V; i++) {
		g.getPath(i);
		cout << "  Distance: " << dist[i];
	} // end-for

	return 0;
} // end-main


/*
test case - 1

int V = 3;
int source = 0;
Graph g(V, source);
g.addEdge(0, 1, 3);
g.addEdge(1, 2, 4);
g.addEdge(0, 2, -10);


test case - 2 (negative weight cycle is present)

int V = 3;
int source = 0;
Graph g(V, source);
g.addEdge(0, 1, 3);
g.addEdge(1, 2, 4);
g.addEdge(2, 0, -10);

test case - 3 (taken from gfg)

int V = 5;
int source = 0;
Graph g(V, source);
g.addEdge(0, 1, -1);
g.addEdge(0, 2, 4);
g.addEdge(1, 2, 3);
g.addEdge(1, 3, 2);
g.addEdge(3, 1, 1);
g.addEdge(3, 2, 5);
g.addEdge(4, 3, -3);
g.addEdge(1, 4, 2);
*/