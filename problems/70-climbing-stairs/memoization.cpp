class Solution {
public:
    int memo(int n, vector<int>& dp) {
        if (n == 0 || n == 1) return n;
        if(n == 2) return 2;
        if (dp[n] != -1) return dp[n]; 
        dp[n] = memo(n - 1, dp) + memo(n - 2, dp);
        return dp[n];
    }

    int climbStairs(int n) {
        vector<int> dp(n + 1, -1);
        return memo(n, dp);
    }
};
