// Better: every start, extend the end with a running sum - O(n^2) time, O(1) space
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int maxi = INT_MIN;
        for (int i = 0; i < nums.size(); i++) {
            int sum = 0;
            for(int j = i; j < nums.size(); j++){
                sum += nums[j];
                maxi = max(sum, maxi);
            }
        }
        return maxi;
    }
};
