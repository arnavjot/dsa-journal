class Solution {
public:
    vector<vector<int>> ans;

    void dfs(int index, vector<int>& candidates, int target, vector<int>& current) {
        if (target == 0) {
            ans.push_back(current);
            return;
        }
        if (index == candidates.size() || target < 0) {
            return;
        }
        // Pick the current candidate
        current.push_back(candidates[index]);
        dfs(index, candidates, target - candidates[index], current);
        // Backtrack
        current.pop_back();
        // Don't pick the current candidate
        dfs(index + 1, candidates, target, current);
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int> current;
        dfs(0, candidates, target, current);
        return ans;
    }
};
