// Memoization from the end cell (base: row 1 or column 1) - O(m*n) time, O(m*n) space
class Solution {
public:
    int count(int r, int c, vector<vector<int>>& dp) {
        if (dp[r][c] != -1) {
            return dp[r][c];
        }
        if (r == 1 || c == 1) {
            return 1;
        }
        int left = count(r - 1, c, dp);
        int right = count(r, c - 1, dp);
        dp[r][c] = left + right;
        return dp[r][c];
    }

    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, -1));
        return count(m, n, dp);
    }
};
