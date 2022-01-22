#include<bits/stdc++.h>
using namespace std;

// Link: https://www.udemy.com/course/graph-theory-algorithms-for-competitive-programming/learn/quiz/5266068#announcements
// this code contains logic to fetch edges from a matrix in O(m*n) time complexity, where m and n are number_of_rows && number_of_columns in matrix

int populateMatrix(vector<vector<int>> &matrix) {
	int n = (int) matrix[0].size();
	int m = (int) matrix.size();
	int nodeNo = 0;
	
	for (int r = 0; r < m; r++) {
		for (int c = 0; c < n; c++) {
			if(matrix[r][c] == 1) {
				nodeNo += 1;
				matrix[r][c] = nodeNo;
			}
		}
	}
	return nodeNo;
}

int find_set(int node, vector<int> &parent) {
	if (parent[node] == -1) {
		return node;
	}
	return parent[node] = find_set(parent[node], parent);
}

void union_set(int node1, int node2, vector<int> &rank, vector<int> &parent) {
	int s1 = find_set(node1, parent);
	int s2 = find_set(node2, parent);
	
	if (rank[s1] < rank[s2]) {
		parent[s1] = s2;
		rank[s2] += rank[s1];
	} else {
		parent[s2] = s1;
		rank[s1] += rank[s2];
	}
	
}

void addInDSU(int node1, int node2, vector<int> &rank, vector<int> &parent) {
	int s1 = find_set(node1, parent);
	int s2 = find_set(node2, parent);
	
	if (s1 != s2) {
		union_set(s1, s2, rank, parent);
	}
}


int DSU(vector<vector<int>> &matrix, int V) {
	int op = 0;
	int n = (int) matrix[0].size();
	int m = (int) matrix.size();
	vector<int> rank(V + 1, 1);
	vector<int> parent(V + 1, -1);
	
	// column wise find edges
	int node1 = -1; int node2 = -1;
	for (int r = 0; r < m; r++) {
		for (int c = 0; c < n; c++) {
			
			if (matrix[r][c] > 0 && node1 == -1) {
			if (matrix[r][c] > 0 && node1 == -1) {
			if (matrix[r][c] > 0 && node1 == -1) {
				node1 = matrix[r][c];
				continue;
			}
			
			if (matrix[r][c] > 0 && node1 != -1) {
				node2 = matrix[r][c];
				//dsu_union
				addInDSU(node1, node2, rank, parent);
				node1 = node2;
				node2 = -1;
			}
		}
		node1 = -1; node2 = -1;
	}
	
	
	// row wise find edges
	node1 = -1; node2 = -1;
	for (int c = 0; c < n; c++) {
		for (int r = 0; r < m; r++) {
			
			if (matrix[r][c] > 0 && node1 == -1) {
				node1 = matrix[r][c];
				continue;
			}
			
			if (matrix[r][c] > 0 && node1 != -1) {
				node2 = matrix[r][c];
				//dsu_union
				addInDSU(node1, node2, rank, parent);
				node1 = node2;
				node2 = -1;
			}
		}
		node1 = -1; node2 = -1;
	}
	
	for (auto val : parent) {
		if (val == -1) {
			op += 1;
		}
	}
	
	
	return op - 1;	// -1 for 0th index -1 as we are naming nodes from 1.
}

int solve(vector<vector<int>> matrix) {	 
   
	int n = populateMatrix(matrix);
	
	int ans = DSU(matrix, n);
	
	return ans;
}