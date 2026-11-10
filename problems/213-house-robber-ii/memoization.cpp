// Memoization on two ranges - O(n) time, O(n) space
class Solution {
public:
    int solveUsingMem(vector<int>& nums, int start, int end, vector<int>& dp) {
        if (start > end) {
            return 0;
        }

        if (dp[start] != -1) {
            return dp[start];
        }
        // Robbing the current house
        int include = nums[start] + solveUsingMem(nums, start + 2, end, dp);
        // Skipping the current house
        int exclude = solveUsingMem(nums, start + 1, end, dp);

        dp[start] = max(include, exclude);
        return dp[start];
    }

    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];
        vector<int> dp1(n, -1);
        vector<int> dp2(n, -1);

        // Case 1: Exclude last house (rob from 0 to n-2)
        int case1 = solveUsingMem(nums, 0, n - 2, dp1);
        // Case 2: Exclude first house (rob from 1 to n-1)
        int case2 = solveUsingMem(nums, 1, n - 1, dp2);
        return max(case1, case2);
    }
};
