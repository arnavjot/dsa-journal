class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        map<int, int> mp;
        vector<int> ans;

        for (int i = 0; i < k; i++) {
            mp[nums[i]]++;
        }

        ans.push_back(mp.rbegin()->first);

        for (int i = k; i < nums.size(); i++) {
            mp[nums[i - k]]--;
            if (mp[nums[i - k]] == 0)
                mp.erase(nums[i - k]);

            mp[nums[i]]++;

            ans.push_back(mp.rbegin()->first);
        }

        return ans;
    }
};
