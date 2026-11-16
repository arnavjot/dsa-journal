// XOR every index 0..n with every value: all but the missing number cancel - O(n) time, O(1) space
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int ans = n;                    // index n has no slot in the loop, so start with it
        for (int i = 0; i < n; i++) {
            ans ^= i ^ nums[i];
        }
        return ans;
    }
};
