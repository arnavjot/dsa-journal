class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size(), t = m + n;
        int i = 0, j = 0, prev = 0, cur = 0;
        // walk the merge order without storing it, stop at the middle
        for (int k = 0; k <= t / 2; k++) {
            prev = cur;
            if (i < m && (j >= n || nums1[i] <= nums2[j])) cur = nums1[i++];
            else cur = nums2[j++];
        }
        if (t % 2 == 1) return cur;
        return (prev + (double)cur) / 2.0;
    }
};
