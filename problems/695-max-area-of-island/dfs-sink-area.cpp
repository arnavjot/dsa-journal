class Solution {
public:
    int m, n;
    vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    int dfs(int r, int c, vector<vector<int>>& grid) {
        if (r < 0 || c < 0 || r >= m || c >= n) return 0;
        if (grid[r][c] == 0) return 0;

        grid[r][c] = 0;
        int area = 1;
        for (auto& dir : directions) {
            int nr = r + dir[0];
            int nc = c + dir[1];
            area += dfs(nr, nc, grid);
        }
        return area;
    }

    int maxAreaOfIsland(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();

        int maxArea = 0;
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if (grid[r][c] == 1) {
                    int area = dfs(r, c, grid);
                    maxArea = max(maxArea, area);
                }
            }
        }
        return maxArea;
    }
};
