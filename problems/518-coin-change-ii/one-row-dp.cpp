// Count combinations: coins in the outer loop so each mix is counted once - O(coins * amount) time, O(amount) space
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        vector<unsigned int> dp(amount + 1, 0);   // unsigned: middle values may pass INT_MAX, the final one fits
        dp[0] = 1;                                // one way to make 0: no coins
        for (int coin : coins) {
            for (int a = coin; a <= amount; a++) {
                dp[a] += dp[a - coin];            // ways that use this coin at least once more
            }
        }
        return dp[amount];
    }
};
