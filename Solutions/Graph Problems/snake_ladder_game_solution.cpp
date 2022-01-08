#include<bits/stdc++.h>
using namespace std;

/*
	optimized version
	| _ In previous version, we were checking whehter a block has a start to ladder | snake
	| _ Instead we can mark those block who has start and while adding the edge we will keep eye on it ...
*/

int min_dice_throws(int n, vector<pair<int, int>> snakes, vector<pair<int, int>> ladders){
    
    int throws = 0;
    
    vector<vector<int>> graph(n + 1);
	
	vector<int> board(n + 1, 0);
    
	// optimization ... 
	for (auto &x : snakes) {
		int from = x.first;
		int to = x.second;
		
		board[x.first] = x.second - x.first;
	}
	
	for (auto &x : ladders) {
		int from = x.first;
		int to = x.second;
		
		board[x.first] = x.second - x.first;
	}
	// ...
	    
    // directed graph
    for (int i = 1; i <= n; i++) {
        int from = i;
        
        for (int j = 1; j <= 6 && (from + j <= n); j++) {
            int to = from + j;
            
			to += board[to];
			graph[from].push_back(to);
        }
    }
      
    // print graph
    /*
    for (int i = 1; i <= n; i++) {
        cout << "from: " << i << "  to: ";
        for (auto &x : graph[i]) {
            cout << x << ", ";
        }
        cout << "\n";
    }
    */
    
    // BFS shortest path algorithm
    function<int(int)> BFS_ShortestPath = [&](int source) {
        vector<bool> visited(n + 1, false);
        vector<int> dist(n + 1, 0);
        vector<int> parent(n + 1, 0);
        
        queue<int> q;
        
        q.push(source);
        visited[source] = true;
        parent[source] = source;
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            
            for (auto &ngbr : graph[node]) {
                if (!visited[ngbr]) {
                    q.push(ngbr);
                    visited[ngbr] = true;
                    parent[ngbr] = node;
                    dist[ngbr] = dist[parent[ngbr]] + 1;
                }
            }
        }
        return dist[n];
    };    
    
    throws = BFS_ShortestPath(1);
    
    return throws;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    vector<pair<int, int>> snakes = {{2, 15}, {5, 7}, {9, 27}, {18, 29}, {25, 35}};
    vector<pair<int, int>> ladders = {{17, 4}, {20, 6}, {34, 12}, {24, 16}, {32, 30}};
    int n = 36;
    
    cout << "\nAns: \n" << min_dice_throws(n, snakes, ladders) << "\n";    
    
    return 0;
}