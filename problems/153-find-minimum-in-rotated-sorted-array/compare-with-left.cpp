class Solution {
public:
    int findMin(vector<int>& nums) {
        int ans = nums[0];
        int l = 0, r = nums.size() - 1;

        while (l <= r) {
            // this part is already sorted, so its smallest is nums[l]
            if (nums[l] < nums[r]) {
                ans = min(ans, nums[l]);
                break;
            }

            int mid = l + (r - l) / 2;
            ans = min(ans, nums[mid]);

            // left part l..mid is sorted, so the minimum is on the right
            if (nums[mid] >= nums[l]) {
                l = mid + 1;
            } else {
                // the drop is on the left side (mid already counted)
                r = mid - 1;
            }
        }
        return ans;
    }
};
