class Solution {
public:
    vector<vector<int>> ans;
    void dfs(int index, vector<int>& candidates, int target, vector<int>& current) {
        if (target == 0) {
            ans.push_back(current);
            return;
        }
        for (int i = index; i < candidates.size(); i++) {
            if (i > index && candidates[i] == candidates[i - 1]) {
                continue;
            }
            if (candidates[i] > target) {
                break;
            }
            current.push_back(candidates[i]);
            dfs(i + 1, candidates, target - candidates[i], current);
            current.pop_back();
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<int> current;
        dfs(0, candidates, target, current);
        return ans;
    }
};
