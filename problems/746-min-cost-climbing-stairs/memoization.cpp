// Memoization - O(n) time, O(n) space
class Solution {
public:
    int memo(int i, vector<int>& cost, vector<int>& dp) {
        if (i == 0) return cost[0];
        if (i == 1) return cost[1];
        if (dp[i] != -1) return dp[i];
        dp[i] = cost[i] + min(memo(i - 1, cost, dp), memo(i - 2, cost, dp));
        return dp[i];
    }

    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int> dp(n, -1);
        return min(memo(n - 1, cost, dp), memo(n - 2, cost, dp));
    }
};
