class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int> all;                       // merge like merge sort
        int i = 0, j = 0;
        while (i < nums1.size() && j < nums2.size())
            all.push_back(nums1[i] <= nums2[j] ? nums1[i++] : nums2[j++]);
        while (i < nums1.size()) all.push_back(nums1[i++]);
        while (j < nums2.size()) all.push_back(nums2[j++]);

        int t = all.size();
        if (t % 2 == 1) return all[t / 2];
        return (all[t / 2 - 1] + (double)all[t / 2]) / 2.0;
    }
};
