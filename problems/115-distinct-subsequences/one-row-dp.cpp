// dp[j] = ways t[0..j) appears as a subsequence of s[0..i) - O(m * n) time, O(n) space
class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.size(), n = t.size();
        vector<unsigned int> dp(n + 1, 0);        // unsigned: middle values may pass INT_MAX, the answer fits
        dp[0] = 1;                                // the empty t appears once in anything
        for (int i = 1; i <= m; i++) {
            for (int j = n; j >= 1; j--) {        // backwards so dp[j - 1] is still the previous row
                if (s[i - 1] == t[j - 1]) {
                    dp[j] += dp[j - 1];           // also count matches that use s[i - 1] for t[j - 1]
                }
            }
        }
        return dp[n];
    }
};
