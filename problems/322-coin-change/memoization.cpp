// Memoization - O(amount * k) time, O(amount) space (k = number of coins)
class Solution {
public:
    int solve(vector<int>& coins, int amount, vector<int>& dp) {
        if (amount == 0)
            return 0;
        // if (amount < 0)
        //     return INT_MAX;
        if (dp[amount] != -1)
            return dp[amount];

        int mini = INT_MAX;
        for (int coin : coins) {
            if (coin <= amount) {
                int temp = solve(coins, amount - coin, dp);
                if (temp != INT_MAX) {
                    int ans = 1 + temp;
                    mini = min(mini, ans);
                }
            }
        }

        return dp[amount] = mini;
    }
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, -1);
        int ans = solve(coins, amount, dp);
        if (ans == INT_MAX) {
            return -1;
        } else
            return ans;
    }
};
