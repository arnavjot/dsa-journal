// Kadane's algorithm - O(n) time, O(1) space
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int maxi = INT_MIN, sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum = sum + nums[i];
            if (sum > maxi) {
                maxi = sum;
            }
            // maxi = max(sum,maxi);
            if (sum < 0) {
                sum = 0;
            }
        }
        return maxi;
    }
};
