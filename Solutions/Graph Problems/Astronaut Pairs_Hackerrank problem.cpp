#include<bits/stdc++.h>
using namespace std;

// problem statement: https://www.hackerrank.com/contests/alcoding-summer-challenge/challenges/astronaut-pairs/problem

int main() {
    
    int n, p;
    cin >> n >> p;
    
    vector<vector<int>> graph(n);
    
    for (int i = 0; i < p; i++) {
        int from, to;
        cin >> from >> to;
        
        graph[from].push_back(to);
        graph[to].push_back(from);        
    }
    
    vector<bool> visited(n, false);
    int count = 0;
    
    function<void(int)> Dfs = [&](int node) {
        count += 1;
        visited[node] = true;
        for (auto &ngbr : graph[node]) {
            if (!visited[ngbr]) {
                Dfs(ngbr);
            }
        }
        return;
    };
        
    int ans = (n * (n - 1)) / 2;
    for(int i = 0; i < n; i++) { 
        if (!visited[i]) {
            Dfs(i);        
            ans -= ((count * (count - 1)) / 2);
            count = 0;
        }        
    }
    
    cout << ans << "\n";
    
    return 0;
}
