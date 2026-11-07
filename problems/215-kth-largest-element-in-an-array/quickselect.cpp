class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int target = nums.size() - k;              // index it would have if sorted ascending
        int lo = 0, hi = nums.size() - 1;
        mt19937 rng(42);
        while (true) {
            int p = lo + rng() % (hi - lo + 1);    // random pivot avoids the O(n²) worst case in practice
            int pivot = nums[p];
            // 3-way partition: < pivot | == pivot | > pivot
            int lt = lo, i = lo, gt = hi;
            while (i <= gt) {
                if (nums[i] < pivot) swap(nums[lt++], nums[i++]);
                else if (nums[i] > pivot) swap(nums[i], nums[gt--]);
                else i++;
            }
            if (target < lt) hi = lt - 1;
            else if (target > gt) lo = gt + 1;
            else return pivot;                     // target falls in the == block
        }
    }
};
