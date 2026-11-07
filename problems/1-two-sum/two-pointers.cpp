class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        vector<pair<int,int>> v;                  // (value, original index): sorting loses positions
        for (int i = 0; i < n; i++) v.push_back({nums[i], i});
        sort(v.begin(), v.end());

        int l = 0, r = n - 1;
        while (l < r) {
            int sum = v[l].first + v[r].first;
            if (sum == target) return {v[l].second, v[r].second};
            if (sum < target) l++;                // need bigger: move the small end up
            else r--;                             // need smaller: move the big end down
        }
        return {};
    }
};
