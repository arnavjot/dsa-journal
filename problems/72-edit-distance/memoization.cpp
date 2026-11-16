// Memoization - O(n*m) time, O(n*m) space
class Solution {
public:
    int solveUsingMem(
        string& a, string& b, int i, int j,
        vector<vector<int>>& dp) { // MEMORY LIMIT EXCEEDED -> pass by ref

        // base case
        if (i == a.length()) {
            return b.length() - j;
        }
        if (j == b.length()) {
            return a.length() - i;
        }
        if (dp[i][j] != -1) {
            return dp[i][j];
        }
        int ans = 0;

        if (a[i] == b[j]) {
            // match
            ans = 0 + solveUsingMem(a, b, i + 1, j + 1, dp);
        } else {
            // insert
            int insert = 1 + solveUsingMem(a, b, i, j + 1, dp);
            // delete
            int remove = 1 + solveUsingMem(a, b, i + 1, j, dp);
            // replace
            int replace = 1 + solveUsingMem(a, b, i + 1, j + 1, dp);
            ans = min(insert, min(remove, replace));
        }
        dp[i][j] = ans;
        return dp[i][j];
    }
    int minDistance(string word1, string word2) {
        int i = 0;
        int j = 0;
        vector<vector<int>>
        dp(word1.length()+1,vector<int>(word2.length()+1,-1));
        int ans = solveUsingMem(word1, word2, i, j, dp);
        return ans;
    }
};
