class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<pair<int, int>> counts;
        vector<bool> visited(nums.size(), false);
        for(int i = 0; i < nums.size(); i++) {
            if(visited[i]) continue;
            int count = 1;
            visited[i] = true;
            for (int j = i + 1; j < nums.size();j++) {
                if(!visited[j] && nums[i] == nums[j]) {
                    count++;
                    visited[j] = true;
                }
            }
            counts.push_back({count, nums[i]});
        }

        sort(counts.rbegin(), counts.rend());

        vector<int> ans;
        for (int i = 0; i < k; i++) {
            ans.push_back(counts[i].second);
        }

        return ans;
    }
};
