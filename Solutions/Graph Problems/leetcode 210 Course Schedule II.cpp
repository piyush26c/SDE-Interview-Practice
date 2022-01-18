#include<bits/stdc++.h>
using namespace std;

// problem link: https://leetcode.com/problems/course-schedule-ii/

class Solution {
public:
	vector<int> findOrder(int numCourses, vector<vector<int>> prerequisites) {
		
		int n = numCourses;
		vector<int> ans;
		
		int start_node = INT_MAX;

		// creating a graph	
		vector<vector<int>> graph(n);

		// populating a graph
		for (auto &edge : prerequisites) {
			int from = edge[0]; 
			int to = edge[1];
			
			graph[to].push_back(from);			
		}

		// applying Dfs
		list<int> ordering;
		vector<int> visited(n, 0);
		bool cycleFound = false;

		function<void(int)> Dfs = [&](int node) {		 
			if (cycleFound) return; 
			visited[node] = 1;
			
			 for (auto ngbr : graph[node]) {
				 if (visited[ngbr] == 0)
					 Dfs(ngbr);		
				 else if (visited[ngbr] == 1)
					 cycleFound = true;
			}
			
			ordering.push_front(node);
			visited[node] = 2;
			return;
		};

		// because of this loop all nodes connected or absolute will be traversed
		for (int i = 0; i < n; i++) {
			if (visited[i] == 0) {
				Dfs(i);
			}
		}	   
		
		if (!cycleFound) {			  
			copy(ordering.begin(),ordering.end(),back_inserter(ans));
		}

		return ans;	
	}
};