class Solution {
public:
    int m, n;
    vector<vector<bool>> pacific, atlantic;
    vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    void dfs(int r, int c, vector<vector<bool>>& visited, vector<vector<int>>& heights) {
        visited[r][c] = true;
        for (auto& dir : directions) {
            int nr = r + dir[0];
            int nc = c + dir[1];
            if (nr < 0 || nc < 0 || nr >= m || nc >= n) continue;
            if (visited[nr][nc]) continue;
            if (heights[nr][nc] < heights[r][c]) continue;
            dfs(nr, nc, visited, heights);
        }
    }

    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        m = heights.size();
        n = heights[0].size();
        pacific.assign(m, vector<bool>(n, false));
        atlantic.assign(m, vector<bool>(n, false));
        // Pacific: top and left boundaries
        for (int c = 0; c < n; c++) dfs(0, c, pacific, heights);
        for (int r = 0; r < m; r++) dfs(r, 0, pacific, heights);
        // Atlantic: bottom and right boundaries
        for (int c = 0; c < n; c++) dfs(m - 1, c, atlantic, heights);
        for (int r = 0; r < m; r++) dfs(r, n - 1, atlantic, heights);

        vector<vector<int>> result;
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                if (pacific[r][c] && atlantic[r][c]) result.push_back({r, c});
            }
        }
        return result;
    }
};
