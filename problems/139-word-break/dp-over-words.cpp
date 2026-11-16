// dp[i] = can the first i letters be split into words - O(n * W * L) time, O(n) space
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        vector<bool> dp(n + 1, false);
        dp[0] = true;                                   // the empty prefix
        for (int i = 1; i <= n; i++) {
            for (string& w : wordDict) {
                int len = w.size();
                if (len <= i && dp[i - len] && s.compare(i - len, len, w) == 0) {
                    dp[i] = true;                       // a good prefix + this word
                    break;
                }
            }
        }
        return dp[n];
    }
};
