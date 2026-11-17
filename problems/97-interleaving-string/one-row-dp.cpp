// dp[j] = can s1[0..i) and s2[0..j) form s3[0..i+j) - O(m * n) time, O(n) space
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int m = s1.size(), n = s2.size();
        if (m + n != s3.size()) return false;
        vector<bool> dp(n + 1, false);
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                if (i == 0 && j == 0) {
                    dp[j] = true;                 // empty + empty = empty
                } else {
                    bool fromS1 = i > 0 && dp[j] && s1[i - 1] == s3[i + j - 1];          // last letter came from s1
                    bool fromS2 = j > 0 && dp[j - 1] && s2[j - 1] == s3[i + j - 1];      // last letter came from s2
                    dp[j] = fromS1 || fromS2;
                }
            }
        }
        return dp[n];
    }
};
