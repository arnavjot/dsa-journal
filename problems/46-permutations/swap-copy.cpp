class Solution {
public:
// NOT PASSING BY REFERENCE SO WORKS WITHOUT BACKTRACKING BECAUSE EACH TIME NEW COPY IS BEING MADE
// PASS nums BY REFERENCE IT WILL GIVE WRONG ANSWER IF WE DONT USE BACKTRACKING
    void recurPermute(int index, vector<int> nums, vector<vector<int>>& ans) {
        if (index == nums.size()) {
            ans.push_back(nums);
            return;
        }
        for (int i = index; i < nums.size(); i++) {
            swap(nums[index], nums[i]);
            recurPermute(index + 1, nums, ans);
            // backtracking
            // swap(nums[index], nums[i]);
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans;
        recurPermute(0, nums, ans);
        return ans;
    }
};
