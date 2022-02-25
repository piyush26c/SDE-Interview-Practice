#include<bits/stdc++.h>

using namespace std;

// this is one of the best problem on Multisource BFS
/*
	Problem Statement:
	Your are given a binary grid of size n * m. Cells contain either 1s or 0s. You can only traverse on cell with
	only 1s. You can move in any directions (left, right, up, down). You have to start from any cell in the first row and
	finish on any cell on the last row. Find the shortest path.

*/

/*
	Time complexity:
		| _ O(n * m)
*/

// Note: In BFS, wherever we reach at node first, that is the "SHORTEST" distance!!!

/*
	Problems on Multisource BFS
	| _ https://leetcode.com/problems/rotting-oranges/
	| _ https://leetcode.com/problems/shortest-bridge/
	| _ https://leetcode.com/problems/map-of-highest-peak/

*/


int main()
{

	int n, m;
	cin >> n >> m;

	int a[n][m], dist[n][m];
	queue<pair<int, int>> Q;

	int dx[4] = {1, -1, 0, 0};
	int dy[4] = {0, 0, 1, -1};

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
			dist[i][j] = INT_MAX;
			if (i == 0 && a[i][j]) {
				Q.push({i, j});
				dist[i][j] = 0;
			}
		}
	}

	while (!Q.empty()) {
		int x = Q.front().first;
		int y = Q.front().second;
		Q.pop();

		if (x == n - 1) {
			break;
		}

		for (int i = 0; i < 4; i++) {
			int xx = x + dx[i];
			int yy = y + dy[i];

			if (xx >= 0 && xx < n && yy >= 0 && yy < m && dist[xx][yy] == INT_MAX && a[xx][yy] == 1) {
				Q.push({xx, yy});
				dist[xx][yy] = dist[x][y] + 1;
			}

		}

		// for (int i = 0; i < n; i++) {
		//	for (int j = 0; j < m; j++) {
		//		if (dist[i][j] == INT_MAX) cout << "#" << " ";
		//		else cout << dist[i][j] << " ";
		//	} cout << '\n';
		// } cout << '\n';


	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << dist[i][j] << " ";
		} cout << '\n';
	}

	int minimum_distance = INT_MAX;

	for (int j = 0; j < m; j++) {
		minimum_distance = min(minimum_distance, dist[n - 1][j]);
	}


	return 0;
}