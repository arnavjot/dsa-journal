class Solution {
public:
    int binarySearch(vector<int>& nums, int lo, int hi, int target) {
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (nums[mid] == target) return mid;
            if (nums[mid] < target) lo = mid + 1;
            else hi = mid - 1;
        }
        return -1;
    }

    int search(vector<int>& nums, int target) {
        int n = nums.size();

        // 1. find the minimum's index (the pivot), same as LC 153
        int s = 0, e = n - 1;
        while (s < e) {
            int mid = s + (e - s) / 2;
            if (nums[mid] <= nums[e]) e = mid;
            else s = mid + 1;
        }
        int pivot = s;

        // 2. both sides of the pivot are sorted: search the one that can hold target
        if (target >= nums[pivot] && target <= nums[n - 1])
            return binarySearch(nums, pivot, n - 1, target);
        return binarySearch(nums, 0, pivot - 1, target);
    }
};
