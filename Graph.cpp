#######################################################################################################
--------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------

1]
Kosaraju's Strongly Connected Component Algorithm
References for Algorithm: https://www.hackerearth.com/practice/algorithms/graphs/strongly-connected-components/tutorial/








int main() {
	int nov, noe; //number of vertices, number of edges
	cin >> nov;
	unordered_map<int, vector<int>> graph;
	vector<bool> visited(nov, false);
	//input edges from -> to
	for (int i = 0; i < noe; i++) {
		int from, to;
		cin >> from >> to;
		graph[from].push_back(to);		
	}
	
	
	return 0;	
}