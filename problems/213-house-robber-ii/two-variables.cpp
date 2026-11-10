// Two variables on each range - O(n) time, O(1) space
class Solution {
public:
    // House Robber on houses start..end, keeping only the next two answers
    int robRange(vector<int>& nums, int start, int end) {
        int next1 = 0, next2 = 0;
        for (int i = end; i >= start; i--) {
            int include = nums[i] + next2;
            int exclude = next1;
            int curr = max(include, exclude);
            next2 = next1;
            next1 = curr;
        }
        return next1;
    }

    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];
        // the first and last houses are neighbours, so at least one of them is skipped
        int case1 = robRange(nums, 0, n - 2);
        int case2 = robRange(nums, 1, n - 1);
        return max(case1, case2);
    }
};
