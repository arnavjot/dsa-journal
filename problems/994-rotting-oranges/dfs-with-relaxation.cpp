class Solution {
public:
    // DFS CAN work, but only if a cell is revisited whenever a SHORTER time reaches it.
    void dfs(vector<vector<int>>& grid, vector<vector<int>>& t, int i, int j, int time) {
        if (i < 0 || j < 0 || i >= grid.size() || j >= grid[0].size()) return;
        if (grid[i][j] == 0 || t[i][j] <= time) return;   // empty cell, or already reached at least as fast
        t[i][j] = time;
        dfs(grid, t, i - 1, j, time + 1);
        dfs(grid, t, i + 1, j, time + 1);
        dfs(grid, t, i, j - 1, time + 1);
        dfs(grid, t, i, j + 1, time + 1);
    }

    int orangesRotting(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> t(n, vector<int>(m, INT_MAX));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (grid[i][j] == 2) dfs(grid, t, i, j, 0);   // one DFS per rotten orange
        int ans = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (grid[i][j] == 1) {
                    if (t[i][j] == INT_MAX) return -1;     // never reached
                    ans = max(ans, t[i][j]);
                }
        return ans;
    }
};
