class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        vector<int> ans;
        vector<pair<int, int>> counts;

        for (int num : nums) {
            freq[num]++;
        }
        for (auto it : freq) {
            counts.push_back({it.second, it.first});
        }
        sort(counts.rbegin(), counts.rend());
        for (int i = 0; i < k; i++) {
            ans.push_back(counts[i].second);
        }

        return ans;
    }
};
