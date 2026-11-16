// Tabulation with two rows - O(n*m) time, O(m) space
class Solution {
public:
    int solveTabSO(string& text1, string& text2, int i, int j) {
        // vector<vector<int>> dp(text1.length() + 1, vector<int>(text2.length() + 1, 0));
        vector<int> curr(text2.length() + 1, 0);
        vector<int> next(text2.length() + 1, 0);
        for (int i_index = text1.length() - 1; i_index >= 0; i_index--) {
            for (int j_index = text2.length() - 1; j_index >= 0; j_index--) {
                int ans = 0;
                if (text1[i_index] == text2[j_index]) {
                    ans += 1 + next[j_index + 1];
                } else {
                    ans = 0 + max(curr[j_index + 1], next[j_index]);
                }
                curr[j_index] = ans;
            }
            next = curr;
        }
        return next[0];
    }
    int longestCommonSubsequence(string text1, string text2) {
        int i = 0;
        int j = 0;
        // vector<vector<int>> dp(text1.length() + 1, vector<int>(text2.length()
        // + 1, -1));
        int ans = solveTabSO(text1, text2, i, j);
        return ans;
    }
};
