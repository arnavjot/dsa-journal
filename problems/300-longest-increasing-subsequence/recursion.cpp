// Recursion - O(2^n) time, O(n) stack space
class Solution {
public:
    int solveUsingRecursion(vector<int>& num, int curr, int prev) {
        // base case
        if (curr >= num.size()) {
            return 0;
        }

        int include = 0;
        if (prev == -1 || num[curr] > num[prev]) {
            include = 1 + solveUsingRecursion(num, curr + 1, curr);
        }
        int exclude = 0 + solveUsingRecursion(num, curr + 1, prev);
        int ans = max(include, exclude);
        return ans;
    }

    int lengthOfLIS(vector<int>& nums) {
        return solveUsingRecursion(nums, 0, -1);
    }
};
