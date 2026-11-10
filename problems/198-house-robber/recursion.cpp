// Recursion - O(2^n) time, O(n) stack space
class Solution {
public:
    int solveUsingRec(vector<int>& nums, int index) {
        if (index >= nums.size()) {
            return 0;
        }
        // robbing that house
        int include = nums[index] + solveUsingRec(nums, index + 2);
        // not robbing that house
        int exclude = 0 + solveUsingRec(nums, index + 1);
        int ans = max(include, exclude);
        return ans;
    }
    int rob(vector<int>& nums) {
        return solveUsingRec(nums, 0);
    }
};
