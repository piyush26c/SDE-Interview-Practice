#include<bits/stdc++.h>
using namespace std;

// Algorithm to Find Articulation Point and Bridges
/*
	Time complexity:
		| _ O(V) ~ (Time complexity of DFS)

	Space complexity:
		| _ O(V + E)

*/

class Graph {
	private:
	vector<vector<int>> graph; // [[node] ... ]
	vector<bool> visited;
	vector<int> discover;
	vector<int> lowest;
	int time;
	vector<pair<int, int>> bridges;
	set<int> articulationPoints;
	/*
		set stl used because ...
		current_node can have multiple childs and when we visit this childrens, every time we will get
		"current_node" as <articulation point> thus there will be multiple entries in articulationPoints container,
		thus set stl is appropriate container to be used here.
	*/
	int V;

	public:
	Graph(int V) {
		this->V = V;
        graph.resize(V + 1);
		visited.resize(V + 1, false);
		discover.resize(V + 1);
		lowest.resize(V + 1);
		time = 1;
	}

	void add_edge(int node1, int node2) {
		graph[node1].push_back(node2);
		graph[node2].push_back(node1);
	}

	void dfs(int current_node, int parent_node) {
		visited[current_node] = true;
		discover[current_node] = lowest[current_node] = time++;
		int childNodes = 0;

		for (auto child : graph[current_node]) {
			if (!visited[child]) {
				dfs(child, current_node);
				childNodes++;

				lowest[current_node] = min(lowest[current_node], lowest[child]);

				// condition for bridge
				if (lowest[child] > discover[current_node]) {
					// bridge edge found!
					bridges.push_back(make_pair(current_node, child));
				}

				// condition for articulation point
				if (parent_node != 0 && lowest[child] >= discover[current_node]) {
					articulationPoints.insert(current_node);
				}

			} else if (child != parent_node) {
				// backedge found!
				lowest[current_node] = min(lowest[current_node], discover[child]);
			}
		}

		// special condition for root to check whether it is an <articulation point> or not;
		if (parent_node == 0 && childNodes > 1) {	// childNodes = number of childrens to root!
			articulationPoints.insert(current_node);
		}
		return;
	}

	void printBridges() {
		cout << "\nFollowing are the bridges in given graph: ";

		for (auto bridge : bridges) {
			cout << "\n" << bridge.first << " " << bridge.second;
		}
		return;
	}

	void printAritculationPoints() {
		cout << "\nFollowing are the Aritculation Points(Nodes): ";

		for (auto node : articulationPoints) {
			cout << "\n" << node;
		}
	}
};

int main() {

	Graph g(7);
	g.add_edge(1, 2);
	g.add_edge(2, 3);
	g.add_edge(2, 4);
	g.add_edge(2, 5);
	g.add_edge(1, 7);
	g.add_edge(4, 6);

	g.dfs(1, 0);

	g.printBridges();

	g.printAritculationPoints();

	return 0;
}

/*
	Test case - 1:

	Graph g(7);
	g.add_edge(1, 2);
	g.add_edge(1, 3);
	g.add_edge(2, 3);
	g.add_edge(2, 4);
	g.add_edge(4, 5);
	g.add_edge(5, 7);
	g.add_edge(7, 6);
	g.add_edge(4, 6);
*/

/*
	Test Case - 2:

	Graph g(5);
	g.add_edge(1, 2);
	g.add_edge(2, 3);
	g.add_edge(2, 4);
	g.add_edge(4, 3);
	g.add_edge(4, 5);
*/