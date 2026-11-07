class Solution {
public:
    // Same recurrence as the tabulation, keeping only the last two values - O(n) time, O(1) space
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        int prev2 = cost[0], prev1 = cost[1];      // dp[i - 2], dp[i - 1]
        for (int i = 2; i < n; i++) {
            int curr = cost[i] + min(prev1, prev2);
            prev2 = prev1;
            prev1 = curr;
        }
        return min(prev1, prev2);
    }
};
