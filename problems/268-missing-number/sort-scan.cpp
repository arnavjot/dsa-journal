// Sort, then scan for the first index where nums[i] != i - O(n log n) time
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != i)
                return i;
        }
        return nums.size(); // If all numbers 0 to n-1 are present, then n is missing
    }
};
