#include<bits/stdc++.h>
using namespace std;

int min_dice_throws(int n,vector<pair<int,int> > snakes, vector<pair<int,int> > ladders){
    
    int throws = 0;
    
    vector<vector<int>> graph (n + 1);
    
    function<int(int)> isLadder = [&](int from_) {
        int ans = -1;
        
        for (auto &x : ladders) {
            if (x.first == from_) {
                ans = x.second;
                break;
            }
        }
        return ans;
    };
    
    function<int(int)> isSnake = [&](int from_) {
        int ans = -1;
        
        for (auto &x : snakes) {
            if (x.first == from_) {
                ans = x.second;
                break;
            }
        }
        return ans;
    };   
    
    // directed graph
    for (int i = 1; i <= n; i++) {
        int from = i;
        
        for (int j = 1; j <= 6 && (from + j <= n); j++) {
            int to = from + j;
            
            int toL_ = isLadder(to);
            int toS_ = isSnake(to);
            
            if ((toL_ == -1) && (toS_ == -1)) {
                graph[from].push_back(to);
            } else if (toL_ != -1) {
                graph[from].push_back(toL_);
            } else {
                graph[from].push_back(toS_);
            }
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