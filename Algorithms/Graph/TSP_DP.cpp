#include<bits/stdc++.h>
using namespace std;

/*
	Travelling Salesman Problem (DP Based Approch)

	Time complexity: O((n^2) * (2^n))
		| _ total-subproblems = (2 ^ n) * n
									| _ because DP table has this [] (2 * n) * n ] entries!
		| _ time taken by each sub-problem to solve = O(n)
	
	-- this is exponential but better than brute-force = (n - 1)!
*/

const int INF = INT_MAX;


class Graph {

	int V;	// number of nodes
	vector<vector<int>> graph;

	public:
	Graph(int V) {
		this->V = V;
		graph.resize(V, vector<int>(V, INF));

		for (int i = 0; i < V; i++)
			graph[i][i] = 0;
	}

	void addEdge(bool unDirected = true) {
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

			if (unDirected) {
				graph[v][u] = cost;
			}

			cout << "\nEnter another edge ? 0/1";
			cin >> ip;
		} while(ip);
	} // end-addEdge

	// recursive solution
	// setOfCities here is state - stateNo
	int tsp_helper(int setOfCities, int city, vector<vector<int>> &dp) {

		// base case
		if (setOfCities == ((1 << V) - 1)) {
			// returning distance from last remaining node (i.e current) to source
			return graph[city][0];
		}

		// if cached, then fetch
		if (dp[setOfCities][city] != -1) {
			return dp[setOfCities][city];
		}

		// otherwise try all possible options(cities connectd to "city")
		int ans = INF;

		for (int choice = 0; choice < V; choice++) {
			// need to check whether city is visited or not
			if ((setOfCities & (1 << choice)) == 0) {
				int subProblem = graph[city][choice] + tsp_helper(setOfCities | (1 << choice), choice, dp);
				ans = min(ans, subProblem);
			}
		}
		dp[setOfCities][city] = ans;
		return ans;
	}

	int tsp_bruteforce() {
		vector<vector<int>> dp(1 << V, vector<int>(V, -1));
		return tsp_helper(1, 0, dp); // setOfCities(each bit of this(binary) represents whether city is visited or not), current_city_number
	}

}; // end-Graph

int main(){
	int V;
	cout << "\nEnter number of Vertices (V): ";
	cin >> V;

	Graph g(V);

	// set parameter for unDirected, Directed!
	g.addEdge();

	cout << "\nDistance (TSP [Brute Force]): " << g.tsp_bruteforce();

	return 0;
} // end-main

/*
test case - 1 (as per leetcode playground)
4
0
1
20
1
0
2
42
1
0
3
25
1
1
2
30
1
1
3
34
1
2
3
10
0
*/