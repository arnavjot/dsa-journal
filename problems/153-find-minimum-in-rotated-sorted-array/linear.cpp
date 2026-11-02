class Solution {
public:
    int findMin(vector<int>& nums) {
        int ans = nums[0];
        for (int x : nums) ans = min(ans, x);
        return ans;
    }
};
