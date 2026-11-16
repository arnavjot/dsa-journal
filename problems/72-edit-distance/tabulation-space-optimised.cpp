// Tabulation with two columns - O(n*m) time, O(n) space (n = word1 length)
class Solution {
public:
    int solveUsingTabulationSO(string a, string b) {
        // vector<vector<int>> dp(a.length() + 1, vector<int>(b.length() + 1,
        // -1));
        vector<int> curr(a.length() + 1, 0);
        vector<int> next(a.length() + 1, 0);

        // base case analysis
        //   for(int col=0; col <= b.length(); col++) {
        //      dp[a.length()][col] = b.length() - col;
        //  }
        for (int row = 0; row <= a.length(); row++) {
            next[row] = a.length() - row;
        }

        for (int j_index = b.length() - 1; j_index >= 0; j_index--) {
            curr[a.length()] = b.length() - j_index;
            for (int i_index = a.length() - 1; i_index >= 0; i_index--) {
                int ans = 0;
                if (a[i_index] == b[j_index]) {
                    // match
                    ans = 0 + next[i_index + 1];
                } else {
                    // insert
                    int insert = 1 + next[i_index];
                    // delete
                    int remove = 1 + curr[i_index + 1];
                    // replace
                    int replace = 1 + next[i_index + 1];
                    ans = min(insert, min(remove, replace));
                }
                curr[i_index] = ans;
            }
            next = curr;
        }
        return next[0];
    }
    int minDistance(string word1, string word2) {
        int i = 0;
        int j = 0;
        // vector<vector<int>>
        // dp(word1.length()+1,vector<int>(word2.length()+1,-1));
        int ans = solveUsingTabulationSO(word1, word2);
        return ans;
    }
};
