// Sort, then binary search for the first index where nums[i] != i - O(n log n) time
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        // another approach - sorting + binary search
        sort(nums.begin(), nums.end());
        int s = 0, e = nums.size() - 1;

        while (s <= e) {
            int mid = s + (e - s) / 2;
            if (nums[mid] == mid) {
                s = mid + 1;
            } else {
                e = mid - 1;
            }
        }
        return s;
    }
};
