#include<bits/stdc++.h>
using namespace std;

// https://cp-algorithms.com/graph/all-pair-shortest-path-floyd-warshall.html#description-of-the-algorithm

/*
	Floyd Warshall Algorithm
		| _ APSP
		| _ work for "POSITIVE" & "NEGATIVE" weights

	Time complexity: O(V^3)

*/

const int INF = INT_MAX;


class Graph {

	int V;	// number of nodes
	vector<vector<int>> graph;
	vector<vector<int>> restorePath;


	public:
	Graph(int V) {
		this->V = V;
		graph.resize(V + 1, vector<int>(V + 1, INF));
		restorePath.resize(V + 1, vector<int>(V + 1, -1));

		for (int i = 1; i <= V; i++) {
			restorePath[i][i] = 0;
			graph[i][i] = 0;
		}
	}

	void addEdge() {
		int ip = 1;
		do {
			int u, v, cost;
			cout << "\nEnter u: ";
			cin >> u;
			cout << "\nEnter v: ";
			cin >> v;
			cout << "\nEnter cost: ";
			cin >> cost;

			graph[u][v] = cost;

			cout << "\nEnter another edge ? 0/1";
			cin >> ip;
		} while(ip);
	} // end-addEdge

	vector<vector<int>> FloydWarshall() {
		vector<vector<int>> distance(graph);

		// Phase loop, here in kth phase we include 1, 2, 3, ... k as an intermediate vertices
		for (int k = 1; k <= V; k++) {
			for (int i = 1; i <= V; i++) {
				for (int j = 1; j <= V; j++) {
					if ((distance[i][k] < INF) && (distance[k][j] < INF) && ((distance[i][k] + distance[k][j]) < distance[i][j])) {
						// distance[i][j] = min(distance[i][j], distance[i][k] + distance[k][j]); // commented for restorePath
						distance[i][j] = distance[i][k] + distance[k][j];
						restorePath[i][j] = k;
					}
				}
			}
		}

		return distance;
	}

	void getPath(int from, int to, vector<int> &path) {
		if (from == to) return;

		if (restorePath[from][to] != -1) {
			getPath(from, restorePath[from][to], path);
			getPath(restorePath[from][to], to, path);
		} else {
			path.push_back(to);
		}

		return;
	} // end-getPath

}; // end-Graph

int main(){
	int V;
	cout << "\nEnter number of Vertices (V): ";
	cin >> V;

	Graph g(V);
	g.addEdge();

	vector<vector<int>> dist = g.FloydWarshall();

	cout << "\nDistance Matrix: \n";
	for (int i = 1; i <= V; i++) {
		for (int j = 1; j <= V; j++) {
			cout << dist[i][j] << " ";
		}
		cout << "\n";
	}

	for (int i = 1; i <= V; i++) {
		for (int j = 1; j <= V; j++) {
			vector<int> path;
			path.push_back(i);
			g.getPath(i, j, path);

			cout << "\nPath from : " << i << " to : " << j << "\n";
			for (auto node : path)
				cout << node << " ";
			cout << "\nDistance: " << dist[i][j];
			cout << "\n";
			path.clear();
		}

	} // end-for

	return 0;
} // end-main

/*
test case - 1 (as per leetcode playground)
4
2
1
4
1
1
3
-2
1
3
4
2
1
4
2
-1
1
2
3
3
0
*/

/*
0	INF	-2	INF 
4	0	3	INF 
INF	INF	0	2 
INF	-1	INF	0 
*/