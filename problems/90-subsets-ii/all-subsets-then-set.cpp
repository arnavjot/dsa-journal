class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());                 // so equal subsets look identical
        int n = nums.size();
        set<vector<int>> unique;
        for (int mask = 0; mask < (1 << n); mask++) {   // all 2^n subsets, repeats included
            vector<int> s;
            for (int i = 0; i < n; i++)
                if (mask >> i & 1) s.push_back(nums[i]);
            unique.insert(s);                           // the set throws repeats away
        }
        return vector<vector<int>>(unique.begin(), unique.end());
    }
};
