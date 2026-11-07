class Solution {
public:
    vector<vector<int>> ans;

    void dfs(int index, vector<int>& nums, vector<int>& current) {
        ans.push_back(current);

        for (int i = index; i < nums.size(); i++) {
            if (i > index && nums[i] == nums[i - 1]) {
                continue;
            }

            current.push_back(nums[i]);
            dfs(i + 1, nums, current);
            current.pop_back();
        }
    }

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        vector<int> current;
        dfs(0, nums, current);

        return ans;
    }
};
