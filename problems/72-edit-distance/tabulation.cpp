// Tabulation - O(n*m) time, O(n*m) space
class Solution {
public:
    int solveUsingTabulation(string a, string b) {
        vector<vector<int>> dp(a.length() + 1, vector<int>(b.length() + 1, -1));

        // base case analysis
        for (int col = 0; col <= b.length(); col++) {
            dp[a.length()][col] = b.length() - col;
        }
        for (int row = 0; row <= a.length(); row++) {
            dp[row][b.length()] = a.length() - row;
        }

        for (int i_index = a.length() - 1; i_index >= 0; i_index--) {
            for (int j_index = b.length() - 1; j_index >= 0; j_index--) {
                int ans = 0;
                if (a[i_index] == b[j_index]) {
                    // match
                    ans = 0 + dp[i_index + 1][j_index + 1];
                } else {
                    // insert
                    int insert = 1 + dp[i_index][j_index + 1];
                    // delete
                    int remove = 1 + dp[i_index + 1][j_index];
                    // replace
                    int replace = 1 + dp[i_index + 1][j_index + 1];
                    ans = min(insert, min(remove, replace));
                }
                dp[i_index][j_index] = ans;
            }
        }
        return dp[0][0];
    }
    int minDistance(string word1, string word2) {
        int ans = solveUsingTabulation(word1, word2);
        return ans;
    }
};
