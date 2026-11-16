// Memoization - O(n*m) time, O(n*m) space
class Solution {
public:
    int solveMem(string& text1, string& text2, int i, int j,
                 vector<vector<int>>& dp) {
        if (i >= text1.length()) {
            return 0;
        }
        if (j >= text2.length()) {
            return 0;
        }
        if (dp[i][j] != -1) {
            return dp[i][j];
        }
        int ans = 0;
        if (text1[i] == text2[j]) {
            ans += 1 + solveMem(text1, text2, i + 1, j + 1, dp);
        } else {
            ans = 0 + max(solveMem(text1, text2, i, j + 1, dp),
                          solveMem(text1, text2, i + 1, j, dp));
        }
        dp[i][j] = ans;
        return dp[i][j];
    }
    int longestCommonSubsequence(string text1, string text2) {
        int i = 0;
        int j = 0;
        vector<vector<int>> dp(text1.length() + 1, vector<int>(text2.length() + 1, -1));
        int ans = solveMem(text1, text2, i, j, dp);
        return ans;
    }
};
