// Memoization with the last house as the base case - O(n) time, O(n) space
class Solution {
public:
    int solveUsingMem(vector<int>& nums, int index, vector<int>& dp) {
        // if (index >= nums.size()) {
        //     return 0;
        // }
        if (index >= nums.size() - 1) {
            return nums[index];
        }
        if (dp[index] != -1) {
            return dp[index];
        }

        int tempAns = 0;
        if (index + 2 < nums.size()) { // index < nums.size() - 2
            tempAns = solveUsingMem(nums, index + 2, dp);
        }
        int include = nums[index] + tempAns;
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
