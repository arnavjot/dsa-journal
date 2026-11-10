// Tabulation - O(amount * k) time, O(amount) space (k = number of coins)
class Solution {
public:
    int solveTab(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1);
        dp[0] = 0;


        for (int i = 1; i <= amount; i++) {
            int mini = INT_MAX;
            for (int coin : coins) {
                if (coin <= i) {
                    int temp = dp[i - coin];
                    if (temp != INT_MAX) {
                        int ans = 1 + temp;
                        mini = min(mini, ans);
                    }
                }
            }
            dp[i] = mini;
        }
        return dp[amount];
    }
    int coinChange(vector<int>& coins, int amount) {
        // vector<int> dp(amount + 1, -1);
        int ans = solveTab(coins, amount);
        if (ans == INT_MAX) {
            return -1;
        } else
            return ans;
    }
};
