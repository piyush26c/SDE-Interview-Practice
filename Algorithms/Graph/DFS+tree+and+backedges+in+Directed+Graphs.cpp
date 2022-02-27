#include<bits/stdc++.h>

using namespace std;

/*
	Topic: DFS Tree and Backedges in Directed and Undirected grahps
									| _  below code can be used for directed and undirected graphs.
	
	Time Complexity = O(N), N = number of nodes

*/
const int N = 1e5 + 1;

vector<int> gr[N];
int vis[N];
bool cycle = false;

void dfs(int cur, int par) {
	// visited and in call stack
	vis[cur] = 1;
	for (auto x : gr[cur]) {
		// here x is neighbour
		// vsited = 0 means not visited yet.
		if (vis[x] == 0) {
			dfs(x, cur);
		}
		else if (x != par && vis[x] == 1) {
			// backedge
			cycle = true;
		}
	}
	// visited and not in call stack
	vis[cur] = 2;
	return;
}

int main()
{
	int n, m;
	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		gr[x].push_back(y);
		// comment below code if graph is directed
		gr[y].push_back(x);
	}

	for (int i = 1; i <= n; i++) {
		if (vis[i] == 0) {
			dfs(i, 0);
		}
	}

	if (cycle) {
		cout << "Yes cycle found";
	}
	else {
		cout << "Not found";
	}
	return 0;
}