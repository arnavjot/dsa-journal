// Two variables (space optimised) - O(n) time, O(1) space
class Solution {
public:
    int so(vector<int>& nums) {
        int n = nums.size();

        int next1 = 0, next2 = 0;

        for (int i = n - 1; i >= 0; i--) {
            int include = nums[i] + next2;
            int exclude = next1;
            int curr = max(include, exclude);

            next2 = next1;
            next1 = curr;
        }

        return next1;
    }
    int rob(vector<int>& nums) {
        int index = 0;
        int n = nums.size();
        int ans = so(nums);
        return ans;
    }
};
