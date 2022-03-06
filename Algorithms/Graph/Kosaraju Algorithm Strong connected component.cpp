#include<bits/stdc++.h>
using namespace std;

// Algorithm to Find Strongly Connnected Components & draw condensed graph
// This algorithm is also called as """ KOSARAJU ALGORITHM """
// https://cp-algorithms.com/graph/strongly-connected-components.html

/*
	Time complexity:
		| _ O(V + E)

	Space complexity:
		| _ O(V)
*/

class Graph {
	private:
	vector<vector<int>> graph; // [[node] ... ]
	vector<vector<int>> rgraph; // reverse graph
	vector<bool> visited;
	vector<int> order; // to store topological order
	int noOfComponents;
	vector<int> nodeToComponent;	// to store component number of each node(number) either way we can store in a way of adjacency list!
	vector<vector<int>> condensedGraph;
	vector<int> rootNodes; // the list of all root nodes (one per component) in the condensation graph.
	vector<int> components;
	vector<int> rootOfNode;
	int V;

	public:
	Graph(int V) {
		this->V = V;
		graph.resize(V + 1);
		rgraph.resize(V + 1);
		visited.resize(V + 1, false);
		noOfComponents = 0;
		nodeToComponent.resize(V + 1);
		condensedGraph.resize(V + 1);
		rootOfNode.resize(V + 1, 0);
	}

	void add_edge(int node1, int node2) {
		graph[node1].push_back(node2);
		rgraph[node2].push_back(node1);
	}

	// to get the topological order
	void dfs1(int current_node) {
		visited[current_node] = true;

		for (auto child : graph[current_node]) {
			if (!visited[child]) {
				dfs1(child);
			}
		}

		order.push_back(current_node);
		return;
	}

	void getTopologicalOrder() {
		for (int i = 1; i <= V; i++) {
			if (!visited[i]) {
				dfs1(i);
			}
		}

		reverse(order.begin(), order.end());
		return;
	}

	// traversing(DFS) on reverse graph, particularly on first sink(SCC) in topological order
	void dfs2(int current_node, int noOfComponents) {
		visited[current_node] = true;
		nodeToComponent[current_node] = noOfComponents;
		components.push_back(current_node);

		for (auto child : rgraph[current_node]) {
			if (!visited[child]) {
				dfs2(child, noOfComponents);
			}
		}
		return;
	}

	void kosarajuAlgo() {
		fill(visited.begin(), visited.end(), false);

		for (auto node : order) {
			if (!visited[node]) {
				dfs2(node, ++noOfComponents);

				// below provision is to keep track of nodes that will be there in condensedGraph
				int root = components.front();
				for (auto nd : components) {
					rootOfNode[nd] = root;
				}
				rootNodes.push_back(root);
				components.clear();
			}
		}

		return;
	}

	void printNodeToComponent() {
		cout << "\nNode	 ->	 Component(Number): \n";
		for (int i = 1; i <= V; i++) {
			cout << i << "	->	" << nodeToComponent[i] << "\n";
		}
		return;
	}

	void createCondensedGraph() {
		for (int from = 1; from <= V; from++) {
			for (auto to : graph[from]) {
				int root_from = rootOfNode[from];
				int root_to = rootOfNode[to];

				if (root_from != root_to) {
					condensedGraph[root_from].push_back(root_to);
				}
			}
		}
		return;
	}

	void printCondensedGraph() {
		cout << "\nCondensed Graph: \n";

		for (int from = 1; from <= V; from++) {
			if (condensedGraph[from].size() == 0) continue;

			cout << from << "  ->  ";
			for (auto to : condensedGraph[from]) {
				cout << to << " ";
			}
			cout << "\n";
		}
		return;
	}

};

int main() {

	Graph g(9);
	g.add_edge(1, 2);
	g.add_edge(2, 3);
	g.add_edge(3, 1);
	g.add_edge(3, 4);
	g.add_edge(4, 5);
	g.add_edge(5, 6);
	g.add_edge(6, 4);
	g.add_edge(7, 2);
	g.add_edge(7, 8);
	g.add_edge(8, 9);
	g.add_edge(9, 7);

	g.getTopologicalOrder();
	g.kosarajuAlgo();
	g.printNodeToComponent();
	g.createCondensedGraph();
	g.printCondensedGraph();

	return 0;
}

/*
	Test Case - 1

	Graph g(4);
	g.add_edge(1, 2);
	g.add_edge(2, 3);
	g.add_edge(3, 1);
	g.add_edge(3, 4);
	g.add_edge(4, 3);
*/


/*
	Test Case - 2

	Graph g(4);
	g.add_edge(1, 2);
	g.add_edge(2, 3);
	g.add_edge(3, 1);
	g.add_edge(3, 4);
*/

/*
	Test Case - 3

	Graph g(9);
	g.add_edge(1, 2);
	g.add_edge(2, 3);
	g.add_edge(3, 1);
	g.add_edge(3, 4);
	g.add_edge(4, 5);
	g.add_edge(5, 6);
	g.add_edge(6, 4);
	g.add_edge(7, 2);
	g.add_edge(7, 8);
	g.add_edge(8, 9);
	g.add_edge(9, 7);

*/