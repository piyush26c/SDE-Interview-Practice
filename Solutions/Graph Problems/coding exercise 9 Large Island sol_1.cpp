#include<bits/stdc++.h>
using namespace std;

// recursive solution

int maxAreaOfIsland(vector<vector<int>> grid) {
    int ans = 0;
    int row = (int) grid.size();
    int col = (int) grid[0].size();
    
    int count = 0;
    
    vector<vector<int>> points = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    
    function<void(int, int)> Dfs = [&](int i, int j) {
        grid[i][j] = 0;
        
        for (auto &point : points) {
            if (((i + point[1] >= 0) && (i + point[1] < row)) && ((j + point[0] >= 0) && (j + point[0] < col)) && (grid[i + point[1]][j + point[0]] == 1)) {
                ++count;
                Dfs(i + point[1], j + point[0]);
            }            
        }        
        return;
    };    
    
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            if (grid[r][c] == 1) {
                Dfs(r, c);
                count += 1;
                if (count > ans) {
                    ans = count;
                }
                count = 0;
            }
        }
    }
    
    return ans;    
}

int main() {
    vector<vector<int>> grid = 
    {
        {1, 0, 0, 1, 0},
        {1, 0, 1, 0, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 1, 1, 1},
        {1, 0, 1, 1, 0}
    };
	
	// Ans. 8 
        
    cout << "Ans: " << maxAreaOfIsland(grid) << "\n";
    
    return 0;
}