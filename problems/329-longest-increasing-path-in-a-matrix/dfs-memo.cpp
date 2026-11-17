// DFS from every cell with memo: memo[r][c] = longest increasing path starting at (r, c) - O(m * n) time and space
class Solution {
public:
    int m, n;
    vector<vector<int>> memo;
    int dr[4] = {1, -1, 0, 0}, dc[4] = {0, 0, 1, -1};

    int dfs(vector<vector<int>>& matrix, int r, int c) {
        if (memo[r][c] != 0) return memo[r][c];   // already solved
        int best = 1;                             // the cell on its own
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k], nc = c + dc[k];
            if (nr >= 0 && nc >= 0 && nr < m && nc < n && matrix[nr][nc] > matrix[r][c]) {
                best = max(best, 1 + dfs(matrix, nr, nc));
            }
        }
        return memo[r][c] = best;
    }

    int longestIncreasingPath(vector<vector<int>>& matrix) {
        m = matrix.size(); n = matrix[0].size();
        memo.assign(m, vector<int>(n, 0));
        int ans = 0;
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                ans = max(ans, dfs(matrix, r, c));
            }
        }
        return ans;
    }
};
