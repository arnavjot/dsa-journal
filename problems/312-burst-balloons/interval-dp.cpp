// Interval DP: choose the LAST balloon to burst in each open interval - O(n^3) time, O(n^2) space
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        vector<int> v(n + 2, 1);                  // pad with a 1 on each side
        for (int i = 0; i < n; i++) v[i + 1] = nums[i];
        // dp[l][r] = best coins from bursting everything strictly between l and r
        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
        for (int len = 2; len <= n + 1; len++) {
            for (int l = 0; l + len <= n + 1; l++) {
                int r = l + len;
                for (int k = l + 1; k < r; k++) { // k bursts last, next to l and r
                    dp[l][r] = max(dp[l][r], dp[l][k] + dp[k][r] + v[l] * v[k] * v[r]);
                }
            }
        }
        return dp[0][n + 1];
    }
};
