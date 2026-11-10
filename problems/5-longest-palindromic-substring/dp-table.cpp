// DP table - O(n^2) time, O(n^2) space
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.length();
        // dp[i][j] = true when s[i..j] is a palindrome
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        int start = 0, best = 1;
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                // ends match, and the inside is a palindrome (or there is no inside)
                if (s[i] == s[j] && (j - i < 2 || dp[i + 1][j - 1])) {
                    dp[i][j] = true;
                    if (j - i + 1 > best) {
                        best = j - i + 1;
                        start = i;
                    }
                }
            }
        }
        return s.substr(start, best);
    }
};
