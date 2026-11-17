// Turn it into "count subsets with sum P = (total + target) / 2" - O(n * P) time, O(P) space
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int total = 0;
        for (int x : nums) total += x;
        if (abs(target) > total || (total + target) % 2 != 0) return 0;
        int P = (total + target) / 2;             // the numbers that get a '+'
        vector<int> dp(P + 1, 0);
        dp[0] = 1;
        for (int x : nums) {
            for (int s = P; s >= x; s--) {        // backwards: each number used at most once
                dp[s] += dp[s - x];
            }
        }
        return dp[P];
    }
};
