// Tabulation - O(n*m) time, O(n*m) space
class Solution {
public:
    int solveTab(string& text1, string& text2, int i, int j) {
        vector<vector<int>> dp(text1.length() + 1, vector<int>(text2.length() + 1, 0));

        for (int i_index = text1.length() - 1; i_index >= 0; i_index--) {
            for (int j_index = text2.length() - 1; j_index >= 0; j_index--) {
                int ans = 0;
                if (text1[i_index] == text2[j_index]) {
                    ans += 1 + dp[i_index + 1][j_index + 1];
                } else {
                    ans = 0 + max(dp[i_index + 1][j_index], dp[i_index][j_index + 1]);
                }
                dp[i_index][j_index] = ans;
            }
        }
        return dp[0][0];
    }
    int longestCommonSubsequence(string text1, string text2) {
        int i = 0;
        int j = 0;
        int ans = solveTab(text1, text2, i, j);
        return ans;
    }
};
