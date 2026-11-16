// Track the largest and smallest product ending here - O(n) time, O(1) space
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int best = nums[0], curMax = nums[0], curMin = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            int x = nums[i];
            if (x < 0) {
                swap(curMax, curMin);          // a negative flips the biggest and the smallest
            }
            curMax = max(x, curMax * x);       // start fresh at x, or extend
            curMin = min(x, curMin * x);
            best = max(best, curMax);
        }
        return best;
    }
};
