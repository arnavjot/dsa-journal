// Memoization - O(n^2) time, O(n^2) space
class Solution {
public:
    int solveUsingMem(vector<int>& num, int curr, int prev,
                      vector<vector<int>>& dp) {
        // base case
        if (curr >= num.size()) {
            return 0;
        }

        if (dp[curr][prev + 1] != -1) {
            return dp[curr][prev + 1];
        }
        int include = 0;
        if (prev == -1 || num[curr] > num[prev]) {
            include = 1 + solveUsingMem(num, curr + 1, curr, dp);
        }
        int exclude = 0 + solveUsingMem(num, curr + 1, prev, dp);
        dp[curr][prev + 1] = max(include, exclude);
        return dp[curr][prev + 1];
    }

    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int> > dp(n+1, vector<int>(n+1,-1));
        return solveUsingMem(nums, 0, -1, dp);
    }
};
