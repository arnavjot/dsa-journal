// Memoization from the start cell (base: last row or last column) - O(m*n) time, O(m*n) space
class Solution {
public:
    int count(int r, int c, vector<vector<int>>& dp) {
        if (r == dp.size() - 1 || c == dp[0].size() - 1) {
            return 1;
        }

        if (dp[r][c] != -1) {
            return dp[r][c];
        }

        int down = count(r + 1, c, dp);
        int right = count(r, c + 1, dp);
        return dp[r][c] = down + right;
    }

    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, -1));
        return count(0, 0, dp);
    }
};
