class Solution {
public:
    vector<vector<int>> ans;

    void dfs(int start, vector<int>& candidates, int target, vector<int>& current) {
        if (target == 0) {
            ans.push_back(current);
            return;
        }
        for (int i = start; i < candidates.size(); i++) {
            if (candidates[i] > target) continue;                  // too big to fit
            current.push_back(candidates[i]);
            dfs(i, candidates, target - candidates[i], current);   // i, not i + 1: reuse allowed
            current.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int> current;
        dfs(0, candidates, target, current);
        return ans;
    }
};
