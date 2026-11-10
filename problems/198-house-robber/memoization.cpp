// Memoization - O(n) time, O(n) space
class Solution {
public:
    int solveUsingMem(vector<int>& nums, int index, vector<int>& dp) {
        if (index >= nums.size()) {
            return 0;
        }
        if (dp[index] != -1) {
            return dp[index];
        }
        int include = nums[index] + solveUsingMem(nums, index + 2, dp);
        // not robbing that house
        int exclude = 0 + solveUsingMem(nums, index + 1, dp);
        dp[index] = max(include, exclude);
        return dp[index];
    }
    int rob(vector<int>& nums) {
        vector<int> dp(nums.size(), -1);
        return solveUsingMem(nums, 0, dp);
    }
};
